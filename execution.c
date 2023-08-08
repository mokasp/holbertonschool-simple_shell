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
	char *path;
	char *path_copy;
	char *dir;

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

	getenv("PATH");
	strdup(path);
	strtok(path_copy, ":");

	while (dir != NULL)
	{
    	char executable_path[1024];
snprintf(executable_path, sizeof(executable_path), "%s/%s", dir, parsed[0]);
    if (access(executable_path, X_OK) == 0)
	{
        execv(executable_path, parsed);
        perror("execution failed");
        return -1;
    }
    dir = strtok(NULL, ":");
}
free(path_copy);
perror("command not found");
return -1;


}

