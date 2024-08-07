#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

size_t hash_string(const char* str);
int compare_string(const char* a, const char* b);

#endif // STRING_UTILS_H