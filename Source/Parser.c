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
static int read_operands(char* instruction, InstructionInfo info, char** operands, int instructionLen);
static char* read_instruction(char* string, int* tokenLen);

int parse_source(const char* filename)
{	
	FILE** file = malloc(sizeof(FILE*));
	if (!file)
	{
		puts("Memory allocation error");
		return -1;
	}

	// This returns 0 on success
	const errno_t error = fopen_s(file, filename, "r");
	if (error != 0 || !*file)
	{
		puts("Error opening the file");
		return -1;
	}

	/* Line reading setup, parsing will break with lines longer than 512 chars
	 * a custom file-reading function (similar to getline() on unix) would be needed to fix this */
	char* line = malloc(sizeof(char) * 512);
	if (!line)
	{
		puts("Error allocating memory");
		return -1;
	}

	int lineCounter = 0;	// Used to point at lines with invalid syntax
	// Line parsing
	while (!feof(*file))
	{
		if (!fgets(line, 512, *file) && feof(*file))
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
	}

	free(line);
	
	return 0;
} // parse_source()


static int parse_line(char* string)
{	
	int * instructionLen = calloc(1, sizeof(int));
	if (!instructionLen)
	{
		puts("Calloc error");
		return -1;
	}
	char* instruction = read_instruction(string, instructionLen);
	
	const InstructionInfo info = get_instruction_info(instruction);

	// Skips invalid instructions
	const int validity = is_invalid(instruction, string, info);
	if (validity == -1) return -1;
	if (validity == -2) return 0;

	// Visual studio compiler does not implement VLAs (optional feature in C11)
	char* operands[OPERAND_MAX];
	
	if (read_operands(string, info, operands, *instructionLen) == -1)
		return -1;

	add_instruction(instruction, operands, info.opNumber);

	free(instructionLen);
	for (int i = 0; i < info.opNumber; i++)
		free(operands[i]);
	
	return 0;
} //parse_line()

// Returns -1 if the instruction is invalid, 0 if it's valid and -2 if it's empty
static int is_invalid(char* instruction, char* string, InstructionInfo info)
{
	// Empty line
	if (strcmp(string, "\n") == 0) return -2;

	// When instruction begins with non-alpha char
	if (!instruction)
	{
		puts("Invalid line");
		return -1;
	}

	// The instruction doesn't exists
	if (invalid_instruction(&info))
	{
		printf("Invalid instruction '%s' found", instruction);
		return -1;
	}

	return 0;
} // is_invalid()

// Attempts to read all the operands, returning -1 if it fails
static int read_operands(char* instruction, InstructionInfo info, char** operands, int instructionLen)
{
	char* moving = instruction + instructionLen;

	for (int i = 0; i < info.opNumber; i++)
	{
		// Removes leading spaces
		while (isspace(*moving))
			moving++;

		char* start = moving;

		// Adds everything that is a char or digit
		while (isalpha(*moving) || isdigit(*moving))
			moving++;

		const size_t size = sizeof(char) * (moving - start + 1);
		/* Happens if there's a comma after the instruction or if there are two commas with
		 * nothing, or space, in between them */
		if (size == 1)
		{
			puts("empty operand found");
			return -1;
		}
		operands[i] = calloc(1, size);
		
		if(!operands)
		{
			puts("Allocation error");
			return -1;
		}
		if (memcpy_s(operands[i], size, start, size - sizeof(char)))
		{
			puts("Memcpy error");
			return -1;
		}

		// Removes trailing space
		while (isspace(*moving))
			moving++;

		// Looks for a comma if it's not the last operand
		if (*moving != ',' && i < info.opNumber - 1)
		{
			printf("Separator error, expected ',' but found '%c'\n", *moving);
			return -1;
		}
		
		// Looks for end of line or start of a comment, this solves the comment detection issue as well
		if (*moving != '\0' && *moving != COMMENT_TOKEN && i == info.opNumber - 1)
		{
			printf("Separator error, expected end of line or '#' but found '%c'\n", *moving);
			return -1;
		}

		/* Skips the separator for the (possible) next iteration
		 * Doesn't cause issues in the last iteration (even if it goes past the null char */
		moving++;

		// Operand validity check
		if (!is_operand_type(operands[i], info.operands[i]))
		{
			printf("Operand '%s' is invalid\n", operands[i]);
			return -1;
		}
		
		// printf("--Successfully added operand %s\n", operands[i]);
	}

	return 0;
} // read_operands()

// Reads the first string in the line, treating it as the instruction
static char* read_instruction(char* string, int* tokenLen)
{
	char* moving = string;
	while (isalpha(*moving))
		moving++;

	const size_t size = sizeof(char) * (moving - string + 1);
	// Happens when instruction begins with invalid char
	if (size == 1)
		return NULL;
	char* instruction = calloc(1, size);

	// Something wrong with copy
	if (memcpy_s(instruction, size, string, size - sizeof(char)))
	{
		puts("Error copying instruction");
		exit(-1);
	}
	
	*tokenLen = moving - string;
	return instruction;
} // read_instruction
