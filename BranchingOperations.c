#include <stddef.h>

#include "BranchingOperations.h"

#include <stdio.h>

#include "Conversions.h"
#include "Program.h"
#include "StrUtils.h"

static bool is_branching(char* instruction);
static void run(char* instruction, char** operands);

void (*get_branching_instruction(char* instruction))(char*, char**)
{
	if (is_branching(instruction))
		return &run;
	return NULL;
}

static bool is_branching(char* instruction)
{
	char* tests[] = { "BEQ", "BNE", "BGT", "BGE", "BLT", "BLE" };
	return str_contains(instruction, tests, 6);
}

static void run(char* instruction, char** operands)
{
	const int first = get_register_value_literal(operands[0]);
	const int second = get_register_value_literal(operands[1]);

	const int address = get_immediate_literal(operands[2]);
	if ((instruction[2] == 'E' && instruction[1] != 'N' || instruction[2] == 'Q') && first == second ||	// All the ones ending with E (except for BNE) admit equality
		instruction[1] == 'G' && first > second ||	// BGE, BGT
		instruction[1] == 'L' && first < second ||	// BLE, BLT
		instruction[1] == 'N' && first != second)	// BNE
	{
		set_instruction_index(address);
	}
}
