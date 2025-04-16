#include <stdio.h>
#include <stdlib.h>
// Implementing a HashMap using Double Hashing in C

int hash_function_1(int key, int size)
{
    return key % size;
}

int hash_function_2(int key, int size, int attempt)
{
    return (hash_function_1(key, size) + attempt * (1 + (key % (size - 1)))) % size;
}

typedef struct Node
{
    int key;
    int value;
} Node;

typedef struct HashMap
{
    Node *table;
    int size;
} HashMap;

HashMap *create_hashmap(int size)
{
    HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));
    if (!hashmap)
        return NULL;

    hashmap->size = size;
    hashmap->table = (Node *)calloc(size, sizeof(Node));
    return hashmap;
}

void insert(HashMap *hashmap, int key, int value)
{
    int index, attempt = 0;
    do
    {
        index = hash_function_2(key, hashmap->size, attempt);
        if (hashmap->table[index].key == 0)
        { // Empty slot
            hashmap->table[index].key = key;
            hashmap->table[index].value = value;
            return;
        }
        attempt++;
    } while (attempt < hashmap->size);
    printf("HashMap is full. Cannot insert key %d.\n", key);
}

void delete_key(HashMap *hashmap, int key)
{
    int index, attempt = 0;
    do
    {
        index = hash_function_2(key, hashmap->size, attempt);
        if (hashmap->table[index].key == key)
        {                                  // Key found
            hashmap->table[index].key = 0; // Mark as deleted
            return;
        }
        attempt++;
    } while (attempt < hashmap->size);
    printf("Key %d not found.\n", key);
}

void search(HashMap *hashmap, int key)
{
    int index, attempt = 0;
    do
    {
        index = hash_function_2(key, hashmap->size, attempt);
        if (hashmap->table[index].key == key)
        { // Key found
            printf("Key: %d, Value: %d\n", key, hashmap->table[index].value);
            return;
        }
        attempt++;
    } while (attempt < hashmap->size);
    printf("Key %d not found.\n", key);
}

void destroy_hashmap(HashMap *hashmap)
{
    free(hashmap->table);
    free(hashmap);
}

int main()
{
    HashMap *hashmap = create_hashmap(10);
    if (!hashmap)
    {
        printf("Failed to create HashMap.\n");
        return 1;
    }

    insert(hashmap, 1, 100);
    insert(hashmap, 2, 200);
    insert(hashmap, 12, 300); // Collision with key 2

    search(hashmap, 1);
    search(hashmap, 2);
    search(hashmap, 12);

    delete_key(hashmap, 2);
    search(hashmap, 2); // Should not be found

    destroy_hashmap(hashmap);
    return 0;
}