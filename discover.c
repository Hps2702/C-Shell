#include "headers.h"
void call_func(char **command, char *path_init, char *dir_init, char mess[], int val)
{
    //  printf("%s\n",path);
    struct dirent *files;
    DIR *dir;
    char directory[M];
    getcwd(directory, M);
    dir = opendir(path_init);
    char curdir[M];
    while ((files = readdir(dir)) != NULL)
    {
        strcpy(curdir, path_init);
        strcat(curdir, "/");
        // printf("%s\n",curdir);
        // printf("%s",files->d_name);
        strcat(curdir, files->d_name);
        struct stat store = {0};
        if (stat(curdir, &store) == 0)
        {
            if (val == 3)
            {
                if (S_ISDIR(store.st_mode))
                {
                    int len = strlen(directory);
                    char *parse = strstr(curdir, directory);
                    if (parse)
                    {
                        if (files->d_name[0] != '.')
                        {
                            // printf(".%s\n",&parse[len]);
                            // call_func(path_init,path,val);
                            call_func(command, curdir, dir_init, mess, val);
                            // return;
                        }
                    }
                }
                if (S_ISREG(store.st_mode) && (!strcmp(files->d_name, mess)))
                {

                    int len = strlen(directory);
                    char *parse = strstr(curdir, directory);
                    //   printf("fff %s\n",dir_init);
                    if (parse)
                        printf(".%s\n", &parse[len]);
                    else
                        printf("%s\n", curdir);
                    // printf("./%s\n",files->d_name);
                }
            }
            if (val == 2)
            {
                if (S_ISDIR(store.st_mode))
                {
                    // printf("%s\n",store.)
                    int len = strlen(directory);
                    char *parse = strstr(curdir, directory);
                    if (parse)
                    {
                        if (files->d_name[0] != '.')
                        {
                            printf(".%s\n", &parse[len]);
                            // call_func(path_init,path,val);
                            call_func(command, curdir, dir_init, mess, val);
                            // return;
                        }
                    }
                    else
                        printf("%s\n", curdir);
                }
                else if (S_ISREG(store.st_mode))
                {
                    int len = strlen(directory);
                    char *parse = strstr(curdir, directory);
                    if (parse)
                        printf(".%s\n", &parse[len]);
                    else
                        printf("%s\n", curdir);
                    // printf("./%s\n",files->d_name);
                }
            }
            if (val == 1)
            {
                // directory
                if (S_ISDIR(store.st_mode))
                {
                    // printf("%s\n",store.)
                    int len = strlen(directory);
                    char *parse = strstr(curdir, directory);
                    if (parse)
                    {
                        if (files->d_name[0] != '.')
                        {
                            printf(".%s\n", &parse[len]);
                            // call_func(path_init,path,val);
                            call_func(command, curdir, dir_init, mess, val);
                            // return;
                        }
                    }
                    else
                        printf("%s\n", curdir);
                }
            }
            // return;
        }
        if (val == 0)
        {
            // files
            if (S_ISREG(store.st_mode))
            {
                int len = strlen(directory);
                char *parse = strstr(curdir, directory);
                if (parse)
                    printf(".%s\n", &parse[len]);
                else
                    printf("%s\n", curdir);
                // printf("./%s\n",files->d_name);
            }
            if (S_ISDIR(store.st_mode))
            {
                // printf("%s\n",store.)
                int len = strlen(directory);
                char *parse = strstr(curdir, directory);
                if (parse)
                {
                    if (files->d_name[0] != '.')
                    {
                        // printf(".%s\n", &parse[len]);
                        // call_func(path_init,path,val);
                        call_func(command, curdir, dir_init, mess, 0);
                        // return;
                    }
                }
            }
        }
    }
}
void execute_discover(char **command, int no_of_words, char *curdir_init, char *dir_init, char mess[], int flag)
{
    //  printf("%s\n",curdir_init);
    // printf("%s\n",dir_init);

    //  for(int i=0;i<5;i++) printf("%d",check[i]);
    char curdir[M];
    // getcwd(curdir_init,M);
    if (no_of_words == 1)
    {
        // dir=opendir(".");
        // printf("jjjj\n");
        // printf("cur %s\n",curdir_init);
        call_func(command, curdir_init, dir_init, mess, flag);
    }
    else if (no_of_words == 2)
    {
        if (check[0] == 1)
        {
            execute_discover(command, 1, curdir_init, dir_init, mess, flag); //.
        }
        else if (check[1] == 1)
        {
            //     printf("GGGG\n");

            strcpy(curdir, curdir_init);
            // printf("dire %s\n",curdir);
            char *pos_slash = strrchr(curdir, '/'); //..
            // printf("parse %s\n",pos_slash);
            char new_dir[M];
            int len = strlen(curdir);
            int val = strlen(pos_slash);
            if (pos_slash)
            {
                // printf("bbb\n");
                strncpy(new_dir, curdir, len - val);
            }
            //   printf(" new %s\n",new_dir);
            //      printf(" new %s\n",dir_init);
            execute_discover(command, 1, new_dir, dir_init, mess, flag);
        }
        else if (check[2] == 1)
        {
            execute_discover(command, 1, dir_init, dir_init, mess, flag);
        }
        else if (check[3] == 1)
        {
            execute_discover(command, 1, curdir_init, dir_init, mess, 0);
        }
        else if (check[4] == 1)
        {
            execute_discover(command, 1, curdir_init, dir_init, mess, 1);
        }
        else
        {
            //  printf("debug\n");
            // printf("%s\n",command[1]);
            char tmp[M], temp[M], tp[M];
            getcwd(temp, M);
            strcpy(tmp, command[1]);
            strcpy(tp, temp);
            char *parse = strstr(command[1], "./");
            if (parse)
            {
                //   printf("var\n");
                strcat(temp, &tmp[1]);
            }
            else
            {
                strcat(temp, "/");
                strcat(temp, tmp);
            }
            //   printf("%s\n",temp);
            if (opendir(temp))
            {
                // printf("HHHHHH\n");
                execute_discover(command, 1, temp, dir_init, mess, 2);
                return;
            }

            else
            {
                //     printf("HHHH\n");
                int len = strlen(command[1]);
                // printf("%d",len);
                char mess[1000];
                strncpy(mess, &command[1][1], len - 2);
                mess[len - 2] = '\0';
                //  printf("mess %s\n",mess);
                // printf("==========\n");
                execute_discover(command, 1, tp, dir_init, mess, 3);
                return;
            }
            perror("error");
        }
    }
    else if (no_of_words >= 3)
    {
        if (check[0] == 1 && check[3] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 0);
            return;
        }
        if (check[0] == 1 && check[4] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 1);
            return;
        }
        if (check[1] == 1 && check[3] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 0);
            return;
            //  printf("%s\n",curdir_init);
            //  printf("%s\n",dir_init);
        }
        if (check[1] == 1 && check[4] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 1);
            return;
            //              printf("%s\n",curdir_init);
            //    printf("%s\n",dir_init);di
        }
        if (check[2] == 1 && check[3] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 0);
            return;
        }
        if (check[2] == 1 && check[4] == 1)
        {
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 1);
            return;
        }
        else if (check[0] == 1)
        {
            // execute_discover()
            // check[0]=0;
            check[0] = 0;
            if (strcmp(command[no_of_words - 1], ".") == 0)
                ;
            else
                command[1] = command[no_of_words - 1];
            execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 3);
            return;
        }
        else if (check[1] == 1)
        {
            // execute_discover()
            // check[0]=0;
            strcpy(curdir, curdir_init);
            // printf("dire %s\n",curdir);
            char *pos_slash = strrchr(curdir, '/'); //..
                                                    // printf("parse %s\n",pos_slash);
            char new_dir[M];
            int len = strlen(curdir);
            int val = strlen(pos_slash);
            if (pos_slash)
            {
                // printf("bbb\n");
                strncpy(new_dir, curdir, len - val);
            }
            // printf(" new %s\n",new_dir);
            char temp_dir[M];
            getcwd(temp_dir, M);
            chdir(new_dir);
            check[1] = 0;
            if (strcmp(command[no_of_words - 1], "..") == 0)
                ;
            else
                command[1] = command[no_of_words - 1];
            execute_discover(command, no_of_words - 1, new_dir, dir_init, mess, 3);
            chdir(temp_dir);
            return;
        }
        else if (check[2] == 1)
        {
            // execute_discover()
            // check[0]=0;
            char temp_dir[M];
            getcwd(temp_dir, M);
            chdir(dir_init);
            check[2] = 0;
            if (strcmp(command[no_of_words - 1], "~") == 0)
                ;
            else
                command[1] = command[no_of_words - 1];
            execute_discover(command, no_of_words - 1, dir_init, dir_init, mess, 3);
            chdir(temp_dir);
            return;
        }
        else if (check[3] == 1)
        {
            check[3] = 0;
            if (strcmp(command[no_of_words - 1], "-f") == 0)
                ;
            else
                command[1] = command[no_of_words - 1];
            //   printf("HHHHHH\n");
            char *parse = strstr(command[1], "./");
            char temp[M];
            strcpy(temp, command[1]);
            if (parse)
            {
                strcpy(command[1], &temp[2]);
            }
            if (opendir(command[1]))
            {
                strcat(curdir_init, "/");
                strcat(curdir_init, command[1]);
                //  printf("%s\n",curdir_init);
                call_func(command, curdir_init, dir_init, mess, 0);
                return;
                // execute_discover(command,no_of_words-1,curdir_init,dir_init,mess,0);
            }
            else if (strrchr(command[1], '"'))
            {
                char tmp[strlen(command[1]) - 2];
                strncpy(tmp, &temp[1], strlen(command[1]) - 2);
                command[1] = temp;
                execute_discover(command, no_of_words - 1, curdir_init, dir_init, mess, 0);
                return;
            }
            else
                perror("error");
        }
        else if (check[4] == 1)
        {
            check[4] = 0;
            if (strcmp(command[no_of_words - 1], "-d") == 0)
                ;
            else
                command[1] = command[no_of_words - 1];
            char *parse = strstr(command[1], "./");
            char temp[M];
            strcpy(temp, command[1]);
            if (parse)
            {
                strcpy(command[1], &temp[2]);
            }
            if (opendir(command[1]))
            {
                strcat(curdir_init, "/");
                strcat(curdir_init, command[1]);
                //  printf("%s\n",curdir_init);
                call_func(command, curdir_init, dir_init, mess, 1);
                return;
                // execute_discover(command,no_of_words-1,curdir_init,dir_init,mess,0);
            }

            else
                perror("error");
            //  execute_discover(command,no_of_words-1,curdir_init,dir_init,mess,1);
        }
    }
}