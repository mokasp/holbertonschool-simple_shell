#include "shell.h"
/**
 * **parse - parses user input from string into a 2d array
 * @str: user input to parse
 *
 * Return: 2d array of parsed user input
 */
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
		token = strtok(NULL, TOK_DELIM);
	}
	toks[i] = NULL;
	free(token);
	return (toks);
}
