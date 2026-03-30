# Print n cities with highest or lowest growth rates

import csv


def main():

    max_growth_percent = int(input("Maximum Grouth Percentage: "))
    max_growth_rate = max_growth_percent / 100

    min_growth_percent = int(input("Minimum Grouth Percentage: "))
    min_growth_rate = min_growth_percent / 100

    sort_by = input("Highest Growth First: ")
    while True:
        if sort_by in ["yes", "y", "Yes", "YES", "Highest", "highest", "HIGHEST"]:
            order_by = True
            break
        elif sort_by in ["No", "N", 'n', "NO", "no", "lowest", "low"]:
            order_by = False
            break

    countries = get_data(max_growth_rate, min_growth_rate)

    number = int(input("How many to print: "))

    sorted_countries = sorted(countries, key=lambda x: x['population_growthRate'], reverse=order_by)

    for i in range(min(number, len(countries))):
        country = sorted_countries[i]
        growth = country['population_growthRate']
        print(f"{country['city']}, {country['country']}, {round(growth * 100, 2)}%")


def get_data(max, min):
    countries = []

    with open("world-country-populations.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            growth = float(row["population_growthRate"])
            if min <= growth <= max:
                country = row
                country['population_growthRate'] = growth
                countries.append(country)

    return countries


main()