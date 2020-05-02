#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "hashtable.h"
#include "utils.h"

/*=================================Private============================================*/

bool toGrow(HashTable* _hashtable) {
    if( _hashtable->canGrow && (float)_hashtable->numberOfNodes/MAX_INDEX_TABLE_SIZE >= 1) return true;
    else return false;
}

uint32_t getNewSize(uint32_t oldSize) {
    uint64_t newSize = oldSize * 2;
    if(newSize >= INT_MAX) {
        printf("Could not fit into 32 bit integer.");
        exit(1);
    }
    return (uint32_t)newSize;
}

void initIndexTable(HashTable* _hashtable, uint32_t lowerBound, uint32_t upperBound) {
    for(uint32_t i=lowerBound; i < upperBound; i++) {
        (&_hashtable->index[i])->head = NULL;
        (&_hashtable->index[i])->size = 0;
    }
    return;
}

void reIndexTable(HashTable* _hashtable, uint32_t oldSize) {
    Index* ptrToIndex = _hashtable->index;
    _hashtable->collisions = 0;

    // Traverse only till the point which has old nodes present
    for(uint32_t i=0; i < oldSize; i++) {
        Node* curr = (&ptrToIndex[i])->head;

        // detach the LL from the Index Table
        (&ptrToIndex[i])->head = NULL;
        (&ptrToIndex[i])->size = 0;

        uint32_t count = 0;
        Node* prev = NULL;

        // Traverse the Detached LL and insert them to Hash Table again
        while(curr != NULL) {
            prev = curr;
            insert(_hashtable, prev->key, prev->value);
            curr = curr->next;

            // Make it a dangling Pointer so that it's picked up by garbage collector.
            // Somehow, using free(prev) deletes it's associated objects also, leading
            // to object not found.
            prev->next = NULL;
            _hashtable->numberOfNodes -= 1;
        }
    }
    return;
}

uint32_t growHashTable(HashTable* _hashtable) {
    uint32_t oldSize = MAX_INDEX_TABLE_SIZE;
    uint32_t newSize = getNewSize(MAX_INDEX_TABLE_SIZE);

    _hashtable->index = realloc(_hashtable->index, sizeof(Index) * newSize);
    if(_hashtable->index == NULL) {
        printf("Memory allocation Error");
        exit(1);
    }

    initIndexTable(_hashtable, MAX_INDEX_TABLE_SIZE, newSize);
    MAX_INDEX_TABLE_SIZE = newSize;
    _hashtable->canGrow = false;

    // This is needed because after growing the hashtable, it may be possible,
    // that existing keys are not mapped to the same index.
    reIndexTable(_hashtable, oldSize);

    _hashtable->canGrow = true;
    return 0;
}

/*=================================Public===============================================*/

void insert(HashTable* _hashtable, Key* key, Value* value) {
    if(toGrow(_hashtable) && growHashTable(_hashtable) !=0) {
        printf("Could not grow HashTable");
        exit(1);
    }
    
    uint32_t index = HashFunction(_hashtable, key);

    insertIntoIndex(_hashtable, value, key, index);
    _hashtable->numberOfNodes += 1;
    
    return;
}

Value* find(HashTable* _hashtable, Key* key) {
    uint32_t index = HashFunction(_hashtable, key);

    return get(_hashtable, key, index);
}

HashTable* initHashTable(){
    HashTable* _hashtable = malloc(sizeof(HashTable));

    _hashtable->index = (Index* )malloc(sizeof(Index) * MAX_INDEX_TABLE_SIZE);

    initIndexTable(_hashtable, 0, MAX_INDEX_TABLE_SIZE);

    _hashtable->numberOfNodes = 0;
    _hashtable->collisions = 0;
    _hashtable->canGrow = true;

    return _hashtable;
}
