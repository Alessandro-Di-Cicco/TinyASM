#include "RegisterOperations.h"

#include <stdbool.h>
#include <stddef.h>

#include "Conversions.h"
#include "Memory.h"
#include "StrUtils.h"

static bool is_register_op(const char* instruction);
static void run(const char* instruction, const char** operands);

void (*get_register_instruction(char* instruction))(const char*, const char**)
{
	if (is_register_op(instruction))
		return &run;
	return NULL;
}

static bool is_register_op(const char* instruction)
{
	char* tests[] = { "SET", "CPY" };
	return str_contains(instruction, tests, 2);
}

static void run(const char* instruction, const char** operands)
{
	const Register target = get_register_literal(operands[0]);
	const int value = instruction[0] == 'S' ? get_immediate_literal(operands[1]) : get_register_value_literal(operands[1]);
	set_register(target, value);
}
