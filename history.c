# include "headers.h"
int history_store(char *add_command, char command[21][M], int no_of_words)
{
    // FILE *fp=fopen()
    // printf("%d\n", no_of_words);
    if (no_of_words == 0)
    {
        //    printf("%s %s\n",command[0],add_command);
        strcpy(command[0], add_command);
        no_of_words++;
    }
    else if (no_of_words < 20)
    {
        if (strcmp(command[no_of_words - 1], add_command) == 0)
            ;
        else
        {
            strcpy(command[no_of_words], add_command);
            no_of_words++;
        }
    }
    else
    {
        if (strcmp(command[no_of_words - 1], add_command) != 0)
        {
            for (int i = 1; i < 20; i++)
            {
                strcpy(command[i - 1], command[i]);
                if (i == 19)
                    strcpy(command[i], add_command);
            }
            no_of_words++;
        }
    }
    FILE *fp = fopen("his_store.txt", "w");
    if (no_of_words < 20)
    {
        for (int i = 0; i < no_of_words; i++)
            fprintf(fp, "%s\n", command[i]);
    }
    else
    {
        for (int i = 0; i < 20; i++)
            fprintf(fp, "%s\n", command[i]);
    }
    fclose(fp);
    return no_of_words;
}
void print_history(char command[21][M], int no_of_words)
{
    if (no_of_words < 10)
    {
        for (int i = 0; i < no_of_words; i++)
            printf("%s\n", command[i]);
    }
    else if (no_of_words > 20)
    {
        for (int i = 10; i < 20; i++)
            printf("%s\n", command[i]);
    }
    else
    {
        for (int i = no_of_words - 10; i < no_of_words; i++)
            printf("%s\n", command[i]);
    }
}