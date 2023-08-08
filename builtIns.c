#include "shell.h"
/**
* cmdHandler - compares command with list of built-in commands and calls execute function if command was not found in built-ins
* @parsed: 2d array holding parsed user input
 *
 * Return: -1 if user enters "exit", else returns 1
 */
int cmdHandler(char **parsed)
{
	int switchArg = 0, status = 0, i;
	char **env = environ;
	char *cmdList[4];

	cmdList[0] = "exit";
	cmdList[1] = "cd";
	cmdList[2] = "env";
	for (i = 0; i < 3; i++)
	{
		if (strcmp(parsed[0], cmdList[i]) == 0)
			switchArg = i + 1;
	}
	switch (switchArg)
	{
		case 1:
			return (-1);
		case 2:
			if (parsed[1] == NULL)
				perror("too few arguments");
			else
			{
				if (chdir(parsed[1]) != 0)
					perror("hsh");
			}
			return (1);
		case 3:
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			return (1);
		default:
			status = execution(parsed);
			return (status);
	}
	return (0);
}
