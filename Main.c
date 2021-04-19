#include <stdio.h>

#include "Parser.h"
#include "Program.h"

int main(void)
{
	// TODO IMPORTANT: debug all the operations implemented, some might not perform as expected!
	
	// todo: replace printf with puts all over
	if (parse_source() == -1)
		puts("Parsing error");
	else puts("Parsing successful");

	while (run_next()) {}

	puts("Execution completed successfully");
	
	printf("\n\n");
	return 0;
}
