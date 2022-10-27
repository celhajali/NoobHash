/* 
    Author: Christopher El-Hajali (GitHub: celhajali)
    File: main.c
    Description: A program that demonstrates the use of adding key/value pairs to a hash table and searching for a value associated with a key.
                 This limited hash table implementation allows a user to use only strings for keys and values.
*/

#include <stdio.h>
#include <string.h>
#include "MyHash.h"

#define TEST_1_FILE "KeyValPairsTest1.txt"
#define TEST_2_FILE "KeyValPairsTest2.txt"

int main()
{   
    Bucket *HashTable = InitializeTable();

    FILE *pTest1, *pTest2;

    pTest1 = fopen(TEST_1_FILE, "r");
    pTest2 = fopen(TEST_2_FILE, "r");

    char keyAndString[MAX_STRING*2];
    char key[MAX_STRING];
    char val[MAX_STRING];
    char *token;

    while ((!feof(pTest1)))
    {   
        fgets(keyAndString, MAX_STRING*2, pTest1);
        token = strtok(keyAndString, ",");
        strncpy(key, token, MAX_STRING);
        token = strtok(NULL, ",");
        strncpy(val, token, MAX_STRING);

        AddToTable(HashTable, key, val);
    }

    printf("\n\n");

    fseek(pTest1, 0L, SEEK_SET);

    while ((!feof(pTest1)))
    {    
        char *valForKey;
        fgets(keyAndString, MAX_STRING*2, pTest1);
        token = strtok(keyAndString, ",");
        strncpy(key, token, MAX_STRING);
        valForKey = GetValueFromTable(HashTable, key);
        printf("Key: %s, Value: %s\n", key, valForKey);
    }

    while ((!feof(pTest2)))
    {   
        fgets(keyAndString, MAX_STRING*2, pTest2);
        token = strtok(keyAndString, ",");
        strncpy(key, token, MAX_STRING);
        token = strtok(NULL, ",");
        strncpy(val, token, MAX_STRING);

        AddToTable(HashTable, key, val);
    }

    printf("\n\n");

    fseek(pTest2, 0L, SEEK_SET);

    while ((!feof(pTest2)))
    {    
        char *valForKey;
        fgets(keyAndString, MAX_STRING*2, pTest2);
        token = strtok(keyAndString, ",");
        strncpy(key, token, MAX_STRING);
        valForKey = GetValueFromTable(HashTable, key);
        printf("Key: %s, Value: %s\n", key, valForKey);
    }

    char *valForKey;
    
    valForKey = GetValueFromTable(HashTable, "key12");
    printf("\n");
    printf("Key: %s, Value: %s\n", "key12", valForKey);
    valForKey = GetValueFromTable(HashTable, "key13");
    printf("Key: %s, Value: %s\n", "key13", valForKey);
    valForKey = GetValueFromTable(HashTable, "key14");
    printf("Key: %s, Value: %s\n", "key14", valForKey);
    valForKey = GetValueFromTable(HashTable, "key15");
    printf("Key: %s, Value: %s\n", "key15", valForKey);


    fclose(pTest1);
    fclose(pTest2);

    return 0;

}