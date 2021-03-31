#include <stdio.h>

#include "UserOperations.h"
#include "Memory.h"
#include "Program.h"

void print(const int* command);

bool run_user_command(const int* command)
{
	if ((int)command[0] != PRINT) return false;

	print(command);
	return true;
}

void print(const int* command)
{
	int value = get_register((Register)command[1]);

	printf("PRINT: REG R%d = %d\n", (Register)command[1], value);
}
