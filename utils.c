#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

/*========================================Private============================================*/

uint32_t MAX_INDEX_TABLE_SIZE = 1000;

bool comparePtr(void* A, void* B, uint32_t size) {
    for(uint32_t i=0;i < size;i++) {
        if(*(char*)&A[i] != *(char*)&B[i]) return false;
    }
    return true;
}

Value* linearSearch(Node* ptrToLL, Key* key) {
    if(ptrToLL == NULL) return NULL;

    Node* iterator = ptrToLL;

    while(iterator != NULL) {
        if(iterator->key->size == key->size && comparePtr(key->data, iterator->key->data, key->size)) {
            return iterator->value;
        }
        iterator = iterator->next;
    }

    return NULL;
}

/*====================================Public====================================================*/

uint32_t HashFunction(HashTable* _hashtable, Key* key) {
    uint64_t sum = 0;
    const uint32_t R = 13;

    for(uint32_t i=0; i < key->size; i++) {
        sum = ( R * sum + (uint32_t)(*(char*)&key->data[i]) ) % MAX_INDEX_TABLE_SIZE;
    }

    return (sum % MAX_INDEX_TABLE_SIZE);
}

void insertNodeIntoBeginning(HashTable* _hashtable, Node* element, Index* ptrToLL) {

    if(ptrToLL->head == NULL) {
        ptrToLL->head = element;
    } else{
        Node* currHead = ptrToLL->head;
        ptrToLL->head = element;
        element->next = currHead;
        _hashtable->collisions += 1;
    }

    ptrToLL->size += 1;

    return;
}

void insertIntoIndex(HashTable* _hashtable, Value* _value, Key* _key, uint32_t index) {

    Index* ptrToIndex = &_hashtable->index[index];
    Node* element = malloc(sizeof(Node));

    element->next = NULL;
    
    element->key = _key;
    element->value = _value;

    insertNodeIntoBeginning(_hashtable, element, ptrToIndex);

    return;
}

Value* get(HashTable* _hashtable, Key* key, uint32_t index) {
    Index* ptrToIndex = &_hashtable->index[index];
    if(ptrToIndex->size == 0) return NULL;
    
    Node* ptrToLL = ptrToIndex->head;

    Value* result = linearSearch(ptrToLL, key);

    if(result == NULL) return NULL;
    else return result;
}
