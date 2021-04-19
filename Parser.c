#include "Parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "InstructionSet.h"
#include "Program.h"

#define COMMENT_TOKEN '#'

static int parse_line(char* string);
static int is_invalid(char* instruction, char* string, InstructionInfo info);
static char* read_operands(char* instruction, InstructionInfo info, char** strtokContext, char** operands);
static int check_comment(char* lastRead, const char* string, size_t stringLen);

int parse_source()
{
	FILE** file = malloc(sizeof(FILE*));
	if (!file)
	{
		puts("Memory allocation error");
		return -1;
	}

	// This returns 0 on success
	const errno_t error = fopen_s(file, "source.tsm", "r");
	if (error || !*file)
	{
		puts("Error opening the file");
		return -1;
	}

	// Line reading setup
	char* line = malloc(sizeof(char) * 256);
	if (!line)
	{
		puts("Error allocating memory");
		return -1;
	}

	int lineCounter = 0;	// Used to point at lines with invalid syntax
	// Line parsing
	while (!feof(*file))
	{
		// todo: have this count each line length by scanning the file through getc(), allowing unlimited line length
		if (!fgets(line, 256, *file) && feof(*file))
			puts("End of file reached");
		else
		{
			lineCounter++;
			// Parsing error detection
			if (parse_line(line))
			{
				printf("Error at line %d\n", lineCounter);
				exit(-1);	// Immediate stop, the program cannot run
			}
		}

		puts("\n");
	}
	return 0;
} // parseSource()


static int parse_line(char* string)
{
	// Initializes context for strtok_s
	char** context = malloc(sizeof(char*));
	if (!context) return -1;

	// Computed ahead of time because strtok_s alters the string
	const size_t stringLen = strlen(string);
	
	char* instruction = strtok_s(string, ",\n", context);
	InstructionInfo info = get_instruction_info(instruction);

	// Skips invalid instructions
	const int validity = is_invalid(instruction, string, info);
	if (validity == -1) return -1;
	if (validity == -2) return 0;

	// Visual studio compiler does not implement VLAs (optional feature in C11)
	char* operands[OPERAND_MAX];
	char* lastRead = read_operands(instruction, info, context, operands);
	if (!lastRead) return -1;

	// -1 if invalid input after the instruction, 0 if comment or nothing
	if (check_comment(lastRead, string, stringLen) == -1) return -1;

	add_instruction(instruction, operands, info.opNumber);

	return 0;
}

// Returns -1 if the instruction is invalid, 0 if it's valid and -2 if it's empty
static int is_invalid(char* instruction, char* string, InstructionInfo info)
{
	if (strcmp(string, "\n") == 0) return -2;
	
	if (!instruction)
	{
		puts("Invalid line");
		return -1;
	}

	// Line that begins with ','
	if (instruction != string)
	{
		puts("Found invalid token ',' at the start of the line");
		return -1;
	}

	if (invalid_instruction(&info))
	{
		printf("Invalid instruction '%s' found", instruction);
		return -1;
	}

	return 0;
}

static char* read_operands(char* instruction, InstructionInfo info, char** strtokContext, char** operands)
{
	char* lastRead = instruction;

	// Operands reading
	for (int i = 0; i < info.opNumber; i++)
	{
		// Less than expected
		char* operand = strtok_s(NULL, ",\n", strtokContext);
		if (!operand)
		{
			printf("Expected %d operands, found %d\n", info.opNumber, i);
			return NULL;
		}

		// todo: add operand type validity check!

		// Multiple commas detection
		const int len = operand - lastRead;
		// todo: clarify the or, it might not be needed
		if (len > 1 && (lastRead[len - 2] == ',' || lastRead[len - 1] == ','))
		{
			puts("Detected more than one comma between operands");
			return NULL;
		}

		// Checks if the operand is valid and of the required type
		if (!is_operand_type(operand, info.operands[i]))
		{
			printf("Operand \"%s\" is invalid\n", operand);
			return NULL;
		}

		// Stores the operand in the operands array
		const size_t space = (strlen(operand) + 1) * sizeof(char);
		operands[i] = malloc(space);			// todo: remember to free this memory!
		if (!operands[i])
		{
			puts("Memory allocation error");
			return NULL;
		}
		if (strcpy_s(operands[i], space, operand) != 0)
		{
			puts("Copy error");
			return NULL;
		}
		lastRead = operand;
	}

	return lastRead;
}

static int check_comment(char* lastRead, const char* string, size_t stringLen)
{
	// Comment detection
	char* comment = lastRead + strlen(lastRead) + 1;

	// todo: current approach REQUIRES one comma after the last operand (should change it!)
	// todo: also, a comma is required between instruction and first operand (weird)
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
