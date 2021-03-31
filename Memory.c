#include <stdbool.h>

#include "Memory.h"

#include <stdio.h>


#include "Program.h"
#include "RegisterOperations.h"
#include "RunSettings.h"

int registers[REGISTERS_COUNT];

void set_register(Register reg, int value)
{
	registers[reg] = value;
}

int get_register(Register reg)
{
	return registers[reg];
}

bool run_register_command(const int* command)
{
	if (command[0] != SET) return false;

	registers[command[1]] = command[2];

	#ifdef COMMAND_DUMP
	printf("Set register R%d to value %d\n", command[1], command[2]);
	#endif
	
	return true;
}
