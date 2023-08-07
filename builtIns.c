#include "shell.h"

int cmdHandler(char **parsed)
{
        int switchArg = 0;
        char **env = environ;
        char **envp = environ;
        int i, j;
        char *cmdList[6];
        int status = 0;

        cmdList[0] = "exit";
        cmdList[1] = "hi";
        cmdList[2] = "cd";
        cmdList[3] = "env";
        cmdList[4] = "path";

        for (i = 0; i < 5; i++)
        {
                if (strcmp(parsed[0], cmdList[i]) == 0)
                {
                        switchArg = i + 1;
                }
        }

        switch (switchArg)
        {
                case 1:
                        return (-1);
                case 2:
                        printf("\n oh hallo \n");
                        return (1);
                case 3:
                        if (parsed[1] == NULL)
                                perror("too few arguments");
                        else
                        {
                                if (chdir(parsed[1]) != 0)
                                {
                                        perror("hsh");
                                }
                        }
                        return (1);
		case 4:
                        while (*env != NULL)
                        {
                                printf("%s\n", *env);
                                env++;
                        }
                        return (1);
                case 5:
                        for (j = 0; envp[j] != NULL; j++)
                        {
                                if (strncmp(envp[j], "PATH=", 5) == 0)
                                {
                                        printf("%s\n", &envp[j][5]);
					break;
                                }
                        }
			return (1);
                default:
                        status = execution(parsed);
			return (status);
        }
        return (0);
}
