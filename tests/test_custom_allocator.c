#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/memory/custom_allocator.h"

#define POOL_SIZE (1024 * 1024)  // 1 MB

void test_basic_allocation() {
    custom_allocator_init(POOL_SIZE);

    int* ptr1 = custom_malloc(sizeof(int));
    assert(ptr1 != NULL);
    *ptr1 = 42;

    char* ptr2 = custom_malloc(100);
    assert(ptr2 != NULL);
    strcpy(ptr2, "Hello, World!");

    assert(*ptr1 == 42);
    assert(strcmp(ptr2, "Hello, World!") == 0);

    custom_free(ptr1);
    custom_free(ptr2);

    custom_allocator_cleanup();
    printf("Basic allocation test passed.\n");
}

void test_reallocation() {
    custom_allocator_init(POOL_SIZE);

    int* ptr = custom_malloc(5 * sizeof(int));
    assert(ptr != NULL);

    for (int i = 0; i < 5; i++) {
        ptr[i] = i;
    }

    ptr = custom_realloc(ptr, 10 * sizeof(int));
    assert(ptr != NULL);

    for (int i = 0; i < 5; i++) {
        assert(ptr[i] == i);
    }

    for (int i = 5; i < 10; i++) {
        ptr[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        assert(ptr[i] == i);
    }

    custom_free(ptr);
    custom_allocator_cleanup();
    printf("Reallocation test passed.\n");
}

void test_fragmentation() {
    custom_allocator_init(POOL_SIZE);

    void* ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = custom_malloc(100);
        assert(ptrs[i] != NULL);
    }

    for (int i = 0; i < 100; i += 2) {
        custom_free(ptrs[i]);
    }

    void* large_ptr = custom_malloc(5000);
    assert(large_ptr != NULL);

    for (int i = 1; i < 100; i += 2) {
        custom_free(ptrs[i]);
    }

    custom_free(large_ptr);

    large_ptr = custom_malloc(POOL_SIZE - 1024);  // Should succeed after coalescing
    assert(large_ptr != NULL);

    custom_free(large_ptr);
    custom_allocator_cleanup();
    printf("Fragmentation test passed.\n");
}

void test_out_of_memory() {
    custom_allocator_init(1024);  // Small pool size

    void* ptr1 = custom_malloc(512);
    assert(ptr1 != NULL);

    void* ptr2 = custom_malloc(512);
    assert(ptr2 != NULL);

    void* ptr3 = custom_malloc(100);  // Should fail
    assert(ptr3 == NULL);

    custom_free(ptr1);
    custom_free(ptr2);

    ptr3 = custom_malloc(1000);  // Should succeed now
    assert(ptr3 != NULL);

    custom_free(ptr3);
    custom_allocator_cleanup();
    printf("Out of memory test passed.\n");
}

void test_stress() {
    custom_allocator_init(POOL_SIZE);

    void* ptrs[1000];
    for (int i = 0; i < 1000; i++) {
        size_t size = (rand() % 1000) + 1;
        ptrs[i] = custom_malloc(size);
        assert(ptrs[i] != NULL);
    }

    for (int i = 0; i < 1000; i += 2) {
        custom_free(ptrs[i]);
    }

    for (int i = 0; i < 500; i++) {
        size_t size = (rand() % 1000) + 1;
        void* ptr = custom_malloc(size);
        assert(ptr != NULL);
        custom_free(ptr);
    }

    for (int i = 1; i < 1000; i += 2) {
        custom_free(ptrs[i]);
    }

    custom_allocator_cleanup();
    printf("Stress test passed.\n");
}

int main() {
    test_basic_allocation();
    test_reallocation();
    test_fragmentation();
    test_out_of_memory();
    test_stress();

    printf("All custom allocator tests passed.\n");
    return 0;
}