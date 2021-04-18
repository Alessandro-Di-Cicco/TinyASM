#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Parser.h"
#include "InstructionSet.h"

#define COMMENT_TOKEN '#'

static int generateToken(char* string);

int parseSource()
{
	FILE** file = malloc(sizeof(FILE*));
	if (!file)
	{
		puts("Error, could not read file");
		return -1;
	}

	// This returns 0 on success
	errno_t error = fopen_s(file, "source.tsm", "r");
	if (error || !*file)
	{
		printf("Error opening the file\n");
		return -1;
	}

	char* line = malloc(sizeof(char) * 256);
	if (!line)
	{
		puts("Error allocating memory");
		return -1;
	}

	int lineCounter = 0;
	while (!feof(*file))
	{
		// todo: have this count each line length by scanning the file through getc(), allowing unlimited line length
		if (!fgets(line, 256, *file) && feof(*file))
			puts("END OF FILE");
		else
		{
			lineCounter++;
			// Parsing error
			if (generateToken(line))
			{
				printf("Error at line %d\n", lineCounter);
				exit(-1);
			}
		}

		puts("\n");
	}

	puts("");
	return 0;
} // parseSource()


static int generateToken(char* string)
{
	// Initializes context for strtok
	char** context = malloc(sizeof(char*));
	if (!context) return -1;

	const size_t stringLen = strlen(string);
	
	// Skips empty lines
	char* instruction = strtok_s(string, ",\n", context);
	if (!instruction)
	{
		puts("Skipping empty line");
		return 0;
	}
	
	printf("Instruction \"%s\"\n", instruction);	// Debug

	// Line that begins with ','
	if (instruction != string)
	{
		puts("Found invalid token ',' at the start of the line");
		return -1;
	}

	InstructionInfo info = getInstructionInfo(instruction);
	if (invalidInstruction(&info))
	{
		printf("Invalid instruction '%s' found", instruction);
		return -1;
	}

	// Visual studio compiler does not implement VLAs (optional feature in C11)
	char* operands[OPERAND_MAX];
	char* lastRead = instruction;

	// Operands reading
	for (int i = 0; i < info.opNumber; i++)
	{
		puts("Performing a read");
		// Less than expected
		char* operand = strtok_s(NULL, ",\n", context);
		if (!operand)
		{
			printf("Expected %d operands, found %d\n", info.opNumber, i);
			return -1;
		}

		// todo: add operand type validity check!
		
		// Multiple commas detection
		const int len = operand - lastRead;
		// todo: clarify the or, it might not be needed
		if (len > 1 && (lastRead[len - 2] == ',' || lastRead[len - 1] == ','))
		{
			puts("Detected more than one comma between operands");
			return -1;
		}

		// Checks if the operand is valid and of the required type
		if(!isOperandType(operand, info.operands[i]))
		{
			printf("Operand \"%s\" is invalid\n", operand);
			return -1;
		}
		
		// Stores the operand in the operands array
		const size_t space = (strlen(operand) + 1) * sizeof(char);
		operands[i] = malloc(space);			// todo: remember to free this memory!
		if (!operands[i])
		{
			puts("Memory allocation error");
			return -1;
		}
		if (strcpy_s(operands[i], space, operand) != 0)
		{
			puts("Copy error");
			return -1;
		}
		lastRead = operand;
	}

	// Comment detection
	char* comment = lastRead + strlen(lastRead) + 1;
	
	// todo: current approach allows one comma after the last operand (should remove!)
	// No comment, end of the input string
	if ((size_t)(comment - string) > stringLen)
		return 0;
	
	// Potential comment, removing all leading whitespace
	while (isspace(*comment)) comment++;
	// Real comment
	if (*comment == '\0' || *comment == COMMENT_TOKEN) return 0;

	// String not starting with the comment token, invalid
	printf("Invalid token '%c'\n", *comment);
	return -1;
}
