#include "shell.h"

char **parse(char *str)
{
<<<<<<< HEAD
	int i = 0;
	int bufsize = TOK_BUFSIZE;
	char **toks = malloc(bufsize * sizeof(char *));
	char *token;
=======
	char *token = NULL;
	char **toks = NULL;
	int i;
>>>>>>> origin

	token = strtok(str, " ");
	while (token != NULL)
	{
<<<<<<< HEAD
		toks[i] = token;
=======
		toks[i] = strdup(token);

>>>>>>> origin
		token = strtok(NULL, " ");
		i++;
	}
	toks[i] = token;
<<<<<<< HEAD
	return (toks);
}
=======
	free(token);
	free(toks);
	return (toks);
}
>>>>>>> origin
