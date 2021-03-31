#include "BranchingOperations.h"
#include "Program.h"
#include "Memory.h"

void branch(const int* command);

bool run_branching_command(const int* command)
{
	switch (command[0])
	{
	case BEQ:
	case BNE:
	case BGT:
	case BGE:
	case BLT:
	case BLE:
		branch(command);
		return true;
	default:
		return false;
	}
}

void branch(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second = get_register((Register)command[2]);
	bool result;

	switch (command[0])
	{
	case BEQ:
		result = first == second;
		break;
	case BNE:
		result = first != second;
		break;
	case BGT:
		result = first > second;
		break;
	case BGE:
		result = first >= second;
		break;
	case BLT:
		result = first < second;
		break;
	case BLE:
		result = first <= second;
		break;
	}
	/* The value is -1 because, after this instruction finishes running, the runner will call
	 * move_to_next_instruction, advancing the index by another unit */
	if (result)
		set_instruction_index(command[3] - 1);
}
