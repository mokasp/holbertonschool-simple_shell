#include "shell.h"
/**
 * *readLine - gets user input and returns to main
 *
 * Return: user input stored in as a string
 */

char *readLine(void)
{
	char *line = NULL;
	size_t buffer = 0;

	if (getline(&line, &buffer, stdin) == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	return (line);
}
