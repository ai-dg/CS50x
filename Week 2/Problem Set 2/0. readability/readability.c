#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int count_lettres(char *str);
int count_sentences(char *str);
int count_words(char *str);

int main(void)
{
    string text = get_string("Text: ");

    float grade;
    float L;
    float S;

    int round_grade;
    // Calculate index formula
    L = count_lettres(text) * ((100 / (float) count_words(text)));
    S = count_sentences(text) * ((100 / (float) count_words(text)));

    grade = (0.0588 * L) - (0.296 * S) - 15.8;

    // Float to integer
    round_grade = grade + 0.5;

    // Conditions of grade levels
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", round_grade);
    }

    return (0);
}
// Count lettres using ctype.h
int count_lettres(char *str)
{
    int i;
    int lettres;

    i = 0;
    lettres = 0;

    while (str[i])
    {
        if (isalpha(str[i]) > 0)
            lettres++;
        i++;
    }

    return lettres;
}
// Count lettres using sentences conditions
int count_sentences(char *str)
{
    int i;
    int sentences;

    i = 0;
    sentences = 0;

    while (str[i])
    {
        if (str[i] == '!' || str[i] == '.' || str[i] == '?')
            sentences++;
        i++;
    }
    return sentences;
}
// Count lettres using words conditions
int count_words(char *str)
{
    int i;
    int words;

    i = 0;
    words = 0;

    while (str[i])
    {
        if (str[i] == ' ')
            words++;
        i++;
    }
    words += 1;
    return words;
}
