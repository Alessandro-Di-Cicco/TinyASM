#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ArithmeticOperations.h"
#include "Conversions.h"
#include "StrUtils.h"

static bool is_arithmetic(char* instruction);
static void run(char* instruction, char** operands);

void (*get_arithmetic_instruction(char* instruction))(char*, char**)
{
	if (is_arithmetic(instruction)) 
		return &run;
	return NULL;
}

static bool is_arithmetic(char* instruction)
{
	char* tests[] = { "ADD", "SUB", "MUL", "DIV" };
	return str_contains(instruction, tests, 4);
}

static void run(char* instruction, char** operands)
{
	const int first = get_register_value_literal(operands[1]);
	const int second = strlen(instruction) == 4
		             ? get_immediate_literal(operands[2])
		             : get_register_value_literal(operands[2]);
	const int destination = get_register_literal(operands[0]);

	if (strstr(instruction, "ADD"))
		set_register(destination, first + second);
	else if (strstr(instruction, "SUB"))
		set_register(destination, first - second);
	else if (strstr(instruction, "MUL"))
		set_register(destination, first * second);
	// todo: divide by zero check!
	else if (strstr(instruction, "DIV"))
		set_register(destination, first / second);
}
