#include <stdio.h>

#include "Parser.h"
#include "Program.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		puts("Invalid number of parameters, must be one");
		return -1;
	}
	
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
