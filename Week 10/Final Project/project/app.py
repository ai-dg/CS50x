# Web application developped by Diego Agudelo and Ralph Balazs
# pip install Flask-Mail Flask-Session Werkzeug pip3 install cs50
# admin username: admin password: 12345
# standard username: Maite password: 12
# test username: test password: 123
from cs50 import SQL
from flask import Flask, render_template, request, session, redirect
from flask_mail import Mail, Message
from flask_session import Session
from werkzeug.utils import secure_filename
from werkzeug.security import check_password_hash
import werkzeug.security
from config import Config
import os
import sqlite3

app = Flask(__name__)
# app.config['MAIL_SERVER'] = 'smtp.gmail.com'
# app.config['MAIL_PORT'] = 587
# app.config['MAIL_USE_TLS'] = True
# app.config['MAIL_USE_SSL'] = False
# app.config['MAIL_USERNAME'] = os.environ.get('MAIL_USERNAME')
# app.config['MAIL_PASSWORD'] = os.environ.get('MAIL_PASSWORD')
app.config.from_object(Config)
mail = Mail(app)
db = SQL("sqlite:///database.db")
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Index route
@app.route("/")
def index():
    return render_template("index.html")


# Search tool in the header
@app.route("/search/")
def search():
    q = request.args.get("q")
    if q:
        shows = db.execute(
            "SELECT * FROM recettes WHERE nom LIKE ? LIMIT 10", "%" + q + "%"
        )
    else:
        shows = []
    return render_template("search.html", shows=shows)


# Depth search taking the same value of q in /search
@app.route("/search2")
def search2():
    q = request.args.get("q")
    page = request.args.get("page", 1, type=int)
    per_page = 10
    if q:
        result = db.execute(
            "SELECT COUNT(*) as count FROM recettes WHERE nom LIKE ?", "%" + q + "%"
        )
        total_count = result[0]["count"] if result else 0
        shows = db.execute(
            "SELECT * FROM recettes WHERE nom LIKE ? LIMIT ? OFFSET ?",
            "%" + q + "%",
            per_page,
            (page - 1) * per_page,
        )
    else:
        total_count = 0
        shows = []
    if not shows:
        return redirect("/apology?message=" + "No results found.")
    total_pages = (total_count + per_page - 1) // per_page
    return render_template(
        "search2.html", shows=shows, total_pages=total_pages, q=q, page=page
    )


# Detail of each recipe
@app.route("/detail")
def recette_detail():
    recette_id = request.args.get("id")
    recettes = []
    # print(f"RECEETTTEEEEEE, {recette_id}")
    if recette_id:
        recettes = db.execute(
            "SELECT * FROM recettes WHERE recettes.id = ?", (recette_id,)
        )
        # print(f"RECEETTTEEEEEE, {recettes}")
        # print(f"RECEETTTEEEEEE, {ingredients}")
    return render_template("recette_detail.html", recettes=recettes)


# Session to recover the password
@app.route("/send_email", methods=["GET", "POST"])
def send_email():
    if request.method == "GET":
        return render_template("send_mail.html")
    if request.method == "POST":
        first_name = request.form["first_name"]
        last_name = request.form["last_name"]
        result = db.execute(
            "SELECT * FROM users WHERE first_name = ? AND last_name = ?",
            first_name,
            last_name,
        )
        if result:
            user = result[0]
            session["can_reset_password"] = True
            return render_template("reset_password.html", username=user["username"])
        else:
            return redirect(
                "/apology?message="
                + "No users found with this information. Please try again."
            )
    return render_template("send_mail.html")


# End of the session to recover the password
@app.route("/reset_password/<username>", methods=["POST"])
def reset_password(username):
    if not session.get("can_reset_password"):
        return redirect("/login")
    new_password = request.form["new_password"]
    confirm_password = request.form["confirm_password"]
    if new_password != confirm_password:
        return redirect(
            "/apology?message=" + "The passwords do not match. Please try again."
        )
    hashed_password = werkzeug.security.generate_password_hash(new_password)
    db.execute(
        "UPDATE users SET password_hash = ? WHERE username = ?",
        hashed_password,
        username,
    )
    session.pop("can_reset_password", None)
    return redirect("/login")


