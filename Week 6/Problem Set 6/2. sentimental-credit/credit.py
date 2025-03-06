from cs50 import get_int


def main():
    # Variables declaration
    credit = 0
    credit_reduc = 0
    digits = 0
    i = 0
    sum1 = 0
    sum2 = 0
    total_sum = 0
    tmp = 0

    # Input data
    while True:
        credit = get_int("Number: ")
        if credit >= 0:
            break

    #  Calculate checksum
    credit_reduc = credit
    while credit_reduc > 0:
        i += 1
        digits = credit_reduc % 10
        # Checksum with odd number
        if i % 2 == 0:
            # If we have nbr > 10 as an answer of digit * 2, we apply modulo
            if (digits * 2) >= 10:
                sum1 += (digits * 2) // 10
                sum1 += (digits * 2) % 10
            if (digits * 2) < 10:
                sum1 += digits * 2
        # Checksum with pair number
        else:
            sum2 += digits
        # Store the first two numbers of input to check card and starting digits
        if 10 < credit_reduc < 100:
            tmp = credit_reduc

        credit_reduc //= 10

    # Check card and starting digits
    total_sum = sum1 + sum2
    if total_sum % 10 != 0 or not (13 <= i <= 16):
        print("INVALID\n")
    elif 13 <= i <= 16 and 40 <= tmp <= 42:
        print("VISA\n")
    elif i == 15 and (tmp == 34 or tmp == 37):
        print("AMEX\n")
    elif i == 16 and 51 <= tmp <= 55:
        print("MASTERCARD\n")
    else:
        print("INVALID\n")


main()
