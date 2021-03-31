#include "ConditionalOperations.h"
#include "Program.h"
#include "Memory.h"

void execute_operation(const int* command);
void get_values(int* result, const int* command);
void evaluate_operation(int first, int second, Instruction instruction, Register target);

bool run_conditional_command(const int* command)
{
	// todo: use this approach on all the modules
	if (command[0] < SEQ || command[0] > SLEI) return false;

	execute_operation(command);
	return true;
}

void execute_operation(const int* command)
{
	int values[2];
	get_values(values, command);
	evaluate_operation(values[0], values[1], (Instruction)command[0], (Register)command[3]);
}

void get_values(int* result, const int* command)
{
	result[0] = get_register((Register)command[1]);
	result[1] = command[0] < SEQI ? get_register((Register)command[2]) : command[2];
}

void evaluate_operation(int first, int second, Instruction instruction, Register target)
{
	int result;

	switch (instruction)
	{
	case SEQ:
	case SEQI:
		result = first == second;
		break;
	case SNE:
	case SNEI:
		result = first != second;
		break;
	case SLT:
	case SLTI:
		result = first < second;
		break;
	case SLE:
	case SLEI:
		result = first <= second;
		break;
	}

	set_register(target, result);
}
