#include "BranchingOperations.h"
#include "Program.h"
#include "Memory.h"

void branchEquals(const int* command);
void branchLowerEquals(const int* command);

bool run_branching_command(const int* command)
{
	switch (command[0])
	{
	case BEQ:
		branchEquals(command);
		return true;
	case BLE:
		branchLowerEquals(command);
		return true;
	default:
		return false;
	}
}

void branchEquals(const int* command)
{
	if (get_register(command[1]) == get_register(command[2]))
		/* sets to value - 1 because after this instruction is ran, the runner will call
		 * move_to_next, increasing it and reaching the actual desired instruction */
		set_instruction_index(command[3] - 1);
}

void branchLowerEquals(const int* command)
{
	if (get_register(command[1]) <= get_register(command[2]))
		/* sets to value - 1 because after this instruction is ran, the runner will call
		 * move_to_next, increasing it and reaching the actual desired instruction */
		set_instruction_index(command[3] - 1);
}
