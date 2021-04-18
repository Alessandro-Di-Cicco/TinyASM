#include "InstructionSet.h"



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Memory.h"

static bool isRegister(char* string);
static bool isImmediate(char* literal);

// Contains all the supported commands
InstructionInfo instructions[] = {
	{"ADD", 3, {REGISTER, REGISTER, REGISTER}},
	{"ADDI", 3, {REGISTER, REGISTER, IMMEDIATE}},
	{"SUB", 3, {REGISTER, REGISTER, REGISTER}},
	{"SUBI", 3, {REGISTER, REGISTER, IMMEDIATE}}
};

InstructionInfo getInstructionInfo(char* instruction)
{
	for (int i = 0, size = sizeof(instructions) / sizeof(InstructionInfo); i < size; i++)
	{
		if (strcmp(instruction, instructions[i].command) == 0)
			return instructions[1];
	}

	return INVALID_INSTRUCTION;
}

bool invalidInstruction(InstructionInfo* restrict instruction)
{
	return instruction->opNumber == -1;
}

bool isOperandType(char* name, OperandType type)
{
	switch (type)
	{
	case REGISTER:
		return isRegister(name);
	case IMMEDIATE:
		return isImmediate(name);
	default:
		puts("ERROR: INVALID TYPE PASSED TO isOperandType");
	}
}

static bool isRegister(char* string)
{
	if (strlen(string) != 2 || string[0] != 'R' || !isdigit(string[1])) return false;

	return strtol(string + 1, NULL, 10) < REGISTERS_COUNT;
}

static bool isImmediate(char* literal)
{
	while (*literal != '\0')
	{
		if (!isdigit(*literal)) return false;
		literal++;
	}

	return true;
}
