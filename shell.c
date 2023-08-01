#include "shell.h"

int main(void)
{
	char **args = malloc(sizeof(char *)* 64);
	char *line = NULL;
	size_t buffer = 0;

	while (1)
	{
		printf(":3 ");

		if (getline(&line, &buffer, stdin) == -1)
		{
			free(line);
			perror("end of file");
			exit(EXIT_FAILURE);
		}
		args = parse(line);

		if (strcmp(line, "hi\n") == 0)
		{
			printf("halllooo :3c type a command plz\n");
		}

		if (strcmp(line, EXIT) == 0)
		{
			printf("baiiii\n");
			exit (EXIT_SUCCESS);
		}
	}
	free(args);
	free(line);
	return (1);
}