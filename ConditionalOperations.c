#include "ConditionalOperations.h"

#include <stddef.h>

#include "Conversions.h"
#include "Program.h"
#include "StrUtils.h"

static bool is_conditional(char* instruction);
static void run(char* instruction, char** operands);

void (*get_conditional_instruction(char* instruction))(char*, char**)
{
	if (is_conditional(instruction))
		return &run;
	return NULL;
}

static bool is_conditional(char* instruction)
{
	char* tests[] = { "SEQ", "SNE", "SGT", "SGE", "SLT", "SLE" };
	return str_contains(instruction, tests, 6);
}

static void run(char* instruction, char** operands)
{
	const int first = get_register_value_literal(operands[1]);
	const int second = get_register_value_literal(operands[2]);

	const Register output = get_register_literal(operands[0]);

	// todo: this is the copy of the branching operators implementation, find a way to re-use them
	if (instruction[2] == 'E' && instruction[1] != 'N' && first == second ||	// All the ones ending with E (except for SNE) admit equality
		instruction[1] == 'G' && first > second ||	// SGE, SGT
		instruction[1] == 'L' && first < second ||	// SLE, SLT
		instruction[1] == 'N' && first != second)	// SNE
	{
		set_register(output, 1);
	}
	else set_register(output, 0);
}
