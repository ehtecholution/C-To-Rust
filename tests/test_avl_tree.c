#include <stdio.h>
#include <assert.h>
#include "../src/data_structures/avl_tree.h"

static int compare_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

static void free_int(void* value) {
    free(value);
}

void test_avl_insert_and_search() {
    AVLTree* tree = avl_create(compare_int, free_int);
    
    int values[] = {5, 3, 7, 1, 9, 2, 8, 4, 6};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        int* value = malloc(sizeof(int));
        *value = values[i];
        avl_insert(tree, values[i], value);
    }
    
    for (int i = 0; i < n; i++) {
        int* found = (int*)avl_search(tree, values[i]);
        assert(found != NULL && *found == values[i]);
    }
    
    int not_in_tree = 10;
    assert(avl_search(tree, not_in_tree) == NULL);
    
    avl_destroy(tree);
    printf("AVL insert and search test passed.\n");
}

void test_avl_delete() {
    AVLTree* tree = avl_create(compare_int, free_int);
    
    int values[] = {5, 3, 7, 1, 9, 2, 8, 4, 6};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        int* value = malloc(sizeof(int));
        *value = values[i];
        avl_insert(tree, values[i], value);
    }
    
    avl_delete(tree, 3);
    assert(avl_search(tree, 3) == NULL);
    
    avl_delete(tree, 5);
    assert(avl_search(tree, 5) == NULL);
    
    for (int i = 0; i < n; i++) {
        if (values[i] != 3 && values[i] != 5) {
            int* found = (int*)avl_search(tree, values[i]);
            assert(found != NULL && *found == values[i]);
        }
    }
    
    avl_destroy(tree);
    printf("AVL delete test passed.\n");
}

int main() {
    test_avl_insert_and_search();
    test_avl_delete();
    printf("All AVL tree tests passed.\n");
    return 0;
}