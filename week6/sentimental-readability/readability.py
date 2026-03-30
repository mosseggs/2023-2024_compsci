# TODO

from cs50 import get_string


text = get_string("Text: ")


words = 1
letters = 0
sentences = 0


for char in text:
    if char.isalpha():
        letters += 1
    elif char == " ":
        words += 1
    elif char == "." or char == "!" or char == "?":
        sentences += 1


Grade = 0.0588 * (letters / words) * 100 - 0.296 * (sentences / words) * 100 - 15.8


if Grade < 1:
    print("Before Grade 1")
elif Grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(Grade)}")
