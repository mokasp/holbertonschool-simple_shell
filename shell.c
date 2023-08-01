#include "shell.h"
#define TOK_BUFSIZE 64
#define TOK_DELIM " "
int main(void)
{
	char **args = malloc(sizeof(char *) * 64);
	char *line = NULL;
	size_t buffer = 0;

	args = NULL;

	while (1)
	{
		printf(":3 ");
		if (getline(&line, &buffer, stdin) == -1)
		{
			free(line);
			perror("end of file");
			exit (EXIT_FAILURE);
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

char **parse(char *str)
{
	int i = 0;
	int bufsize = TOK_BUFSIZE;
	char **toks = malloc(bufsize * sizeof(char *));
        char *token;

        token = strtok(str, " ");
	while (token != NULL)
	{
		toks[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	toks[i] = token;
        return (toks);
}
