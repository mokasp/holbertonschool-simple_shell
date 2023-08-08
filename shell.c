#include "shell.h"

int main(void)
{
        char **argv;
        char *line;


        while (1)
        {
                printf(":3 ");

<<<<<<< HEAD
                line = readLine();
                argv = parse(line);
=======
		line = readLine();
		argv = parse(line);
		status = cmdHandler(argv);
		if (status == -2)
		{
			free(line);
			free(argv);
			exit(2);
		}
>>>>>>> fd4849020e48beebab598bace3050ceaf35a3c7c

                free(line);
                free(argv);
        }
        exit(EXIT_SUCCESS);
}