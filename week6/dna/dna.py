import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database.csv sequence.txt")

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        STRs = reader.fieldnames
        for row in reader:
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    mys = {}
    for item in STRs:
        if item != "name":
            mys[item] = str(longest_match(dna, item))

    # TODO: Check database for matching profiles
    # Using range and check if match
    # for thing in data:
    #     similarities = 0
    #     for item in range(0, len(STRs)):
    #         if thing[STRs[item]] == str(mys[item]):
    #             similarities += 1
    #         if similarities == len(STRs) - 1:
    #             person = thing["name"]
    # if person == "":
    #    print("No Match")
    # else:
    #    print(person)
    # Using range and check if not match
    # for thing in data:
    #     match = true
    #     for item in range(0, len(STRs)):
    #         if thing[STRs[item]] 1= str(mys[item]):
    #             match = false
    #             break
    #         else:
    #             person = thing["name"]
    # using del
    for thing in data:
        name = thing["name"]
        del thing["name"]
        if thing == mys:
            print(name)
            return
    print("No Match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
