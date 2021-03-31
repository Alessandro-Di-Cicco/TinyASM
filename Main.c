#include <stdbool.h>

// todo: find a way to get rid of this as well
#define CONSUMERS_COUNT 4

#include <stdio.h>

#include "Program.h"
#include "Memory.h"
#include "RegisterOperations.h"
#include "ArithmeticOperations.h"
#include "UserOperations.h"
#include "BranchingOperations.h"

bool (*instructionConsumers[]) (const int*) = {
	run_register_command,
	run_arithmetic_command,
	run_user_command,
	run_branching_command
};

int main(void)
{
	int program[] = {
		SET, R1, 0,
		SET, R7, 1,
		// Loop start
		SET, R0, 5,			// do {
		ADD, R1, R7, R1,	// R1++
		PRINT, R1,			// Print R1
		BLE, R1, R0, 2,		// } while (R1 < R0 = 5)
		
		END
	};

	// todo: make this not need the tokens number
	set_program(program, 20);
	
	int* instruction;
	// Instruction execution loop
	while ((instruction = get_current_instruction()))
	{
		int i;
		for (i = 0; i < CONSUMERS_COUNT; i++)
		{
			if ((*instructionConsumers[i])(instruction))
			{
				move_to_next_instruction();
				break;
			}
		}

		if (i == CONSUMERS_COUNT)
		{
			printf("ERROR: instruction at line %d is not identified", get_instruction_index());
			break;
		}
	}


	printf("\n\n\n");
	return 0;
}