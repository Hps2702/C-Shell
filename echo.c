# include "headers.h"
void execute_echo(char **command, int no_of_words)
{ // printf("jjjjjjjjjjj\n");
    if (no_of_words == 1)
    {
        printf("\n");
        return;
    }
 //  fprintf(stderr,"val %d\n",no_of_words);

    for (int i = 0; i < no_of_words; i++)
    {
        if (strcmp(command[i], "echo") == 0)
            continue;
        else if (i == no_of_words - 1)
            printf("%s\n", command[i]);
        else
            printf("%s ", command[i]);
    }
        
}