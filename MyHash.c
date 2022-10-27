/* 
    Author: Christopher El-Hajali (GitHub: celhajali)
    File: MyHash.c
    Description: Function definitions for function prototypes in MyHash.h
*/

#include "MyHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


void AddToTable(Bucket* table, char *key, char *newVal)
{
    
    int index;
    index = GenerateIndex(key); 
    if (ValIsEmpty(table[index].val))                // add the new val as the first entry in the bucket
    {
        strncpy(table[index].val, newVal, MAX_STRING-1);
        strncpy(table[index].keyUsed, key, MAX_STRING-1);
        table[index].pNext = NULL;
    }
    else                                            // it is not the only val associated with that index
    {
        Bucket *newNode = (Bucket*) malloc(sizeof(Bucket));
        strncpy(newNode->val, newVal, MAX_STRING-1);
        strncpy(newNode->keyUsed, key, MAX_STRING-1);
        Bucket *pSeek = &table[index];
        while (pSeek->pNext != NULL)   
        {      
            if (strncmp(pSeek->keyUsed, key, MAX_STRING) == 0)       // move to the end so we can add to the end. Replace if adding the same key again
            {
                newNode->pNext = pSeek->pNext;                      // hold the same pointer to the next node
                memcpy(pSeek, newNode, sizeof(Bucket)); // replace
                return;
            }                          
            pSeek = pSeek->pNext;
        }

        if (strncmp(pSeek->keyUsed, key, MAX_STRING) == 0)   // move to the end so we can add to the end. Replace if adding the same key again
        {       
                newNode->pNext = pSeek->pNext;               // hold the same pointer to the next node
                memcpy(pSeek, newNode, sizeof(Bucket));      // replace
        }  
        else
        {
            pSeek->pNext = newNode;
            newNode->pNext = NULL;      
        }
    }
}

int GenerateIndex(const char *str)
{   
    int i = 0;
    int sum = 0;
    int index;
    while (str[i] != '\0')
    {   
        sum = sum + (int) str[i];
        i++;
    }

    index = sum % TABLE_SIZE;
    return index;
}

char *GetValueFromTable(Bucket* table, char *key)
{
    int index = GenerateIndex(key);
    if (!(ValIsEmpty(table[index].val)))   // There have been values added here.
    {
        Bucket *pSeek = &table[index];
        while (pSeek->pNext != NULL)
        {
            if (strncmp(pSeek->keyUsed, key, MAX_STRING) == 0)
            {
                return pSeek->val;
            }
            pSeek = pSeek->pNext;
        }
        if (strncmp(pSeek->keyUsed, key, MAX_STRING) == 0)
        {
            return pSeek->val;
        }

        return NULL;         // if it was not found at the index
    }
    else
    {
        return NULL;        // no values at all for that key
    }
}

void InitializeString(char *str)                          // initializes all the bytes in the str to the null terminator char
{
    int i;
    for (i = 0; i < MAX_STRING; i++)
        str[i] = '\0';
}

Bucket* InitializeTable()
{
    Bucket *tableHead;
    if ((tableHead = (Bucket*) calloc(TABLE_SIZE, sizeof(Bucket))) == NULL)
    {
        printf("Space could not be allocated for a table of size %lu bytes.\n", TABLE_SIZE*sizeof(Bucket));
        exit(1);
    } 
    return tableHead;
}

bool ValIsEmpty(char *str)                                 // checks if all the bytes in the value for that bucket are still null chars
{
    int i;
    bool empty = true;
    for (i = 0; i < MAX_STRING; i++)
    {   
        if (str[i] != '\0')
            return false;
    }

    return empty;
}