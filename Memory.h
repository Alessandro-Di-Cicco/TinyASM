#ifndef MEMORY_h
#define MEMORY_h

#define REGISTERS_COUNT 8

typedef enum
{
	R0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
} Register;

void set_register(Register reg, int value);
int get_register(Register reg);

#endif