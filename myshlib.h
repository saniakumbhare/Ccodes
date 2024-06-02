void initshell();
char* getinput();
void main_loop(char **args);
void main_loop(char **args);
char **parsecommand(char *input_line);
void runbatch(char *filename);
void execextcom(char *argv[]);