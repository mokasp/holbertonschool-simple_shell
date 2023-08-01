#ifndef SHELL_H
#define SHELL_H

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
extern char **environ;

#endif
