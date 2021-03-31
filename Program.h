#ifndef PROGRAM_h
#define PROGRAM_h

typedef enum
{
	// Special
	END,		// Terminates the program
	PRINT,		// Print the value of the given register on screen
	
	// Setting
	SET,		// Set the content of the first operand (register) to the value of the second (register)
	SETI,		// Set the content of the first operand (register) to the value of the second (immediate)

	// Arithmetic
	ADD,		// Adds the content of the first op (register) with the second (register) and stores it in the third (register)
	SUB,		// Same as add, but for subtraction
	MUL,		// Same as add, but for multiplication
	DIV,		// Same as add, but for division
	
	ADDI,		// Adds the content of the first op (register) with the second (immediate) and stores it in the third (register)
	SUBI,		// Same as ADDI, but for subtraction

	// Logic
	AND,		// Bitwise AND of the first two registers operators (registers), stored in third (register)
	OR,			// Same as AND, but for the bitwise OR
	NOT,		// Performs the bitwise NOT of first operand's content (register) and stores it in the second (register)
	
	ANDI,		// Same as AND, but the second operator is an immediate instead of a register
	ORI,		// Same as ANDI, but for the bitwise OR

	// Conditional jump
	BEQ,		// Jump to the address specified as the third op if the two given operands (registers) are equal
	BNE,		// Jump to the address specified as the third op if the two given operands (registers) are not equal
	BGT,		// Same as BEQ, but the comparision is ">"
	BGE,		// Same as BGT, but equality is admitted as well
	BLT,		// Same as BEQ, but the comparision is "<"
	BLE,		// Same as BLT, but equality is admitted as well

	// Conditional set
	SEQ,		// Sets the third operand (register) to 1 if the first (register) is equal to the second (register), otherwise sets it to 0
	SNE,		// The opposite of SEQ
	SLT,		// Same as SEQ, but the comparision is op1<op2
	SLE,		// Same as SLT, but it admits equality as well

	SEQI,		// Same as SEQ, but the second operand is an immediate
	SNEI,		// Same as SNE, but the second operand is an immediate
	SLTI,		// Same as SLT, but the second operand is an immediate
	SLEI		// Same as SLE, but the second operand is an immediate
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
