// HashTables.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct KeyValuePair {
    char* key;
    char* value;
    KeyValuePair* nextKVP;
} KeyValuePair;

typedef struct HashTable {
    KeyValuePair* Table[MAX_SIZE];
} HashTable;

char* searchValue (HashTable* ht, const char* key);
HashTable* createHashTable();
KeyValuePair* createKVP(const char* key, const char* value);
void insertKVPOverwrite(HashTable* hashTable, const char* key, const char* value);
void insertKVPChaining(HashTable* hashTable, const char* key, const char* value);
int hash(const char* key);


int main()
{
    HashTable* ht = createHashTable();
    insertKVPChaining(ht, "firstKey", "blue");
    insertKVPChaining(ht, "secondKey", "red");
    insertKVPChaining(ht, "Keyfirst", "green");
    char* value = searchValue(ht, "Keyfirst");
    char* valueTwo = searchValue(ht, "firstKey");
    return 0;
}

HashTable* createHashTable()
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht == NULL)
    {
        printf("low memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        ht->Table[i] = NULL;
    }
    return ht;
}

KeyValuePair* createKVP(const char* key, const char* value)
{
    KeyValuePair* KVP = (KeyValuePair*)malloc(sizeof KeyValuePair);
    if (KVP == NULL)
    {
        printf("low memory");
        exit(EXIT_FAILURE);
    }
    KVP->key = _strdup(key);
    KVP->value = _strdup(value);
    KVP->nextKVP = NULL;
    return KVP;
}

int hashKey(const char* key)
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = (hash + key[i]) % MAX_SIZE;
    }
    return hash;
}

char* searchValue(HashTable* ht, const char* key)
{
    int hashIndex = hashKey(key);
    char* response = (char*)"Key Not Found";
    if (ht->Table[hashIndex] != NULL)
    {
        KeyValuePair* current = ht->Table[hashIndex];
        while (current != NULL)
        {
            if (strcmp(current->key, key) == 0)
            {
                response = current->value;
            }
            //temp = ht->Table[hashIndex]->nextKVP;
            current = current->nextKVP;
        }
    }
    return response;
}
void insertKVPOverwrite(HashTable* ht, const char* key, const char* value)
{
    int hash = hashKey(key);
    if (ht->Table[hash] == NULL)
    {
        ht->Table[hash] = createKVP(key, value);
    }
    else
    {
        KeyValuePair* toFree = ht->Table[hash];
        ht->Table[hash] = createKVP(key, value);
        free(toFree);
    }
    return;
}

void insertKVPChaining(HashTable* ht, const char* key, const char* value)
{
    int hash = hashKey(key);
    KeyValuePair* toAdd = createKVP(key, value);
    if (ht->Table[hash] == NULL)
    {
        ht->Table[hash] = toAdd;
    }
    else
    {
        ht->Table[hash]->nextKVP = toAdd;
    }
    return;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
