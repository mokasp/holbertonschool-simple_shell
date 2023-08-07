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

		free(line);
		free(argv);
	}
	exit(EXIT_FAILURE);
}
