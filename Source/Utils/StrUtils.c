#include "Utils/StrUtils.h"

#include <string.h>

bool str_contains(const char* source, char** pool, int size, bool allowI)
{
	const size_t sourceLen = strlen(source);
	
	for (int i = 0; i < size; i++)
	{
		char* match = strstr(source, pool[i]);
		// Match present at the start
		if (match && match - source == 0)
		{
			// Checks for I at the end
			const size_t poolLen = strlen(pool[i]);
			if (sourceLen == poolLen || sourceLen == poolLen + 1 && allowI && source[sourceLen - 1] == 'I')
				return true;
		}
	}

	return false;
}
