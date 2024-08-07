#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HashTable* ht_create(size_t size, size_t (*hash_func)(const char*), 
                     int (*compare)(const char*, const char*), void (*free_value)(void*)) {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->buckets = calloc(size, sizeof(HashNode*));
    ht->hash_func = hash_func;
    ht->compare = compare;
    ht->free_value = free_value;
    return ht;
}

void ht_destroy(HashTable* ht) {
    // Implementation omitted for brevity
}

int ht_insert(HashTable* ht, const char* key, void* value) {
    size_t index = ht->hash_func(key) % ht->size;
    HashNode* new_node = malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->count++;
    return 0;
}

void* ht_search(const HashTable* ht, const char* key) {
    size_t index = ht->hash_func(key) % ht->size;
    HashNode* node = ht->buckets[index];
    while (node != NULL) {
        if (ht->compare(key, node->key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

int ht_delete(HashTable* ht, const char* key) {
    // Implementation omitted for brevity
    return 0;
}

void ht_print(const HashTable* ht) {
    for (size_t i = 0; i < ht->size; i++) {
        HashNode* node = ht->buckets[i];
        while (node != NULL) {
            printf("%s: %s\n", node->key, (char*)node->value);
            node = node->next;
        }
    }
}