#ifndef CUSTOM_ALLOCATOR_H
#define CUSTOM_ALLOCATOR_H

#include <stddef.h>

void* custom_malloc(size_t size);
void custom_free(void* ptr);
void* custom_realloc(void* ptr, size_t new_size);
void custom_allocator_init(size_t pool_size);
void custom_allocator_cleanup();

#endif // CUSTOM_ALLOCATOR_H