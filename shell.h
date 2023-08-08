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

char *readLine(void);

char *find_full_path(const char *command, const char *path_env);

int run_command(char *args[], const char *path_env);

char **parse(char *str);

extern char **enviorn;

#endif
