#include <stdbool.h>
#include <stdio.h>

#include "Program.h"
#include "Memory.h"
#include "Parser.h"
#include "RegisterOperations.h"
#include "ArithmeticOperations.h"
#include "UserOperations.h"
#include "BranchingOperations.h"
#include "LogicOperations.h"
#include "ConditionalOperations.h"

#define CONSUMERS_COUNT 6

bool (*instructionConsumers[]) (const int*) = {
	run_register_command,
	run_arithmetic_command,
	run_user_command,
	run_branching_command,
	run_logic_command,
	run_conditional_command,
};

int main(void)
{
	// todo: replace printf with puts
	if (parseSource() == -1)
		printf("Parsing error\n");
	else printf("Parsing successful\n");
	
	/*
	int program[] = {
		SETI, R1, 2,
		SETI, R2, 2,
		
		SEQ, R1, R2, R3,	// R1 == R2 -> R3	true
		SLEI, R1, 2, R4,	// R1 <= 2	-> R4	true
		SLTI, R1, 2, R5,	// R1 < 2	-> R6	false
		SNE, R1, R6, R6,	// R1 != R6 -> R6	true
		
		PRINT, R0,
		
		END
	};

	// todo: make this not need the tokens number
	set_program(program, 50);
	
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

		if (instruction[0] == END)
		{
			printf("\nExecution terminated successfully.\n");
			break;
		}
	}*/

	printf("\n\n\n");
	return 0;
}
