#include "headers.h"
void execute_cd(char **command, int no_of_words, char *dir_init)
{
    // printf("%d\n",no_of_words);
    // printf("%s\n",command[1]);
    char *dir = malloc(N);
    getcwd(dir, N);
    char cmd_handler[][3] = {".", "..", "~", "-"};
    if (no_of_words == 1)
    {
        // printf("gggg\n");
        getcwd(dir_store, N);
        chdir(dir_init);
    }
    else if (no_of_words > 2)
    {
        perror("too many arguements for cd");
    }
    else
    {
        char *parse = strstr(command[1], "~/");
        if (parse)
        {
            // printf("%s\n",parse);
            int len = strlen(parse);
            // printf("%d\n",len);
            command[1] = "~";
            execute_cd(command, 2, dir_init);
            char temp[len - 2];
            strcpy(temp, &parse[2]);
            command[1] = temp;
            execute_cd(command, 2, dir_init);
            strcpy(dir_store, dir);
            return;
        }
        parse = strstr(command[1], "../");

        if (parse)
        {
            // printf("%s\n",parse);
            int len = strlen(parse);
            // printf("%d\n",len);
            command[1] = "..";
            execute_cd(command, 2, dir_init);
            char temp[len - 3];
            strcpy(temp, &parse[3]);
            command[1] = temp;
            execute_cd(command, 2, dir_init);
            strcpy(dir_store, dir);
            return;
        }
        parse = strstr(command[1], "./");
        if (parse)
        {
            int len = strlen(parse);
            command[1] = ".";
            execute_cd(command, 2, dir_init);
            char temp[len - 2];
            strcpy(temp, &parse[2]);
            command[1] = temp;
            execute_cd(command, 2, dir_init);
            strcpy(dir_store, dir);
            return;
        }

        if (strcmp(command[1], cmd_handler[0]) == 0)
        {
            getcwd(dir_store, N);
        }
        else if (strcmp(command[1], cmd_handler[1]) == 0)
        {
            // printf("ggggg\n");
            getcwd(dir_store, N);
            strcpy(dir, dir_store);
            char *pos_slash = strrchr(dir, '/');
            char *new_dir = malloc(N);
            int len = strlen(dir);
            int val = pos_slash - dir;
            if (pos_slash)
            {
                strncpy(new_dir, dir, val);
                // printf("%s\n",new_dir);
                chdir(new_dir);
            }
        }
        else if (strcmp(command[1], cmd_handler[2]) == 0)
        {
            getcwd(dir_store, N);
            chdir(dir_init);
        }
        else if (strcmp(command[1], cmd_handler[3]) == 0)
        {
            chdir(dir_store);
            printf("%s\n", dir_store);
        }
        else if (chdir(command[1]) != 0)
            perror("issue in cd command");
        else
        {
            strcpy(dir_store, dir);
            chdir(command[1]);
        }
    }
}
