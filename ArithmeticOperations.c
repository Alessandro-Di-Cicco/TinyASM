#include "ArithmeticOperations.h"

#include <stdio.h>

#include "Memory.h"
#include "Program.h"

void registers_operation(const int*);
void immediate_operation(const int*);

void operation(int first, int second, Instruction instruction, Register target);

bool run_arithmetic_command(const int* command)
{
	switch (command[0])
	{
	case ADD:
	case SUB:
	case MUL:
	case DIV:
		registers_operation(command);
		return true;
		
	case ADDI:
	case SUBI:
		immediate_operation(command);
		return true;
		
	default:
		return false;
	}
}

void registers_operation(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second = get_register((Register)command[2]);
	
	operation(first, second, command[0], command[3]);
}

void immediate_operation(const int* command)
{
	const int first = get_register((Register)command[1]);
	const int second = command[2];
	
	operation(first, second, command[0], command[3]);
}

void operation(int first, int second, Instruction instruction, Register target)
{
	int value;
	
	switch (instruction)
	{
	case ADD:
	case ADDI:
		value = first + second;
		break;
	case SUB:
	case SUBI:
		value = first - second;
		break;
	case MUL:
		value = first * second;
		break;
	case DIV:
		value = first / second;
		break;
	default:
		printf("ERROR: UNSUPPORTED OPERATION\n");
		return;
	}

	set_register(target, value);
}
