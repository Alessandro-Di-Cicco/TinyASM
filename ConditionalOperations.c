#include "ConditionalOperations.h"

#include <stddef.h>

#include "Conversions.h"
#include "StrUtils.h"
#include "ComparisionChecker.h"

static bool is_conditional(const char* instruction);
static void run(const char* instruction, const char** operands);

void (*get_conditional_instruction(char* instruction))(const char*, const char**)
{
	if (is_conditional(instruction))
		return &run;
	return NULL;
}

static bool is_conditional(const char* instruction)
{
	char* tests[] = { "SEQ", "SNE", "SGT", "SGE", "SLT", "SLE" };
	return str_contains(instruction, tests, 6);
}

static void run(const char* instruction, const char** operands)
{
	const int first = get_register_value_literal(operands[1]);
	const int second = get_register_value_literal(operands[2]);

	const Register output = get_register_literal(operands[0]);

	if (compare_values(instruction, first, second))
		set_register(output, 1);
	else set_register(output, 0);
}
