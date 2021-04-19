#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "InstructionSet.h"
#include "Memory.h"

static bool is_register(char* string);
static bool is_immediate(char* literal);

// Contains all the supported commands
InstructionInfo instructions[] = {
	// Setting
	{"SET", 2, {REGISTER, IMMEDIATE}},
	{"CPY", 2, {REGISTER, REGISTER}},
	
	// Arithmetic
	{"ADD", 3, {REGISTER, REGISTER, REGISTER}},
	{"ADDI", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"SUB", 3, {REGISTER, REGISTER, REGISTER}},
	{"SUBI", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"MUL", 3, {REGISTER, REGISTER, REGISTER}},
	{"MULI", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"DIV", 3, {REGISTER, REGISTER, REGISTER}},
	{"DIVI", 3, {REGISTER, REGISTER, IMMEDIATE}},

	// Branching
	{"BEQ", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"BNE", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"BGT", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"BGE", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"BLT", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"BLE", 3, {REGISTER, REGISTER, IMMEDIATE}},

	// Conditionals
	{"SEQ", 3, {REGISTER, REGISTER, REGISTER}},
	{"SNE", 3, {REGISTER, REGISTER, REGISTER}},
	{"SGT", 3, {REGISTER, REGISTER, REGISTER}},
	{"SGE", 3, {REGISTER, REGISTER, REGISTER}},
	{"SLT", 3, {REGISTER, REGISTER, REGISTER}},
	{"SLE", 3, {REGISTER, REGISTER, REGISTER}},

	// Logic
	{"AND", 3, {REGISTER, REGISTER, REGISTER}},
	{"OR", 3, {REGISTER, REGISTER, REGISTER}},
	{"NOT", 2, {REGISTER, REGISTER}},

	// Misc
	{"PRINT", 1, {REGISTER}}
};

InstructionInfo get_instruction_info(char* instruction)
{
	if (!instruction) return INVALID_INSTRUCTION;
	
	for (int i = 0, size = sizeof(instructions) / sizeof(InstructionInfo); i < size; i++)
	{
		if (strcmp(instruction, instructions[i].command) == 0)
			return instructions[i];
	}

	return INVALID_INSTRUCTION;
}

bool invalid_instruction(InstructionInfo* restrict instruction)
{
	return instruction->opNumber == -1;
}

bool is_operand_type(char* name, OperandType type)
{
	switch (type)
	{
	case REGISTER:
		return is_register(name);
	case IMMEDIATE:
		return is_immediate(name);
	default:
		puts("ERROR: INVALID TYPE PASSED TO isOperandType");
		return false;
	}
}

static bool is_register(char* string)
{
	if (strlen(string) != 2 || string[0] != 'R' || !isdigit(string[1])) return false;

	return strtol(string + 1, NULL, 10) < REGISTERS_COUNT;
}

static bool is_immediate(char* literal)
{
	while (*literal != '\0')
	{
		if (!isdigit(*literal)) return false;
		literal++;
	}

	return true;
}
