#include "BranchingOperations.h"

#include <stddef.h>

#include "ComparisionChecker.h"
#include "Conversions.h"
#include "Program.h"
#include "StrUtils.h"

static bool is_branching(const char* instruction);
static void run(const char* instruction, const char** operands);

void (*get_branching_instruction(const char* instruction))(const char*, const char**)
{
	if (is_branching(instruction))
		return &run;
	return NULL;
}

static bool is_branching(const char* instruction)
{
	char* tests[] = { "BEQ", "BNE", "BGT", "BGE", "BLT", "BLE" };
	return str_contains(instruction, tests, 6);
}

static void run(const char* instruction, const char** operands)
{
	const int first = get_register_value_literal(operands[0]);
	const int second = get_register_value_literal(operands[1]);

	const int address = get_immediate_literal(operands[2]);
	
	if (compare_values(instruction, first, second))
		set_instruction_index(address);
}
