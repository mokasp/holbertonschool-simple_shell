#include "shell.h"

int execution(char **parsed)
{
	pid_t pid = fork();
<<<<<<< HEAD


=======
	
>>>>>>> e995c0c30cb034b9d38af900ce42195032655d5a
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
