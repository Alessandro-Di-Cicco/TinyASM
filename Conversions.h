#ifndef CONVERSIONS_h
#define CONVERSIONS_h

#include "Memory.h"

// Returns the register identified by the given literal
Register get_register_literal(char* name);
// Returns the contents of the register indicated by the passed literal
int get_register_value_literal(char* name);
// Converts an immediate to a value
int get_immediate_literal(char* literal);

#endif
