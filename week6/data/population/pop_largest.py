import csv

countries = []

with open("world-country-populations.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        countries.append(row)

max_growth = 0

for country in countries:
    growth = float(country["population_growthRate"])
    if growth > min_growth_rate:
        max_growth = growth
        max_country = country["country"]
        max_city = country["city"]

max_growth_percent = round(max_growth * 100, 2)
print(f'{max_city} in {max_country} had the highest growth rate at {max_growth_percent}%')