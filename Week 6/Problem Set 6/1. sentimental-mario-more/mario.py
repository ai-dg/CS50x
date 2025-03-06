from cs50 import get_int


def main():
    # List of variables
    n = 0
    y = 0
    z = 0

    # Declaration of n, limited beetwen 1 and 8
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break

    # Initialization of z to be modified in the loop
    z = n

    # Mario loop !
    for i in range(n):
        x = y
        for j in range(z - 2, -1, -1):
            print(" ", end="")
        for x in range(y, -1, -1):
            print("#", end="")
        print("  ", end="")
        for x in range(y, -1, -1):
            print("#", end="")
        print()
        z -= 1
        y += 1


main()
