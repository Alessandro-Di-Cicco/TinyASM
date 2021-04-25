#ifndef INSTRUCTION_SET_h
#define INSTRUCTION_SET_h

// The maximum number of operands an instruction could have
#define OPERAND_MAX 3
#define INVALID_INSTRUCTION (InstructionInfo) { "INVALID", -1 }
#include <stdbool.h>

typedef enum { REGISTER, IMMEDIATE } OperandType;

typedef struct InstructionInfo
{
	char* command;
	int opNumber;
	OperandType operands[OPERAND_MAX];
} InstructionInfo;

InstructionInfo get_instruction_info(char* instruction);

bool invalid_instruction(InstructionInfo* restrict instruction);

bool is_operand_type(char* name, OperandType type);

#endif
