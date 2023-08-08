#include "shell.h"

int main(void)
{
        char **argv;
        char *line;


        while (1)
        {
                printf(":3 ");

                line = readLine();
                argv = parse(line);

                free(line);
                free(argv);
        }
        exit(EXIT_SUCCESS);
}