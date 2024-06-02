#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 32 
#define MAX_ARG_LEN 128 

void initshell() 
{
    system("clear");
    printf("\nWelcome to MyShell interactive mode!\n");
    printf("Enter commands and press Enter to execute.\n");

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("mysh:%s$ ", cwd);
}

char *getinput() 
{
    char *input_line = NULL; 
    size_t buffer_size = 0;   
    ssize_t position = 0;        
    int character;           

    while ((character = getchar()) != '\n' && character != EOF) 
    {
        if (position == buffer_size - 1) 
        {
            buffer_size += 100; 
            input_line = realloc(input_line, buffer_size);
            if (input_line == NULL) 
            {
                fprintf(stderr, "Memory allocation error!\n");
                return NULL; 
            }
        }
        input_line[position++] = character;
    }

    input_line[position] = '\0';
    return input_line;
}

char **parsecommand(char *input_line) 
{
    char **argv = malloc(MAX_ARGS * sizeof(char *));
    int argc = 0;  

    char *token = strtok(input_line, " \t\n"); 
    while (token) 
    {
        if (argc >= MAX_ARGS) 
        {
            fprintf(stderr, "Error: Too many arguments!\n");
            return NULL; 
        }

        argv[argc] = strdup(token);
        if (!argv[argc]) 
        {
            fprintf(stderr, "Error: Memory allocation error!\n");
            for (int i = 0; i < argc; i++) free(argv[i]);
            free(argv);
            return NULL; 
        }
        argc++;
        token = strtok(NULL, " \t\n"); 
    }
    argv[argc] = NULL;
    return argv;
}

void execextcom(char *argv[]) 
{
    pid_t pid = fork(); 
    if (pid < 0) {
        fprintf(stderr, "Error: Fork failed\n");
    } else if (pid == 0) {
        execvp(argv[0], argv);  
        fprintf(stderr, "Error: execvp failed\n");
        _exit(1);  
    } else {
        int status;
        waitpid(pid, &status, 0);  
        if (WIFEXITED(status)) 
        {
            printf("Command exited with status: %d\n", WEXITSTATUS(status));
        } else 
        {
            printf("Command terminated abnormally!\n");
        }
    }
}

void runbatch(char *filename) 
{
    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL) 
    {
        fprintf(stderr, "Error: Cannot open batch file: %s\n", filename);
        return; 
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        line[strcspn(line, "\n")] = '\0';
        char **parsed_args = parsecommand(line);
        if (parsed_args) 
        {
            execextcom(parsed_args);  
            for (int i = 0; parsed_args[i] != NULL; i++) free(parsed_args[i]);
            free(parsed_args); 
        } else 
        {
            fprintf(stderr, "Error: Failed to parse command: %s\n", line);
        }
    }

    fclose(fp); 
    free(line); 
}
