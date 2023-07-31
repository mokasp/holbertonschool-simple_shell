#include "shell.h"

int main(void)
{
        char *line = NULL;
        size_t buffer = 0;

        while (1)
        {
                printf(":3 ");
                getline(&line, &buffer, stdin);
                if (strcmp(line, "hello\n") == 0)
                        printf("halllooo :3c type a command plz\n");
                if (strcmp(line, EXIT) == 0)
                {
                        printf("baiiii\n");
                        exit (EXIT_SUCCESS);
                }
        }
        free(line);
        return (1);
}
