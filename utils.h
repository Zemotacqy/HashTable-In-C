#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "hashtable.h"

uint32_t HashFunction(HashTable* _hashtable, Key* key);

void insertNodeIntoBeginning(HashTable* _hashtable, Node* element, Index* ptrToLL);

void insertIntoIndex(HashTable* _hashtable, Value* value, Key* key, uint32_t index);

Value* get(HashTable* _hashtable, Key* key, uint32_t index);

#endif // !UTILS_H
