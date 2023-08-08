#ifndef SHELL_H
#define SHELL_H

#define TOK_BUFSIZE 64
#define TOK_DELIM " \n\t\r"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER 1024

#define MAXTOK 64

#define EXIT "exit\n"

char **parse(char *str);
char *readLine(void);
extern char **environ;
int execution(char **parsed);
int cmdHandler(char **parsed);

#endif
