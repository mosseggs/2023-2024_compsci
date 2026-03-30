# TODO

from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            break

    for i in range(height):
        print_row(height - i - 1, i + 1)


def print_row(spaces, bricks):
    print(" " * spaces, end="")
    print("#" * bricks, end="")
    print("  ", end="")
    print("#" * bricks, end="")
    print()


main()
