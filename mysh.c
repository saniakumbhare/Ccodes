#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myshlib.h" 

void main_loop(char **args) 
{
    while (1) 
    {
        char *command = getinput(); 
        char **args = parsecommand(command); 

        if (strcmp(args[0], "exit") == 0) 
        {
            free(command);
            free(args);
            break; 
        } else if (strcmp(args[0], "run") == 0) 
        {
            if (args[1] == NULL) 
            {
                fprintf(stderr, "Error: Missing filename for 'run' command\n");
            } else 
            {
                runbatch(args[1]);
            }
        } else 
        {
            execextcom(args);
        }

        free(command);
        free(args);
    }
}

int main(int argc, char *argv[]) 
{
    initshell();

    main_loop(NULL);

    return 0; 
}