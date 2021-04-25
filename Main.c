#include <stdio.h>

#include "Parser.h"
#include "Program.h"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 3)
	{
		puts("Invalid number of parameters, must be one or two");
		return -1;
	}
	
	// todo: allow to set debug mode from input
	if (parse_source(argv[1]) == -1)
	{
		puts("Parsing error");
		return -1;
	}

	while (run_next()) {}

	puts("Execution completed successfully");
	
	printf("\n\n");
	return 0;
}
