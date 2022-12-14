/* 
    Author: Christopher El-Hajali (GitHub: celhajali)
    File: MyHash.h
    Description: A collection of function prototypes, preprocessor constants, and structs used by MyHash.c
*/

#ifndef MY_HASH_H
#define MY_HASH_H

#include <stdbool.h>

#define MAX_STRING 100      // Max length of a key and of a value. Change as needed.
#define TABLE_SIZE 10       // Change as needed

// Structure for each item that is needed to find the value associated with a key
typedef struct bucket{
    char keyUsed[MAX_STRING];
    char val[MAX_STRING];
    struct bucket *pNext;
} Bucket;

void AddToTable(Bucket* table, char *key, char *newVal);    // Adds a value to the table at the index generated by GenerateIndex(). If some value(s) exists, a next pointer to the new value will be created.

int GenerateIndex(const char *str);                         // return an index in the hash table to place the value at

char *GetValueFromTable(Bucket* table, char *key);          // Find the value associated with the key specified. Return NULL is a value is not found.

void InitializeString(char *str);                           // initializes all the bytes in the str to the null terminator char

Bucket* InitializeTable();                                  // Creates a table with the size of one bucket.

bool ValIsEmpty(char *str);                                 // checks if all the bytes in the value for that bucket are still null chars

#endif