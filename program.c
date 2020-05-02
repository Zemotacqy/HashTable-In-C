#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"

char *rand_string(uint32_t size)
{
    char *str = (char*)malloc(sizeof(char)*size);

    // Make sure the set is large enough to facilitate random ordering.
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            uint32_t key = rand() % (uint32_t) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("USAGE:\tprogram <count_of_keys>\n");
        return 1;
    }

    const uint32_t SAMPLINGRETRIES = 10;
    uint32_t iterations = atoi(argv[1]);
    clock_t t;
    char* key;
    char* value;

    /* Initialize the data structure. */

    Key** keystore = malloc(sizeof(Key)*iterations);
    HashTable* hash = initHashTable();

    /* Insert Elements */

    uint32_t count = 0;
    while(count < iterations) {
        key = rand_string(20); value = rand_string(10);

        Key* _key = (Key*)malloc(sizeof(Key));
        _key->data = key; _key->size = strlen(key);

        Value* _value = (Value*)malloc(sizeof(Value));
        _value->data = value; _value->size = strlen(value);

        insert(hash, _key, _value);
        
        keystore[count] = _key;
        
        count++;
    }

    /* Fetch Elements */

    clock_t timeSum = 0;
    
    for(uint32_t i=0; i<SAMPLINGRETRIES ;i++) {

        uint32_t random_index = rand() % (uint32_t)( count );
        Key* randomKey = keystore[random_index];

        t = clock();
        Value* result = find(hash, randomKey);
        if(result == NULL) {
            printf("Not Found: %s\n", randomKey->data);
            exit(1);
        }
        t = clock() - t;
        timeSum += t;
    }

    /* Result Time */

    printf("Average fetch Time: %.2f ns\n", ((double)timeSum*1000000/(CLOCKS_PER_SEC * SAMPLINGRETRIES)));

    printf("%d Nodes, %d Collisions:\t%.2f%\n", hash->numberOfNodes, hash->collisions, (float)hash->collisions*100/hash->numberOfNodes);

    printf("Final Index Table Size: %d\n", MAX_INDEX_TABLE_SIZE);
    return 0;
}
