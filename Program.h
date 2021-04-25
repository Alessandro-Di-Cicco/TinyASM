#ifndef PROGRAM_h
#define PROGRAM_h
#include <stdbool.h>

// Adds a new instruction to the program
void add_instruction(char* instruction, char** operands, int opCount);

// Set the index of the next instruction to run
void set_instruction_index(int value);

/* Runs the next instruction in the list, returning false if end of program reached
 must be called only once all the instructions have been added. Calling "add_instruction()"
 after run_next() has been called causes undefined behaviour */
bool run_next(void);

#endif