# Profile detail of the user session
@app.route("/profile")
def profile():
    if not session.get("name"):
        return redirect("/login")
    username = session["name"]
    result = db.execute("SELECT * FROM users WHERE username = ?", (username,))
    if result:
        user = result[0]
        if username == "admin":
            return redirect("/admin")
        recettes = db.execute("SELECT * FROM recettes WHERE username = ?", (username,))
        user_info = {
            "email": user["email"],
            "first_name": user["first_name"],
            "last_name": user["last_name"],
        }
        return render_template("profile.html", recettes=recettes, user_info=user_info)
    else:
        return redirect("/login")


# Login access to create user session
@app.route("/login", methods=["GET", "POST"])
def login():
    if "name" in session:
        return redirect("/profile")
    if request.method == "POST":
        username = request.form.get("name")
        password = request.form.get("password")
        result = db.execute("SELECT * FROM users WHERE username = ?", (username,))
        if result:
            user = result[0]
            if check_password_hash(user["password_hash"], password):
                session["name"] = username
                return redirect("/profile")
            else:
                return redirect("/apology?message=" + "Invalid username or password.")
        else:
            return redirect("/apology?message=" + "Invalid username or password.")
    return render_template("login.html")


# Route to specify the error case
@app.route("/apology")
def apology():
    message = request.args.get("message", "An error has occurred.")
    return render_template("apology.html", message=message)


# Logout tool to redirect the index page
@app.route("/logout")
def logout():
    session.pop("name", None)
    return redirect("/")


# Route for creating the user identifies
@app.route("/signup", methods=["GET", "POST"])
def signup():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return redirect("/apology?message=" + "Passwords don't match")
        existing_user = db.execute(
            "SELECT * FROM users WHERE username = ?", (username,)
        )
        if existing_user:
            return redirect("/apology?message=" + "This username already exists")
        password_hash = werkzeug.security.generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, password_hash) VALUES (?, ?)",
            username,
            password_hash,
        )
        session["username"] = username
        return redirect("/login")
    return render_template("signup.html")


# Admin route, its just for erasing the users accounts
@app.route("/admin")
def admin():
    users = db.execute("SELECT * FROM users")
    return render_template("admin.html", users=users)


# Tool to erase the user acccount
@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM users WHERE username = ?", id)
        db.execute("DELETE FROM recettes WHERE username = ?", id)
    return redirect("/admin")


# Informations updating, a tool in the profile user
@app.route("/update_info", methods=["POST"])
def update_info():
    if not session.get("name"):
        return redirect("/login")
    email = request.form.get("email")
    first_name = request.form.get("first_name")
    last_name = request.form.get("last_name")
    db.execute(
        "UPDATE users SET email = ?, first_name = ?, last_name = ? WHERE username = ?",
        email,
        first_name,
        last_name,
        session["name"],
    )
    return redirect("/profile")


# Tool found in the profile user
@app.route("/delete_recette", methods=["POST"])
def delete_recette():
    recette_id = request.form.get("id")
    if not session.get("name"):
        return redirect("/login")
    photo_url = db.execute("SELECT photo_url FROM recettes WHERE id = ?", recette_id)
    if photo_url and photo_url[0]["photo_url"] != "images/default.png":
        photo_path = photo_url[0]["photo_url"]
        same_photo_count = db.execute(
            "SELECT COUNT(*) FROM recettes WHERE photo_url = ?", photo_path
        )
        if same_photo_count[0]["COUNT(*)"] <= 1:
            try:
                os.remove(os.path.join("static", photo_path))
            except OSError:
                pass
    db.execute("DELETE FROM recettes WHERE id = ?", (recette_id,))
    return redirect("/profile")


