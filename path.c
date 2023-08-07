#include "shell.h"

char *find_full_path(const char *command, const char *path_env)
{
	char *full_path = NULL;

	if (path_env != NULL)
	{
		char *path_copy = strdup(path_env);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			full_path = (char *)malloc(strlen(dir) + strlen(command) + 2);
			if (full_path == NULL)
			{
				perror("Memory allocation error");
				free(path_copy);
				return NULL;
			}

			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return full_path;
			}

			free(full_path);
			dir = strtok(NULL, ":");
		}

		free(path_copy);
	}

	return NULL;
}