#include "shell.h"

int main(void)
{
	char **argv;
	char *line;
	int status = 1;


	while (status == 1)
	{
		if (isatty(fileno(stdin)))
			printf(":3 ");

		line = readLine();
		argv = parse(line);
		status = cmdHandler(argv);
		if (status == -2)
		{
			free(line);
			free(argv);
			exit(2);
		}

		free(line);
		free(argv);
	}
	exit(EXIT_SUCCESS);
}
