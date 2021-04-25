#include "Utils/ComparisionChecker.h"

bool compare_values(const char* instruction, const int first, const int second)
{
	return
	(instruction[2] == 'E' && instruction[1] != 'N' || instruction[2] == 'Q') && first == second ||	// All the ones ending with E (except for NE) admit equality
		instruction[1] == 'G' && first > second ||	// GE, GT
		instruction[1] == 'L' && first < second ||	// LE, LT
		instruction[1] == 'N' && first != second;	// NE
}
