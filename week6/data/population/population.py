import csv

min_growth_percent = int(input("Minimum Growth Percentage: "))
min_growth_rate = min_growth_percent/100

countries = []

with open("world-country-populations.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        countries.append(row)

for country in countries:
    growth = float(country["population_growthRate"])
    if growth > min_growth_rate:
        percent = round(growth * 100,2)
        print(f'{country["city"]}, {country["country"]}: {percent}%')