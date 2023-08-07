#include "shell.h"

char **parse(char *str)
{
	char *token = NULL;
	char **toks = NULL;
	int i;

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
