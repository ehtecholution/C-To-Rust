#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h>

typedef struct AVLNode {
    int key;
    void* value;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

typedef struct {
    AVLNode* root;
    size_t size;
    int (*compare)(const void*, const void*);
    void (*free_value)(void*);
} AVLTree;

AVLTree* avl_create(int (*compare)(const void*, const void*), void (*free_value)(void*));
void avl_destroy(AVLTree* tree);
int avl_insert(AVLTree* tree, int key, void* value);
void* avl_search(const AVLTree* tree, int key);
int avl_delete(AVLTree* tree, int key);
void avl_traverse_inorder(const AVLTree* tree, void (*callback)(int key, void* value));

#endif // AVL_TREE_H