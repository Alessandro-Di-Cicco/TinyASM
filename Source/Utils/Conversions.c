#include "Utils/Conversions.h"

#include <stdlib.h>

Register get_register_literal(const char* name)
{
	return strtol(name + 1, NULL, 10);
}

int get_register_value_literal(const char* name)
{
	return get_register(get_register_literal(name));
}

int get_immediate_literal(const char* literal)
{
	return strtol(literal, NULL, 10);
}
