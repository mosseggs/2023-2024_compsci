import csv
import sys

if len(sys.argv) != 2:
    sys.exit("Usage: python phonebook.py data.csv")

f = open(sys.argv[1])
reader = csv.DictReader(f)

fields = reader.fieldnames
if "name" not in fields or "number" not in fields:
    sys.exit("File must have name and number columns")

persons = []

for row in reader:
    # print(row)
    persons.append(row)

# print(persons)
for person in persons:
    name = person["name"]
    number = person["number"]
    print(f"{name}'s number is {number}")

