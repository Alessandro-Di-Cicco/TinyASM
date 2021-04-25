#ifndef STR_UTILS_h
#define STR_UTILS_h
#include <stdbool.h>

// Returns true if any of the strings in pool are contained in source
// The last parameter sets whether or not string that match but end with "I" are allowed
bool str_contains(const char* source, char** pool, int size, bool allowI);

#endif
