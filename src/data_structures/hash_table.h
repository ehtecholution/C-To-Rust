#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    size_t size;
    size_t count;
    size_t (*hash_func)(const char*);
    int (*compare)(const char*, const char*);
    void (*free_value)(void*);
} HashTable;

HashTable* ht_create(size_t size, size_t (*hash_func)(const char*), 
                     int (*compare)(const char*, const char*), void (*free_value)(void*));
void ht_destroy(HashTable* ht);
int ht_insert(HashTable* ht, const char* key, void* value);
void* ht_search(const HashTable* ht, const char* key);
int ht_delete(HashTable* ht, const char* key);
void ht_print(const HashTable* ht);

#endif // HASH_TABLE_H