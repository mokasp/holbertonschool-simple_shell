#include "shell.h"

int path_env()
{
    const char* home_dir = "/root";
    const char* bin_dir = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";

    char *path_env = (char*)malloc(1024);
	FILE *file;

    if (path_env == NULL)
    {
        perror("Memory allocation failed");
        return 1;
    }

    strcpy(path_env, "PATH=");
    strcat(path_env, home_dir);
    strcat(path_env, ":");
    strcat(path_env, bin_dir);
    strcat(path_env, ":/bin:/usr/bin");

    printf("PATH environment variable: %s\n", path_env);


	file = fopen("path_env.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        free(path_env);
        return 1;
    }

    if (fprintf(file, "%s", path_env) < 0)
    {
        perror("Error writing to file");
        free(path_env);
        fclose(file);
        return 1;
    }


    fclose(file);


    free(path_env);

    return 0;
}