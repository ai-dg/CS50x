#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // printf("Premier %d\n", candidates[0].votes);
    // printf("Deuxieme %d\n", candidates[1].votes);
    // printf("Troisieme %d\n", candidates[2].votes);
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Use of strcmp function to compare the name by the candidate.name data
    for (int i = 0; i < candidate_count; i++)
    {
        // Return 0 if the name is the same
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // int index[MAX];
    char *str;
    int temp = 0;
    int y = 0;
    int x = 0;

    str = NULL;
    // printf("Candidate count %d\n\n", candidate_count);
    while (x < candidate_count)
    {
        // printf("%d\n", candidates[x].votes);
        y = 0;
        while (y < candidate_count - 1)
        {
            // Bubble sort to organize the vote number from the biggest to the smallest
            if (candidates[y].votes < candidates[y + 1].votes)
            {
                temp = candidates[y].votes;
                candidates[y].votes = candidates[y + 1].votes;
                candidates[y + 1].votes = temp;

                str = candidates[y].name;
                candidates[y].name = candidates[y + 1].name;
                candidates[y + 1].name = str;
            }
            // printf("%d\n\n", x);
            y++;
        }
        x++;
    }
    // printf("%d\n", index[0]);
    // Printf of candidate[0]
    printf("%s\n", candidates[0].name);
    // Printf of candidates with the same number of votes
    for (int z = 1; z < candidate_count; z++)
    {
        if (candidates[z].votes == candidates[0].votes)
            printf("%s\n", candidates[z].name);
    }
    //     int z = 0;
    //     while (z < candidate_count)
    //     {
    //         printf("\n%d\n", candidates[z].votes);
    //         z++;
    //     }
    //     z = 0;
    //     while (z < candidate_count)
    //     {
    //         printf("\n%s\n", candidates[z].name);
    //         z++;
    //     }
    //     int n = 0;
    //     for (int z = 0; z < candidate_count; z++)
    //     {
    //     n = index[z];
    //     printf("%s", candidates[n].name);
    //     }
    return;
}
