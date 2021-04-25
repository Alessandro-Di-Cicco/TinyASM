#include "Program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Operations/ArithmeticOperations.h"
#include "Operations/BranchingOperations.h"
#include "Operations/LogicOperations.h"
#include "Operations/MiscOperations.h"
#include "Operations/RegisterOperations.h"
#include "Operations/ConditionalOperations.h"

// Type of pointers that run instructions
typedef void (*run_func_t)(const char*, const char**);
typedef run_func_t(*run_getter_t)(char*);

typedef struct InstructionNode
{
	char* instruction;
	char** operands;
	void (*run)(char* instruction, char** operands);
	struct InstructionNode* next;
} InstructionNode;


static run_func_t get_run(char* instruction);
static InstructionNode* make_node(char* instruction, char** operands, int opCount);
static void append_node(InstructionNode* node);

static InstructionNode* head;
static InstructionNode* tail;
static InstructionNode* current;

static int index;
static int endAddress;

void add_instruction(char* instruction, char** operands, int opCount)
{
	InstructionNode* node = make_node(instruction, operands, opCount);
	append_node(node);
}

static InstructionNode* make_node(char* instruction, char** operands, int opCount)
{
	InstructionNode* node = malloc(sizeof(InstructionNode));
	if (!node) { puts("Error, could not allocate space"); exit(-1); }

	// Instruction copy
	const size_t instrLen = (strlen(instruction) + 1) * sizeof(char);
	node->instruction = malloc(instrLen);
	if (!node->instruction) { puts("Error, could not allocate space"); exit(-1); }
	strcpy_s(node->instruction, instrLen, instruction);

	// Clearing
	node->next = NULL;

	// Operands copy
	node->operands = calloc(3, sizeof(char*));
	if (!node->operands) { puts("Copy error"); exit(-1); }

	for (int i = 0; i < opCount; i++)
	{
		const size_t len = (strlen(operands[i]) + 1) * sizeof(char);
		node->operands[i] = malloc(len);
		if (!node->operands[i]) { puts("Error, could not allocate space"); exit(-1); }
		if (strcpy_s(node->operands[i], len, operands[i])) { puts("Copy error"); exit(-1); }
	}

	node->run = get_run(instruction);

	return node;
}

void append_node(InstructionNode* node)
{
	if (!head)
	{
		head = node;
		tail = node;
		current = head;
	}
	else
	{
		tail->next = node;
		tail = node;
	}

	endAddress++;
}

void set_instruction_index(int value)
{
	if (value >= endAddress)
	{
		printf("Memory violation: accessing address %d out of the address space (endAddr = %d)\n", value, endAddress - 1);
		exit(-1);
	}
	
	if (index > value - 1)
	{
		current = head;
		index = 0;
	}

	// Stops at index -1 because it will be advanced by another unit by the run function
	for (; index < value - 1; index++)
		current = current->next;
}

static run_func_t get_run(char* instruction)
{	
	static run_getter_t getters[] = {
		get_arithmetic_instruction,
		get_branching_instruction,
		get_conditional_instruction,
		get_logic_instruction,
		get_register_instruction,
		get_misc_instruction,
	};

	for (int i = 0, count = sizeof(getters) / sizeof(run_getter_t); i < count; i++)
	{
		const run_func_t runner = getters[i](instruction);
		if (runner) return runner;
	}

	printf("Error, couldn't find runner for instruction %s\n", instruction);
	exit(-1);
}

bool run_next()
{
	// This condition captures both an empty program and end of program
	if (!current) return false;
	current->run(current->instruction, current->operands);
	current = current->next;
	index++;
	return true;
}
