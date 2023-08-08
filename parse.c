#include "shell.h"

char **parse(char *str)
{
	int i = 0;
	int bufsize = TOK_BUFSIZE;
	char **toks = malloc(bufsize * sizeof(char *));
	char *token;

	if (!toks)
	{
		perror("allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, TOK_DELIM);
	while (token != NULL)
	{
		toks[i] = token;
		i++;
		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			toks = realloc(toks, bufsize * sizeof(char *));
			if (!toks)
			{
				perror("allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	toks[i] = NULL;
	free(token);
	return (toks);
}
