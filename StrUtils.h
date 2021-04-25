#ifndef STR_UTILS_h
#define STR_UTILS_h
#include <stdbool.h>

// Returns true if any of the strings in pool are contained in source
bool str_contains(const char* source, char** pool, int size);

#endif
