#include "ArithmeticOperations.h"
#include "Memory.h"
#include "Program.h"

void add(const int*);
void subtract(const int*);

bool run_arithmetic_command(const int* command)
{
	switch (command[0])
	{
	case ADD:
		add(command);
		return true;
	case SUB:
		return true;
	default:
		return false;
	}
}

void add(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second = get_register((Register)command[2]);
	set_register((Register)command[3], first + second);
}

void subtract(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second = get_register((Register)command[2]);
	set_register((Register)command[3], first - second);
}
