# TODO
from cs50 import get_int

while True:
    length = get_int("Height: ")
    if 1 <= length <= 8:
        break

for row in range(length):
    for column in range(length - row - 1):
        print(" ",end='')
    for column in range(row + 1):
        print("#",end='')
    print("  ",end='')
    for column in range(row + 1):
        print("#",end='')
    for column in range(length - row - 1):
        print(" ",end='')
    print()
