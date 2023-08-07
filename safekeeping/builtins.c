#include "shell.h"

int builtIn(char **parsed)
{
        int i;
        char *numOfCmds = 4;
        int switchArg = 0;
        char *ownCmdList[numOfCmds];

        ownCmdList[0] = "exit";
        ownCmdList[1] = "";
        ownCmdList[2] = "";
        ownCmdList[3] = "";


        for (i = 0; i < numOfCmds; i++)
        {
                if (strcmp(parsed[0], ownCmdList[i]) == 0)
                {
                        switchArg = i + 1;
                        break;
                }
        }

        switch (switchArg)
        {
                if (strcmp(line, EXIT) == 0)
                {
                        printf("baiiii\n");
                        exit (EXIT_SUCCESS);
                }
        }
}