# Add button in the header
@app.route("/add_recipe", methods=["GET", "POST"])
def add_recipe():
    if not session.get("name"):
        return redirect("/login")
    if request.method == "POST":
        nom_recette = request.form.get("nom_recette")
        description = request.form.get("description")
        temps_preparation = request.form.get("temps_preparation")
        temps_cuisson = request.form.get("temps_cuisson")
        portions = request.form.get("portions")
        difficulte = request.form.get("difficulte")
        categorie = request.form.get("categorie")
        instructions = ";".join(
            request.form.get(f"instruction{i}")
            for i in range(1, 100)
            if request.form.get(f"instruction{i}")
        )
        ingredients = ";".join(
            request.form.get(f"ingredient{i}")
            for i in range(1, 100)
            if request.form.get(f"ingredient{i}")
        )
        file = request.files["image"]
        image_path = None
        existing_recette = db.execute(
            "SELECT * FROM recettes WHERE nom = ?", (nom_recette,)
        )
        if existing_recette:
            return redirect("/apology?message=" + "This recipe name already exists")
        file = request.files["image"]
        if file and file.filename:
            filename = secure_filename(file.filename)
            file.save(os.path.join("static/images/recipes/", filename))
            image_path = "images/recipes/" + filename
        else:
            image_path = "images/default.png"

        db.execute(
            "INSERT INTO recettes (nom, description, instructions, username, photo_url, temps_preparation, temps_cuisson, portions, difficulte, categorie, ingredients) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            nom_recette,
            description,
            instructions,
            session["name"],
            image_path,
            temps_preparation,
            temps_cuisson,
            portions,
            difficulte,
            categorie,
            ingredients,
        )
        return redirect("/profile")
    return render_template("add_recipe.html")


# Modify recipe once the user creates an account
@app.route("/modify_recipe/<int:recette_id>", methods=["GET", "POST"])
def modify_recipe(recette_id):
    if request.method == "GET":
        recette = db.execute("SELECT * FROM recettes WHERE id = ?", (recette_id,))
        if recette:
            return render_template("modify_recipe.html", recettes=recette)
        return redirect("/apology?message=" + "Recipe not found")
    if request.method == "POST":
        file = request.files["image"]
        if file and file.filename:
            filename = file.filename
            file.save(os.path.join("static/images/recipes/", filename))
            image_path = "images/recipes/" + filename
        else:
            image_path = request.form.get("image_url")
        nom = request.form.get("nom")
        descript = request.form.get("descript")
        categorie = request.form.get("categorie")
        difficulte = request.form.get("difficulte")
        portions = request.form.get("portions")
        temps_preparation = request.form.get("temps_preparation")
        temps_cuisson = request.form.get("temps_cuisson")
        instructions = []
        for i in range(1, 100):
            instruction = request.form.get(f"instruction{i}")
            if instruction:
                instructions.append(instruction)
        instructions_str = ";".join(instructions)
        ingredients = []
        for i in range(1, 100):
            ingredient = request.form.get(f"ingredient{i}")
            if ingredient:
                ingredients.append(ingredient)
        ingredients_str = ";".join(ingredients)
        db.execute(
            "UPDATE recettes SET nom = ?, description = ?, categorie = ?, difficulte = ?, portions = ?, instructions = ?, ingredients = ?, temps_preparation = ?, temps_cuisson = ?, photo_url = ? WHERE id = ?",
            nom,
            descript,
            categorie,
            difficulte,
            portions,
            instructions_str,
            ingredients_str,
            temps_preparation,
            temps_cuisson,
            image_path,
            recette_id,
        )
        return redirect(f"/modify_recipe/{recette_id}")


# Its the three buttons in the index page just to choose one category
@app.route("/recettes/<category>")
def category(category):
    if category in ["Culinary Arts", "Bakery", "Pastry"]:
        recettes = db.execute("SELECT * FROM recettes WHERE categorie = ?", (category,))
        return render_template("category.html", recettes=recettes, categorie=category)
    else:
        return redirect("/apology?message=" + "Catégorie invalide")
