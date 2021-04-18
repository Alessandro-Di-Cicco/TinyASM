#include <stdbool.h>

#include "LogicOperations.h"
#include "Memory.h"
#include "Program.h"

static void operation(const int* command);
static void not(const int* command);

bool run_logic_command(const int* command)
{
	switch (command[0])
	{
	case AND:
	case OR:
	case ANDI:
	case ORI:
		operation(command);
		return true;
	case NOT:
		not(command);
		return true;
	default:
		return false;
	}
}

// todo: naming this operation gives an error with aritmeticOperations.c that also defines operation()
// but neither of these can see the other, these should be internal functions, what's going on?
static void operation(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second =
		command[0] == ANDI || command[0] == ORI ?
		command[2] :
		get_register((Register)command[2]);

	int value;
	if (command[0] == ANDI || command[0] == AND)
		value = first & second;
	else value = first | second;

	set_register((Register)command[3], value);
}

static void not(const int* command)
{
	const int value = get_register((Register)command[1]);
	set_register((Register)command[2], ~value);
}
