#include "shell.h"

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
