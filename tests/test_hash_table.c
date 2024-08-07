#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../src/data_structures/hash_table.h"
#include "../src/utils/string_utils.h"

void test_hash_table_insert_and_search() {
    HashTable* ht = ht_create(10, hash_string, compare_string, free);
    
    ht_insert(ht, "key1", strdup("value1"));
    ht_insert(ht, "key2", strdup("value2"));
    ht_insert(ht, "key3", strdup("value3"));
    
    assert(strcmp(ht_search(ht, "key1"), "value1") == 0);
    assert(strcmp(ht_search(ht, "key2"), "value2") == 0);
    assert(strcmp(ht_search(ht, "key3"), "value3") == 0);
    assert(ht_search(ht, "key4") == NULL);
    
    ht_destroy(ht);
    printf("Hash table insert and search test passed.\n");
}

void test_hash_table_delete() {
    HashTable* ht = ht_create(10, hash_string, compare_string, free);
    
    ht_insert(ht, "key1", strdup("value1"));
    ht_insert(ht, "key2", strdup("value2"));
    ht_insert(ht, "key3", strdup("value3"));
    
    ht_delete(ht, "key2");
    assert(ht_search(ht, "key2") == NULL);
    assert(strcmp(ht_search(ht, "key1"), "value1") == 0);
    assert(strcmp(ht_search(ht, "key3"), "value3") == 0);
    
    ht_destroy(ht);
    printf("Hash table delete test passed.\n");
}

int main() {
    test_hash_table_insert_and_search();
    test_hash_table_delete();
    printf("All hash table tests passed.\n");
    return 0;
}