#include "shell.h"

char **parse(char *str)
{

	int i = 0;
	int bufsize = TOK_BUFSIZE;
	char **toks = malloc(bufsize * sizeof(char *));
	char *token;

	token = strtok(str, " ");
	while (token != NULL)
	{
		toks[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;
	}
	toks[i] = token;


	free(token);
	free(toks);
	return (toks);
}