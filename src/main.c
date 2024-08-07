#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures/avl_tree.h"
#include "data_structures/hash_table.h"
#include "algorithms/sorting.h"
#include "utils/string_utils.h"

void print_int(int key, void* value) {
    printf("%d: %s\n", key, (char*)value);
}

int compare_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void free_string(void* value) {
    free(value);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "avl") == 0) {
        AVLTree* tree = avl_create(compare_int, free_string);
        avl_insert(tree, 5, strdup("five"));
        avl_insert(tree, 3, strdup("three"));
        avl_insert(tree, 7, strdup("seven"));
        avl_insert(tree, 1, strdup("one"));
        avl_insert(tree, 9, strdup("nine"));

        printf("AVL Tree contents:\n");
        avl_traverse_inorder(tree, print_int);

        avl_delete(tree, 3);
        printf("\nAfter deleting 3:\n");
        avl_traverse_inorder(tree, print_int);

        avl_destroy(tree);
    } else if (strcmp(argv[1], "hash") == 0) {
        HashTable* ht = ht_create(10, hash_string, compare_string, free_string);
        ht_insert(ht, "key1", strdup("value1"));
        ht_insert(ht, "key2", strdup("value2"));
        ht_insert(ht, "key3", strdup("value3"));

        printf("Hash Table contents:\n");
        ht_print(ht);

        char* value = ht_search(ht, "key2");
        if (value) {
            printf("\nValue for key2: %s\n", value);
        }

        ht_delete(ht, "key1");
        printf("\nAfter deleting key1:\n");
        ht_print(ht);

        ht_destroy(ht);
    } else if (strcmp(argv[1], "sort") == 0) {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);

        printf("Original array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        quicksort(arr, 0, n - 1);

        printf("Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}