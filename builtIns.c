#include "shell.h"

int cmdHandler(char **parsed)
{
	int switchArg = 0, status = 0, i;
	char **env = environ
	char *cmdList[4];

	cmdList[0] = "exit";
	cmdList[1] = "cd";
	cmdList[2] = "env";
	for (i = 0; i < 4; i++)
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
