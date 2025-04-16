#include <stdio.h>
#include <stdlib.h>
// Implementing a HashMap using Chaining in C

// Define the hash function
int hash_function(int key, int size)
{
    return key % size;
}

// Define a node for the linked list (chaining)
typedef struct Node
{
    int key;
    int value;
    struct Node *next;
} Node;

// Define the HashMap structure
typedef struct HashMap
{
    Node **table;
    int size;
} HashMap;

// Create a new HashMap
HashMap *create_hashmap(int size)
{
    HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));
    if (!hashmap)
        return NULL;

    hashmap->size = size;
    hashmap->table = (Node **)calloc(size, sizeof(Node *));
    return hashmap;
}

// Insert a key-value pair into the hashmap
void insert(HashMap *hashmap, int key, int value)
{
    int index = hash_function(key, hashmap->size);

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    Node *current = hashmap->table[index];

    // If the slot is empty, insert directly
    if (current == NULL)
    {
        hashmap->table[index] = new_node;
    }
    else
    {
        // Otherwise, add to the end of the chain
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Delete a key-value pair by key
void delete(HashMap *hashmap, int key)
{
    int index = hash_function(key, hashmap->size);
    Node *current = hashmap->table[index];
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->key == key)
        {
            if (prev == NULL)
            {
                hashmap->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted successfully.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Key %d not found.\n", key);
}

// Search for a key and print its value
void search(HashMap *hashmap, int key)
{
    int index = hash_function(key, hashmap->size);
    Node *current = hashmap->table[index];

    while (current != NULL)
    {
        if (current->key == key)
        {
            printf("Key: %d, Value: %d\n", key, current->value);
            return;
        }
        current = current->next;
    }

    printf("Key %d not found.\n", key);
}

// Free all allocated memory
void destroy_hashmap(HashMap *hashmap)
{
    for (int i = 0; i < hashmap->size; i++)
    {
        Node *current = hashmap->table[i];
        while (current != NULL)
        {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(hashmap->table);
    free(hashmap);
}

// Demo
int main()
{
    HashMap *hashmap = create_hashmap(10);

    insert(hashmap, 1, 100);
    insert(hashmap, 2, 200);
    insert(hashmap, 12, 300); // Collision with key 2 (12 % 10 == 2)

    search(hashmap, 1);
    search(hashmap, 2);
    search(hashmap, 12);
    search(hashmap, 3); // Not found

    delete (hashmap, 2);
    search(hashmap, 2); // Deleted

    destroy_hashmap(hashmap);
    return 0;
}
