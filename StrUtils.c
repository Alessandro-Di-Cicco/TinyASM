#include "StrUtils.h"

#include <string.h>

bool str_contains(char* source, char** pool, int size)
{
	for (int i = 0; i < size; i++)
		if (strstr(source, pool[i])) return true;

	return false;
}
