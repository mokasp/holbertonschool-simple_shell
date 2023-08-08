#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_ARGS 64
#define MAX_BG_PROCESSES 64

typedef struct BackgroundProcess {
    pid_t pid;
    char *command;
} BackgroundProcess;

BackgroundProcess backgroundProcesses[MAX_BG_PROCESSES];
int numBackgroundProcesses = 0;

void handle_sigint(int signum);
void add_background_process(pid_t pid, const char *command);
void remove_background_process(pid_t pid);
char *read_line(void);
char **parse_line(char *line);
void execute_command(char **args);

void handle_sigint(int signum)
{
    pid_t foregroundPid;
    signum = signum; /* To silence the unused parameter warning */

    /* Ignore SIGINT (Ctrl+C) in the shell itself */
    signal(SIGINT, SIG_IGN);

    /* If there is a foreground process, forward SIGINT to it */
    foregroundPid = waitpid(-1, NULL, WNOHANG);
    if (foregroundPid > 0)
        kill(foregroundPid, SIGINT);
}

void add_background_process(pid_t pid, const char *command)
{
    if (numBackgroundProcesses < MAX_BG_PROCESSES) {
        backgroundProcesses[numBackgroundProcesses].pid = pid;
        backgroundProcesses[numBackgroundProcesses].command = strdup(command);
        numBackgroundProcesses++;
    } else {
        fprintf(stderr, "Cannot add more background processes.\n");
    }
}

void remove_background_process(pid_t pid)
{
    int i;
    for (i = 0; i < numBackgroundProcesses; i++) {
        if (backgroundProcesses[i].pid == pid) {
            free(backgroundProcesses[i].command);
            numBackgroundProcesses--;
            backgroundProcesses[i] = backgroundProcesses[numBackgroundProcesses];
            break;
        }
    }
}

char *read_line(void)
{
    char *line = NULL;
    size_t buffer = 0;
    if (getline(&line, &buffer, stdin) == -1)
    {
        free(line);
        printf("thanks bai !\n");
        exit(EXIT_SUCCESS);
    }
    return line;
}

char **parse_line(char *line)
{
    int bufsize = MAX_ARGS;
    int position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGS;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

void execute_command(char **args)
{
    int i;
    int pipe_pos = -1;

    if (args[0] == NULL) {
        /* Empty command */
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        /* Built-in command: exit */
        for (i = 0; i < numBackgroundProcesses; i++) {
            kill(backgroundProcesses[i].pid, SIGKILL);
            free(backgroundProcesses[i].command);
        }
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        /* Built-in command: cd */
        if (args[1] == NULL) {
            fprintf(stderr, "Expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return;
    } else if (strcmp(args[0], "bglist") == 0) {
        /* Built-in command: bglist */
        for (i = 0; i < numBackgroundProcesses; i++) {
            printf("[%d] %s\n", i + 1, backgroundProcesses[i].command);
        }
        return;
    } else if (strcmp(args[0], "bgkill") == 0) {
        /* Built-in command: bgkill */
        if (args[1] == NULL) {
            fprintf(stderr, "Expected argument to \"bgkill\"\n");
        } else {
            int bgIndex = atoi(args[1]);
            if (bgIndex >= 1 && bgIndex <= numBackgroundProcesses) {
                pid_t pid = backgroundProcesses[bgIndex - 1].pid;
                kill(pid, SIGKILL);
            } else {
                fprintf(stderr, "Invalid background process index\n");
            }
        }
        return;
    } else if (strcmp(args[0], "bg") == 0) {
        /* Built-in command: bg */
        if (args[1] == NULL) {
            fprintf(stderr, "Expected argument to \"bg\"\n");
        } else {
            int bgIndex = atoi(args[1]);
            if (bgIndex >= 1 && bgIndex <= numBackgroundProcesses) {
                pid_t pid = backgroundProcesses[bgIndex - 1].pid;
                kill(pid, SIGCONT);
            } else {
                fprintf(stderr, "Invalid background process index\n");
            }
        }
        return;
    }

    /* Non-built-in command: Check for pipe operator '|' */
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL; /* Replace '|' with NULL to split commands */
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos >= 0) {
        /* There is a pipe operator '|', execute command with pipe */
        char **first_command = args;
        char **second_command = &args[pipe_pos + 1];

        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("Pipe creation failed");
            exit(EXIT_FAILURE);
        }

        pid_t *pid1;
        pid_t pid2;
        pid1 = fork();
		pid_t pid = fork();

        if (pid1 == 0) {
            /* Child process (first command) */
            close(pipefd[0]); /* Close read end of the pipe */
            dup2(pipefd[1], STDOUT_FILENO); /* Redirect stdout to the write end of the pipe */
            close(pipefd[1]); /* Close the write end of the pipe */
            execvp(first_command[0], first_command);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid1 < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else {
            /* Parent process (main shell) */
            pid2 = fork();

            if (pid2 == 0) {
                /* Child process (second command) */
                close(pipefd[1]); /* Close write end of the pipe */
                dup2(pipefd[0], STDIN_FILENO); /* Redirect stdin to the read end of the pipe */
                close(pipefd[0]); /* Close read end of the pipe */
                execvp(second_command[0], second_command);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else if (pid2 < 0) {
                perror("Fork error");
                exit(EXIT_FAILURE);
            } else {
                /* Parent process (main shell) */
                close(pipefd[0]);
                close(pipefd[1]);
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
            }
        }
    } else {
        /* No pipe operator '|', execute single command */
        int background = 0;
        for (i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "&") == 0) {
                background = 1;
                args[i] = NULL; /* Remove the '&' from the arguments */
                break;
            }
        }

        if (pid == 0) {
            /* Child process */
            if (execvp(args[0], args) == -1) {
                perror("Command not found");
                exit(EXIT_FAILURE);
            }
        } else if (pid < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else {
            /* Parent process */
            if (!background) {
                int status;
                do {
                    waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            } else {
                add_background_process(pid, args[0]);
            }
        }
    }
}

int main(void)
{
    char *line;
    char **args;

    signal(SIGINT, handle_sigint);

    while (1) {
        printf("my_shell> ");
        line = read_line();
        args = parse_line(line);
        execute_command(args);
        free(line);
        free(args);
        while (numBackgroundProcesses > 0) {
            pid_t pid = waitpid(-1, NULL, WNOHANG);
            if (pid > 0) {
                remove_background_process(pid);
            } else {
                break;
            }
        }
    }

    return 0;
}
