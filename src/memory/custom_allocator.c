#include "custom_allocator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ALIGN(size) (((size) + (sizeof(size_t) - 1)) & ~(sizeof(size_t) - 1))
#define HEADER_SIZE sizeof(struct block_header)

struct block_header {
    size_t size;
    int is_free;
    struct block_header* next;
};

static struct block_header* head = NULL;
static size_t total_size = 0;

void custom_allocator_init(size_t pool_size) {
    if (head != NULL) {
        fprintf(stderr, "Allocator already initialized\n");
        return;
    }
    total_size = pool_size;
    head = (struct block_header*)malloc(pool_size);
    if (head == NULL) {
        fprintf(stderr, "Failed to initialize memory pool\n");
        exit(1);
    }
    head->size = pool_size - HEADER_SIZE;
    head->is_free = 1;
    head->next = NULL;
}

void custom_allocator_cleanup() {
    free(head);
    head = NULL;
    total_size = 0;
}

static struct block_header* find_free_block(struct block_header** last, size_t size) {
    struct block_header* current = head;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

static struct block_header* request_space(struct block_header* last, size_t size) {
    struct block_header* block;
    block = (struct block_header*)((char*)last + HEADER_SIZE + last->size);
    block->size = size;
    block->is_free = 0;
    block->next = NULL;
    if (last != NULL) {
        last->next = block;
    }
    return block;
}

void* custom_malloc(size_t size) {
    size_t aligned_size = ALIGN(size);
    struct block_header* block;

    if (head == NULL) {
        fprintf(stderr, "Allocator not initialized\n");
        return NULL;
    }

    if (size <= 0) {
        return NULL;
    }

    struct block_header* last = head;
    block = find_free_block(&last, aligned_size);

    if (block == NULL) {
        // No free block found, try to expand the last block
        block = request_space(last, aligned_size);
        if (block == NULL) {
            return NULL;
        }
    } else {
        // Found a free block
        block->is_free = 0;
        if (block->size > aligned_size + HEADER_SIZE) {
            struct block_header* new_block = (struct block_header*)((char*)block + HEADER_SIZE + aligned_size);
            new_block->size = block->size - aligned_size - HEADER_SIZE;
            new_block->is_free = 1;
            new_block->next = block->next;
            block->size = aligned_size;
            block->next = new_block;
        }
    }

    return (void*)(block + 1);
}

void custom_free(void* ptr) {
    if (ptr == NULL) return;

    struct block_header* block = (struct block_header*)ptr - 1;
    block->is_free = 1;

    // Merge with next block if it's free
    if (block->next && block->next->is_free) {
        block->size += HEADER_SIZE + block->next->size;
        block->next = block->next->next;
    }

    // Attempt to merge with previous block if it's free
    struct block_header* current = head;
    while (current != block && current != NULL) {
        if (current->is_free && (struct block_header*)((char*)current + HEADER_SIZE + current->size) == block) {
            current->size += HEADER_SIZE + block->size;
            current->next = block->next;
            break;
        }
        current = current->next;
    }
}

void* custom_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) {
        return custom_malloc(new_size);
    }

    struct block_header* block = (struct block_header*)ptr - 1;
    if (block->size >= new_size) {
        return ptr;
    }

    void* new_ptr = custom_malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, block->size);
    custom_free(ptr);
    return new_ptr;
}

void custom_allocator_stats() {
    struct block_header* current = head;
    int total_blocks = 0;
    int free_blocks = 0;
    size_t largest_free_block = 0;
    size_t total_free_memory = 0;

    while (current != NULL) {
        total_blocks++;
        if (current->is_free) {
            free_blocks++;
            total_free_memory += current->size;
            if (current->size > largest_free_block) {
                largest_free_block = current->size;
            }
        }
        current = current->next;
    }

    printf("Allocator Stats:\n");
    printf("Total blocks: %d\n", total_blocks);
    printf("Free blocks: %d\n", free_blocks);
    printf("Largest free block: %zu bytes\n", largest_free_block);
    printf("Total free memory: %zu bytes\n", total_free_memory);
    printf("Total memory: %zu bytes\n", total_size);
}