/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// function prototype
int hash(char* word);

// define linked list node
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// declare hashtable (an array of node pointers to linked lists)
node* hashtable[HASHTABLE_SIZE];

// word counter
int words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // make a copy of word 
    char word_copy[strlen(word)];
    strcpy(word_copy, word);
    
    // make word all lower case
    for(int i = 0; i < strlen(word_copy); i++)
    {
        if (isupper(word_copy[i]))   
            word_copy[i] = tolower(word_copy[i]);
        // if (word_copy[i] == '\'' || islower(word_copy[i]))    
        else
            word_copy[i] = word_copy[i]; 
    }    
    
    //printf("word: %s; copy: %s, length is: %d\n", word, word_copy, strlen(word));
    
    // find in which bucket the word is 
    node* bucket = hashtable[hash(word_copy)];
    
    // abort if list is empty
    if (bucket == NULL) 
        {
            //printf("Linked list [%d] is empty.\n", hash(word_copy));
            return false;
        }
        
    // otherwise traverse the linked list    
    else
    {
        // traversal pointer
        node* crawler = bucket;
        
        // until the end of the list
        //while(crawler->next != NULL)
        while(crawler)
        {
            //printf("Checking %s against %s\n", word_copy, crawler->word);   
            // return true if matching word found
            if(strcmp(word_copy, crawler->word) == 0)
                return true; 
            
            
            // keep traversing the list
            crawler = crawler->next;
                          
        }
    }
    // return false if word is not in dictionary
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // define linked lists inside hashtable
    for(int i = 0; i < HASHTABLE_SIZE; i++)
        hashtable[i] = NULL;
        
    // allocate memory for first word
    node* new_node= malloc(sizeof(node)); 
    if (new_node == NULL)
        return false; 
    
    // open dictionary file
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
     
    // iterate over each word in the dictionary
    while(fscanf(file, "%s", new_node->word)!= EOF)
    {
    
        //printf("\nWord is: %s, length is %d", new_node->word, strlen(new_node->word));
        //hash the word
        int ind = hash(new_node->word);
        
        // insert word into the head of linked list 
        if (hashtable[ind] == NULL) // if list is empty
        {
            new_node->next = NULL;
            hashtable[ind] = new_node;
            //printf("word No %d is loaded as: %s.\n", words, new_node->word);
        }    
        else
        {
            new_node->next = hashtable[ind];
            hashtable[ind] = new_node;
            //printf("word No %d is loaded as: %s.\n", words, new_node->word);
        }
        words++;
        //printf("words loaded: %d\n\n", words);
        
        // allocate memory for all words after first word
        new_node = malloc(sizeof(node)); 
        if (new_node == NULL)
            return false;
    }
    // free last
    free(new_node);
    
    // print hash table
    /*
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        printf("\nwords in bucket %d: ", i);
        for (node* n = hashtable[i]; n != NULL; n = n->next)
            printf("%s, ", n->word);
    }  
    */ 
    
    // close dictionary file
    fclose(file);
    
    if (words != 0)
        return true;
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // number of words loaded in hashtable
    if (words != 0)
        return words;
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // free all nodes inside the hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
        for (node* n = hashtable[i]; n != NULL; n = n->next)
        {
            if(n)
                free(n);
            else
                return false;
        }        
    return true;
}

// hash function
int hash(char* word)
{
    char f_letter = word[0];
    int index;
    
    //printf("word: %s\n", word);
    //printf("f_letter: %c\n", f_letter);
    
    // get index of bucket in hashtable
    switch(f_letter)
    {
        case 'a':
        case 'b':
            index = 0;
            break;
        case 'c':
            index = 1;
            break;    
        case 'd':
        case 'e':
            index = 2;
            break;
        case 'f':
        case 'g':
        case 'h':
            index = 3;
            break;
        case 'i':
        case 'j':
        case 'k':
        case 'l':
            index = 4;
            break;
        case 'm':
        case 'n':
        case 'o':
            index = 5;
            break;
        case 'p':
        case 'q':
            index = 6; 
            break; 
        case 'r':
        case 't':
            index = 7; 
            break;  
        case 's':
            index = 8; 
            break;
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            index = 9;   
            break;
    }
    //printf("index: %d\n", index);
    return index;
}

