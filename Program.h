#ifndef PROGRAM_h
#define PROGRAM_h

typedef enum
{
	END,		// Terminates the program
	SET,		// Set content of a register
	ADD,		// Add first and second, store in third
	SUB,		// Same as add, but subtracting
	AND,		// Bitwise AND of the first two registers, stored in third
	BEQ,		// Jump to the address specified in the third op if the two given registers are equal
	BLE,		// Jump to the address specified in the third op if the first register is lower or equal to the second
	SLT,		// Set the third register to 1 if the first is lower than the second, otherwise set to 0
	SEQ,		// Same as above, but with equality
	PRINT,		// Print the value of the given register on screen
} Instruction;

/* Sets the program to run */
void set_program(int* src, int size);

/* Gets the current instruction, returns NULL if the program is beyond last instruction */
int* get_current_instruction(void);
/* Sets the pc to the value of the next instruction */
void move_to_next_instruction(void);

/* Return the number of the current instruction (not the token index!) */
int get_instruction_index(void);
/* Set the index of the next instruction to run */
void set_instruction_index(int);

#endif
