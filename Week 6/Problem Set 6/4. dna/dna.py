import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable

    filename2 = sys.argv[1]
    with open(filename2, "r") as file:
        reader = csv.DictReader(file)
        column_names = reader.fieldnames[1:]

    # TODO: Read DNA sequence file into a variable

    filename = sys.argv[2]
    with open(filename) as file:
        sequence = file.readline().strip()

    # TODO: Find longest match of each STR in DNA sequence
    counts = {}

    for column_name in column_names:
        count = longest_match(sequence, column_name)
        counts[column_name] = count

    # TODO: Check database for matching profiles

    database = []
    with open(filename2, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    match_found = False

    for row in database:
        match = True
        for column_name, count in counts.items():
            if not row[column_name].isdigit():
                match = False
                break
            if int(row[column_name]) != count:
                match = False
                break

        if match:
            print(row["name"])
            match_found = True

    if not match_found:
        print("No match")


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
