#include "Operations/BranchingOperations.h"

#include <string.h>

#include "Utils/ComparisionChecker.h"
#include "Utils/Conversions.h"
#include "Program.h"
#include "Utils/StrUtils.h"

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
	char* tests[] = { "BEQ", "BNE", "BGT", "BGE", "BLT", "BLE", "BRA" };
	return str_contains(instruction, tests, 7, false);
}

static void run(const char* instruction, const char** operands)
{
	if (strcmp(instruction, "BRA") == 0)
	{
		set_instruction_index(get_immediate_literal(operands[0]));
		return;
	}
	
	const int first = get_register_value_literal(operands[0]);
	const int second = get_register_value_literal(operands[1]);
	const int address = get_immediate_literal(operands[2]);
	
	if (compare_values(instruction, first, second))
		set_instruction_index(address);
}
