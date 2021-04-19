#include "LogicOperations.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "Conversions.h"
#include "StrUtils.h"

static bool is_logic(char* instruction);
static void run(char* instruction, char** operands);

void (*get_logic_instruction(char* instruction))(char*, char**)
{
	if (is_logic(instruction))
		return &run;
	return NULL;
}

static bool is_logic(char* instruction)
{
	char* tests[] = { "AND", "OR", "NOT" };
	if (str_contains(instruction, tests, 3))
	{
		printf("%s contains something for logic\n", instruction);
	}
	return str_contains(instruction, tests, 3);
}

static void run(char* instruction, char** operands)
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
