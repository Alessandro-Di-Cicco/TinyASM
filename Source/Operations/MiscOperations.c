#include "Operations/MiscOperations.h"

#include <stdio.h>
#include <string.h>

#include "Utils/Conversions.h"
#include "Memory.h"

static void print(const char* instruction, const char** operands);

void (*get_misc_instruction(char* instruction))(const char*, const char**)
{
	if (strcmp(instruction, "PRINT") == 0) return &print;

	return NULL;
}

static void print(const char* instruction, const char** operands)
{
	const Register reg = get_register_literal(operands[0]);
	printf("R%d = %d\n", reg, get_register(reg));
}
