import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from werkzeug.utils import secure_filename
from werkzeug.security import check_password_hash
import werkzeug.security
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Global apology function to use in the redirect declarations
def apology(message, code=400):
    return render_template("apology.html", message=message), code


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get stocks and shares
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM operations WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id,
    )
    # Balance cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total_value = cash
    grand_total = cash
    # Iterate stocks and add price and total values
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]
    return render_template(
        "index.html",
        stocks=stocks,
        cash=usd(cash),
        total_value=usd(total_value),
        grand_total=usd(grand_total),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a positive integer number of shares", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("symbol not found", 400)
        price = quote["price"]
        total_cost = int(shares) * price
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if cash < total_cost:
            return apology("not enough cash", 400)
        # Update cash in users table
        db.execute(
            "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
            total_cost=total_cost,
            user_id=user_id,
        )
        # Add the history purchase in the operations table
        db.execute(
            "INSERT INTO operations (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
            user_id=user_id,
            symbol=symbol,
            shares=shares,
            price=price,
        )

        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    # Get the history transactions
    operations = db.execute(
        "SELECT * FROM operations WHERE user_id = ? ORDER BY timestamp DESC", user_id
    )
    return render_template("history.html", operations=operations)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        # Convert the symbol in capital letter
        quote = lookup(symbol.upper())
        if not quote:
            return apology("invalid symbol", 400)

        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()
    if request.method == "POST":
        # Request form to get values for the variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide password", 400)
        elif password != confirmation:
            return apology("passwords don't match", 400)
        existing_user = db.execute(
            "SELECT * FROM users WHERE username = ?", (username,)
        )
        # Verify the existing user
        if existing_user:
            return apology("This username already exists", 400)
        password_hash = werkzeug.security.generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            password_hash,
        )
        session["username"] = username
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    # Get users stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM operations WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=user_id,
    )
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology(
                "must provide a positive integer number of shares",
                400,
            )
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enough shares", 400)
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("symbol not found", 400)
                    price = quote["price"]
                    total_sale = shares * price
                    # Update users table
                    db.execute(
                        "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                        total_sale=total_sale,
                        user_id=user_id,
                    )
                    # Add the sale in the history user
                    db.execute(
                        "INSERT INTO operations (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                        user_id=user_id,
                        symbol=symbol,
                        shares=-shares,
                        price=price,
                    )
                    flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                    return redirect("/")
        return apology("symbol not found", 400)
    else:
        return render_template("sell.html", stocks=stocks)
