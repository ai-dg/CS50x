#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int x;
    int y;
    int z;
    int score[1000];
    int total_score;
    int n;
    char alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    y = 0;
    x = 0;
    z = 0;
    total_score = 0;

    // Convert alpha
    while (word[x])
    {
        if (islower(word[x]) > 0)
        {
            word[x] = word[x] - 32;
        }
        x++;
    }
    x = 0;

    // Loop of word
    while (word[y])
    {

        x = 0;
        // Loop to recover the alpha index
        if (word[y] >= 'A' && word[y] <= 'Z')
        {

            while (alph[x])
            {
                if (alph[x] == word[y])
                {
                    score[z] = x;
                    z++;
                }
                x++;
            }
        }
        y++;
    }

    n = 0;
    x = 0;

    // Recovering of points by alpha index
    while (x <= z - 1)
    {
        n = score[x];
        total_score = total_score + POINTS[n];
        x++;
    }

    return (total_score);
}
