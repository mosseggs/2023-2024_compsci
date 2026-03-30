import csv

sets = []
themes = []
names = []
parts = []
categories = []
names2 = []

def main():
    # uses CSV files from https://www.kaggle.com/datasets/rtatman/lego-database/data?select=inventories.csv

    # uses 4 files and stores them in seperate lists. names for 2 of the files are stored in additional lists.
    with open("sets.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            sets.append(row)

    with open("themes.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            themes.append(row)
            names.append(row["name"].casefold())

    with open("parts.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            parts.append(row)

    with open("part_categories.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            categories.append(row)
            names2.append(row["name"].casefold())

    # Check what section they want to enter
    while True:
        interaction = input("What do you want to do?\n1: Find a Lego Set\n2: Find a Lego Piece\n")
        if interaction == "1":
            findSet()
            break
        elif interaction == "2":
            findPiece()
            break


# Check how they want to identify the set, or say it isnt a method.
def findSet():
    way = input("How do you want to find the set?\n1:Set Number\n2:Theme\n")
    if way == "1":
        findSetwNum(sets)
    elif way == "2":
        findSetwTheme(sets, themes)
    else:
        print("Not a valid way")
        findSet()

# find the set number using the official format of the set number. Then find the set, or say it isn't an official lego set.
def findSetwNum(sets):
    number = input("Input a set number in the official format (ex: '10019-1', the set 'Rebel Blockade Runner - UCS') ").casefold()
    while "-" not in number:
        print("not a valid set number")
        number = input("Input a set number in the official format (ex: '10019-1', the set Rebel Blockade Runner) ").casefold()
    for set in sets:
        if set["set_num"] == number:
            print(set["name"] + ", part of the " + themes[int(set["theme_id"]) - 1]["name"] + " theme, with " + set["num_parts"] + " pieces")
            break
        elif (set == sets[-1:][0]) and (set["set_num"] != number):
            print("not a valid set number")
            break


# find all sets that share a theme in common by inputting the theme id or theme name. If either are invalid, say it isn't a valid theme
def findSetwTheme(sets, themes):
    thing = input("What theme are you looking for? ").casefold()

    while True:
        if thing.isnumeric() == True and (int(thing) <= int(themes[-1:][0]["id"]) and int(thing) >= 1):
            thing = themes[int(thing) - 1]["name"].casefold()
            break
        elif thing.isascii() and thing in names:
            break
        else:
            print("Not a valid theme")
            thing = input("What theme are you looking for? ").casefold()

    for theme in range(0, len(themes)):
        if themes[theme]["name"].casefold() == thing:
            print("The selected theme is " + thing)
            thing = themes[theme]["id"]
            break

    for set in sets:
        if set["theme_id"] == thing:
            print(set["name"] + ", which has " + set["num_parts"] + " parts")

# same as sets but with pieces
def findPiece():
    way = input("How do you want to find the part?\n1:Part Number\n2:Category\n")
    if way == "1":
        findPiecewNum(parts)
    elif way == "2":
        findPiecewCat(parts, categories)
    else:
        print("Not a valid way")
        findPiece()

# find the piece using the offcial format, which sometimes includes letters. Or return that it isn not a valid piece id.
def findPiecewNum(parts):
    number = input("Input a piece number in the official format (ex: '10039', aka Pullback Motor 8 x 4 x 2/3) ").casefold()
    for part in parts:
        if part["part_num"] == number:
            print(part["name"] + ", part of the " + categories[int(part["part_cat_id"]) - 1]["name"] + " category")
            break
        elif (part == parts[-1:][0]) and (part["part_num"] != number):
            print("not a valid piece number")
            break

# same as with set and themes, but with parts and categories.
def findPiecewCat(parts, categories):
    thing = input("What category are you looking for? ").casefold()
    while True:
        if thing.isnumeric() == True and (int(thing) <= int(categories[-1:][0]["id"]) and int(thing) >= 1):
            thing = categories[int(thing) - 1]["name"].casefold()
            break
        elif thing.isascii() and thing in names2:
            break
        else:
            print("Not a valid category")
            thing = input("What category are you looking for? ").casefold()

    for cat in range(0, len(categories)):
        if categories[cat]["name"].casefold() == thing:
            print("The selected theme is " + categories[cat]["name"])
            thing = categories[cat]["id"]
            break

    for part in parts:
        if part["part_cat_id"] == thing:
            print(part["name"] + ", part number " + part["part_num"])

# run the program
main()
