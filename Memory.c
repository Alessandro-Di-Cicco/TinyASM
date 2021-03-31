#include <stdbool.h>
#include <stdio.h>

#include "Memory.h"
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
	switch (command[0])
	{
	case SETI:
		registers[command[1]] = command[2];
		#ifdef COMMAND_DUMP
			printf("Set register R%d to value %d\n", command[1], command[2]);
		#endif
		return true;
	case SET:
		registers[command[1]] = registers[command[2]];
		#ifdef COMMAND_DUMP
			printf("Set register R%d to value %d\n", command[1], registers[command[1]]);
		#endif
		return true;
	}
	
	return false;
}
