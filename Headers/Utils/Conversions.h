#ifndef CONVERSIONS_h
#define CONVERSIONS_h

#include "Memory.h"

// Returns the register identified by the given literal
Register get_register_literal(const char* name);
// Returns the contents of the register indicated by the passed literal
int get_register_value_literal(const char* name);
// Converts an immediate to a value
int get_immediate_literal(const char* literal);

#endif
