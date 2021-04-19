#include "Memory.h"

int registers[REGISTERS_COUNT];

void set_register(Register reg, int value)
{
	registers[reg] = value;
}

int get_register(Register reg)
{
	return registers[reg];
}