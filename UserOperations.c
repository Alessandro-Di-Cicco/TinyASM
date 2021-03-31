#include <stdio.h>

#include "UserOperations.h"
#include "Memory.h"
#include "Program.h"

void print(const int* command);
void end(const int* command);


bool run_user_command(const int* command)
{
	switch (command[0])
	{
	case PRINT:
		print(command);
		return true;
	case END:
		end(command);
		return true;
	}
	return false;
}

void print(const int* command)
{
	int value = get_register((Register)command[1]);

	printf("PRINT: REG R%d = %d\n", (Register)command[1], value);
}

void end(const int* command)
{
	printf("\n\nEND OF EXECUTION, dumping\n");
	printf("R0\t\tR1\t\tR2\t\tR3\t\tR4\t\tR5\t\tR6\t\tR7\n");
	for (Register r = R0; r <= R7; r++)
	{
		printf("%0*d\t", 8, get_register(r));
	}
}
