// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
bool add_word_to_hash(const char *word);
unsigned int size(void);
bool unload(void);
void free_linked_list(node *head);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Index for hash
    int hashIndex = hash(word);

    // Pointer to iterate the list
    node *currentNode = table[hashIndex];

    while (currentNode)
    {
        // Verify if the actual word is equals to the search word
        if (strcasecmp(currentNode->word, word) == 0)
            return true;
        currentNode = currentNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Use a prime number to initialize the hash value
    unsigned int hashvalue = 5381;
    int c;

    // Loop cycle to iterate each char of the word
    while ((c = *word++))
    {
        // Converts each char in lowercase and applies algorithm of djb2 hash
        // Hash * 33 + c
        hashvalue = ((hashvalue << 5) + hashvalue) + tolower(c);
    }
    // Calculates the size of table
    return hashvalue % N;
}

int words_count = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file in the dictionnary
    FILE *file = fopen(dictionary, "r");
    if (!file)
        return false;
    char word[LENGTH + 1];
    // Read the words in the file
    while (fscanf(file, "%s", word) != EOF)
    {
        if (!add_word_to_hash(word))
        {
            fclose(file);
            return false;
        }
        words_count++;
    }
    fclose(file);
    return true;
}

bool add_word_to_hash(const char *word)
{
    // Create new node for each word
    node *new_node = malloc(sizeof(node));
    if (!new_node)
        return false;
    // Copy the word in the node and initialize the next pointer
    strcpy(new_node->word, word);
    new_node->next = NULL;

    // Add the node in the hash table
    int index = hash(word);
    if (table[index] == NULL)
        table[index] = new_node;
    else
    {
        new_node->next = table[index];
        table[index] = new_node;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false

bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // Free the list linked to this index, if it exists
        if (table[i] != NULL)
            free_linked_list(table[i]);
    }
    return true;
}

void free_linked_list(node *head)
{
    if (head == NULL)
        return;
    // If the next node is not NULL, release recursively
    if (head->next != NULL)
        free_linked_list(head->next);
    // // Free the current node
    free(head);
}
