#include <stdio.h>
#include <string.h>

#include "MiscOperations.h"
#include "Conversions.h"
#include "Memory.h"

static void print(char* instruction, char** operands);

void (*get_misc_instruction(char* instruction))(char*, char**)
{
	printf("Evaluating print\n");
	if (strcmp(instruction, "PRINT") == 0) return &print;

	return NULL;
}

static void print(char* instruction, char** operands)
{
	const Register reg = get_register_literal(operands[0]);
	printf("R%d = %d\n", reg, get_register(reg));
}
