#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Initialize of all arrays, values set to 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        pairs[i].winner = 0;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        pairs[j].loser = 0;
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        for (int a = 0; a < candidate_count; a++)
        {
            ranks[a] = 0;
        }
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i = 0;

    i = 0;
    while (i < candidate_count)
    {
        // Check name with strcmp == 0 and ranks updated by order of preferences
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
        i++;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int count = candidate_count;
    int ranks2[candidate_count];

    // Use of a second ranks2[] to assign a system of points to verify the order of strength of preferences
    for (int a = 0; a < candidate_count; a++)
        ranks2[a] = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int x = 0; x < candidate_count; x++)
        {
            if (candidates[x] == candidates[ranks[i]])
            {
                count--;
                ranks2[x] += count;
            }
        }
    }
    // Record of preferences by order of ranks2[]
    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            if (ranks2[x] > ranks2[y])
                preferences[x][y] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    pair_count = 0;
    // Adding pairs to the array pairs[].winner and pairs[].loser
    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = x + 1; y < candidate_count; y++)
        {

            if (preferences[x][y] > preferences[y][x])
            {
                pairs[pair_count].winner = x;
                pairs[pair_count].loser = y;
                pair_count++;
            }
            else if (preferences[x][y] < preferences[y][x])
            {
                pairs[pair_count].winner = y;
                pairs[pair_count].loser = x;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int temp;
    char *temp2;

    int power_victory1;
    int power_victory2;

    // Bubble sort of pairs[].winner and pairs[].loser using strength of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - 1; j++)
        {
            power_victory1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            power_victory2 =
                preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];
            if (power_victory1 < power_victory2)
            {
                temp = pairs[j].winner;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j + 1].winner = temp;

                temp = pairs[j].loser;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].loser = temp;
            }
        }
    }
    return;
}

bool check_cycle(int winner, int loser)
{

    // Check the arrows system and cycles
    while (winner != -1)
    {
        if (winner == loser)
            return true;

        bool arrow_found = false;
        for (int x = 0; x < candidate_count; x++)
        {
            if (locked[x][winner])
            {
                winner = x;
                arrow_found = true;
                break;
            }
        }
        if (!arrow_found)
            return false;
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Using boolean fonction, the locked 2D array is completed
    for (int x = 0; x < pair_count; x++)
    {
        int winner = pairs[x].winner;
        int loser = pairs[x].loser;

        if (!check_cycle(winner, loser))
            locked[winner][loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // One candidate is chosen using an int count and the victory strength definied in pairs[]
    int count_max = 0;
    int index_winner = -1;
    int index_victory_max = -1;

    for (int x = 0; x < candidate_count; x++)
    {
        int count = 0;
        int victory_index = 0;

        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][x] == false)
            {
                count++;
                if (pairs[y].winner == x)
                    victory_index++;
            }
        }
        if (count == count_max && victory_index > index_victory_max && index_winner != -1)
        {
            index_victory_max = victory_index;
            index_winner = x;
        }
        else if (count > count_max)
        {
            count_max = count;
            index_winner = x;
            index_victory_max = victory_index;
        }
    }
    if (index_winner != -1)
    {
        printf("%s\n", candidates[index_winner]);
    }

    return;
}
