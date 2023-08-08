#include "shell.h"
/**
 * execution - execute non built-in parsed command
 * @parsed: 2d array holding parsed user input
 *
 * Return: 1 on success
 */
int execution(char **parsed)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(parsed[0], parsed) == -1)
			perror("unheard of");
		return (-1);
	}
	else if (pid < 0)
		perror("Fork error");
	else
	{
		wait(NULL);
	}
	return (1);
}
