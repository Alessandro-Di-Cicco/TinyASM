#ifndef BRANCHING_OPERATIONS_h
#define BRANCHING_OPERATIONS_h

#include <stdbool.h>

void (*get_branching_instruction(char* instruction))(char*, char**);

#endif
