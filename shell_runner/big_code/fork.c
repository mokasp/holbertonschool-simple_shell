#include "shell.h"

int run_command(char *args[], const char *path_env)
{
	pid_t pid = fork();
	int i = 0;

	if (pid < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *full_path = find_full_path(args[0], path_env);

		if (full_path != NULL)
		{
			execve(full_path, args, NULL);
			perror("execve error");
			free(full_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	return (-1);
}