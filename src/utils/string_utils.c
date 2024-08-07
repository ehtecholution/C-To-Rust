#include "string_utils.h"
#include <string.h>

size_t hash_string(const char* str) {
    size_t hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int compare_string(const char* a, const char* b) {
    return strcmp(a, b);
}