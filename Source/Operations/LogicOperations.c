#include "Operations/LogicOperations.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "Utils/Conversions.h"
#include "Utils/StrUtils.h"

static bool is_logic(const char* instruction);
static void run(const char* instruction, const char** operands);

void (*get_logic_instruction(const char* instruction))(const char*, const char**)
{
	if (is_logic(instruction))
		return &run;
	return NULL;
}

// todo: this checks are imperfect, they need to consider strlen too, change implementation of str_contains
static bool is_logic(const char* instruction)
{
	char* tests[] = { "AND", "OR", "NOT" };
	return str_contains(instruction, tests, 3, false);
}

static void run(const char* instruction, const char** operands)
{
	const int first = get_register_value_literal(operands[1]);
	int second;
	const Register output = get_register_literal(operands[0]);
	
	switch (instruction[0])
	{
	case 'A':
		second = get_register_value_literal(operands[2]);
		set_register(output, first & second);
		break;
	case 'O':
		second = get_register_value_literal(operands[2]);
		set_register(output, first | second);
		break;
	case 'N':
		set_register(output, ~first);
		break;
	}
}
