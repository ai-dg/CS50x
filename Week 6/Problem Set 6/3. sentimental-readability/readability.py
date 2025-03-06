from cs50 import get_string


def main():
    text = get_string("Text: ")

    # Calculate index formula
    L = count_lettres(text) * 100 / count_words(text)
    S = count_sentences(text) * 100 / count_words(text)

    grade = (0.0588 * L) - (0.296 * S) - 15.8

    # Float to integer
    round_grade = int(grade + 0.5)

    # Conditions of grade levels
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round_grade}")


# Count lettres
def count_lettres(string):
    lettres = 0
    for char in string:
        if char.isalpha():
            lettres += 1
    return lettres


# Count lettres using sentences conditions
def count_sentences(string):
    sentences = 0
    for char in string:
        if char in ["!", ".", "?"]:
            sentences += 1
    return sentences


# Count lettres using words conditions
def count_words(string):
    words = string.count(" ") + 1
    return words


main()
