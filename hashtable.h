#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdbool.h>

extern uint32_t MAX_INDEX_TABLE_SIZE;

typedef struct HashTable HashTable;
typedef struct Index Index;
typedef struct Value Value;
typedef struct Key Key;
typedef struct Node Node;

struct Node {
    struct Node* next;

    Key* key;
    Value* value;
};

struct Index {
    Node* head;
    uint32_t size;
}; 

struct Key {
    void* data;
    uint32_t size;
};

struct Value {
    void* data;
    uint32_t size;
};

struct HashTable {
    Index* index;

    uint32_t numberOfNodes;
    uint32_t collisions;
    bool canGrow;
};

HashTable* initHashTable();
void insert(HashTable* _hashtable, Key* key, Value* value);
Value* find(HashTable* _hashtable, Key* key);

#endif // !HASHTABLE_H
