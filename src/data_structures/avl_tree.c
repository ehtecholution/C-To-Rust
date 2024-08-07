#include "avl_tree.h"
#include <stdlib.h>

static int avl_max(int a, int b) {
    return (a > b) ? a : b;
}

static int height(AVLNode* node) {
    return node ? node->height : 0;
}

static int get_balance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

static AVLNode* create_node(int key, void* value) {
    AVLNode* node = malloc(sizeof(AVLNode));
    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = avl_max(height(y->left), height(y->right)) + 1;
    x->height = avl_max(height(x->left), height(x->right)) + 1;

    return x;
}

static AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = avl_max(height(x->left), height(x->right)) + 1;
    y->height = avl_max(height(y->left), height(y->right)) + 1;

    return y;
}

static AVLNode* insert_node(AVLNode* node, int key, void* value, int (*compare)(const void*, const void*)) {
    if (node == NULL)
        return create_node(key, value);

    if (compare(&key, &node->key) < 0)
        node->left = insert_node(node->left, key, value, compare);
    else if (compare(&key, &node->key) > 0)
        node->right = insert_node(node->right, key, value, compare);
    else
        return node;

    node->height = 1 + avl_max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && compare(&key, &node->left->key) < 0)
        return right_rotate(node);

    if (balance < -1 && compare(&key, &node->right->key) > 0)
        return left_rotate(node);

    if (balance > 1 && compare(&key, &node->left->key) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && compare(&key, &node->right->key) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

AVLTree* avl_create(int (*compare)(const void*, const void*), void (*free_value)(void*)) {
    AVLTree* tree = malloc(sizeof(AVLTree));
    tree->root = NULL;
    tree->size = 0;
    tree->compare = compare;
    tree->free_value = free_value;
    return tree;
}

void avl_destroy(AVLTree* tree) {
    // Implementation omitted for brevity
}

int avl_insert(AVLTree* tree, int key, void* value) {
    tree->root = insert_node(tree->root, key, value, tree->compare);
    tree->size++;
    return 0;
}

void* avl_search(const AVLTree* tree, int key) {
    // Implementation omitted for brevity
    return NULL;
}

int avl_delete(AVLTree* tree, int key) {
    // Implementation omitted for brevity
    return 0;
}

static void traverse_inorder(AVLNode* node, void (*callback)(int key, void* value)) {
    if (node != NULL) {
        traverse_inorder(node->left, callback);
        callback(node->key, node->value);
        traverse_inorder(node->right, callback);
    }
}

void avl_traverse_inorder(const AVLTree* tree, void (*callback)(int key, void* value)) {
    traverse_inorder(tree->root, callback);
}