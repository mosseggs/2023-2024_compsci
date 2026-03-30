import csv

countries = []

with open("life_expectancy.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        countries.append(row)

max_life = 0

for country in countries:
    life = float(country["Female Life Expectancy"])
    if life > max_life:
        max_life = life
        max_country = country["Country"]
        max_year = country["Year"]

print(f"{max_country} had the longes life expectancy for females, {max_life}, in {max_year}")