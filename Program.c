#include <memory.h>
#include <stdlib.h>

#include "Program.h"

#include <stdio.h>

int pc;
int instructionIndex;
int programLength;
int* program;

/* Associates to each instruction the amount of operators that it accepts, to make pc manipulation
 * faster */
int operatorsAmount[] = {
	[SET] = 2,
	[ADD] = 3,
	[SUB] = 3,
	[AND] = 3,
	[BEQ] = 3,
	[BLE] = 3,
	[SLT] = 3,
	[SEQ] = 3,
	[PRINT] = 1,
	[END] = 0
};

void set_program(int* src, int size)
{
	free(program);
	pc = 0;
	instructionIndex = 0;

	program = malloc(sizeof(int) * size);
	if (!program)
		return;
	
	memcpy(program, src, sizeof(int) * size);
	programLength = size;
}

// todo: each single runner requests current instruction every time, this is not okay, it's bad for performance,
// they should receive a pointer set to const and run with it
int* get_current_instruction(void)
{
	if (pc >= programLength)
		return NULL;
	
	const int argNum = operatorsAmount[program[pc]];
	int* instruction = calloc(argNum + 1, sizeof(int));
	
	if (!instruction)
		return NULL;

	memcpy(instruction, program + pc, sizeof(int) * (argNum + 1));
	
	return instruction;
}

void move_to_next_instruction(void)
{
	const int argNum = operatorsAmount[program[pc]];
	pc += argNum + 1;
	instructionIndex++;
}

int get_instruction_index(void)
{
	return instructionIndex;
}

void set_instruction_index(int index)
{
	if (index < instructionIndex)
	{
		// todo: this could avoid re-starting and just move backwards (room for improvement here)
		pc = 0;
		instructionIndex = 0;
		for (int i = 0; i < index; i++)
			move_to_next_instruction();
	}
	// Doesn't restart from 0 if the instruction is ahead of the current one
	else
	{
		printf("Current index %d, target index %d\n", instructionIndex, index);
		while (instructionIndex < index)
			move_to_next_instruction();
	}
}
