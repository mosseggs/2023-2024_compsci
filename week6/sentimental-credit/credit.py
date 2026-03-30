from cs50 import get_string

credit = get_string("Number: ")

# Step 1 "Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together."
creditrev = credit[::-1]
credit1 = creditrev[1::2]
# store the original file
creditStore = credit1

for num in creditStore:
    if int(num) * 2 < 9:
        credit1 = credit1 + str(int(num) * 2)
    else:
        credit1 = credit1 + str((2 * int(num)) - 9)
# transfer to becoming an integer, just makes it easier to add multiple digit numbers.
creditInt = sum(map(int, credit1[len(creditStore) :]))
# Step 2 "Add the sum to the sum of the digits that weren’t multiplied by 2."
creditInt += sum(map(int, creditrev[::2]))

# Step 3 "If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!"
length = len(credit)
creditStart = int(credit[:2])

# Checks what card it is
if creditInt % 10 != 0:
    print("INVALID")
elif creditStart // 10 == 4 and (length == 13 or length == 16):
    print("VISA")
elif 50 < creditStart < 56 and length == 16:
    print("MASTERCARD")
elif (creditStart == 34 or creditStart == 37) and length == 15:
    print("AMEX")
else:
    print("INVALID")
