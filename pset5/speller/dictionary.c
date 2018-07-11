// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

#define char2ind(c) ((int)c - (int)'a')

//defining struct for trie that'll load dictionary
typedef struct _trie
{
 bool endword;
 struct _trie* alphabet[27];
}
trie;

//credits to https://www.geeksforgeeks.org/trie-insert-and-search/ for the help
trie* getNode(void)
{
    trie* pNode = NULL;

    pNode = (trie*)malloc(sizeof(trie));

    if (pNode)
    {
        int i;

        pNode->endword = false;

        for (i = 0; i < 27; i++)
            pNode->alphabet[i] = NULL;
    }

    return pNode;
}

//inserting function
void insert(trie* root, char word[46])
{

    for(int g = 0; g < strlen(word); g++)
    {
        char one = word[g];
        //checks if the index of the array at that node is pointing to NULL if it is makes it point to another node
        if(!root->alphabet[char2ind(one)])
        {
            root->alphabet[char2ind(one)] = getNode();
        }
        root = root->alphabet[char2ind(one)];
    }
    root->endword = true;
}

//function used to search through trie in check
bool searcher(trie* lookup, const char *wordsear)
{
    // trie* search = lookup;
    int index;
    for(int i = 0; i < strlen(wordsear); i++)
    {
        if(isalpha(wordsear[i]) != 0)
        {
            index = char2ind(tolower(wordsear[i]));
        }
        else if(wordsear[i] == '\'')
        {
            index = 26;
        }
        if(!lookup->alphabet[index])
        {
            return false;
        }
        lookup = lookup->alphabet[index];
    }
    return lookup->endword;
}

//function used in unload that will free the dict trie
bool freeer(trie* finish)
{
    trie* trav = finish;
    for(int k = 0; k < 27; k++)
    {
        if(trav->alphabet[k] != NULL)
        {
            freeer(trav->alphabet[k]);
        }
    }
    free(trav);
    trav = NULL;
    return true;
}

//global root node for the loaded dictionary
trie* root = NULL;
//global variable for word count
int words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if(searcher(root, word) == true)
        return true;

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    //initializing root node at first load call
    root = getNode();
    trie* trav = root;
    FILE* dict = fopen(dictionary, "r");
    char letters[46];
    int index = 0;
    int c;
    for (c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || c == '\'')
        {
            // Append character to word
            if(c == '\'')
            {
                c = '{';
            }
            char d = tolower(c);
            letters[index] = d;
            index++;

        }
        else if (index > 0)
        {
            // Terminate current word
            letters[index] = '\0';
            insert(trav, letters);
            // Update counter
            words++;

            // Prepare for next word
            index = 0;
        }
    }
    if(index>0)
    {
        letters[index] = '\0';
        insert(trav, letters);
        words++;
        index = 0;
    }
    // close dictionary
    fclose(dict);

    //return true if reach end of dictionary
    if(c == EOF)
        return true;

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    if(freeer(root))
        return true;

    return false;
}
