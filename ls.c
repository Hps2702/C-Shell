#include "headers.h"
int cmpfunc(const void *a, const void *b)
{
    const char **_a = (const char **)a;
    const char **_b = (const char **)b;
    return strcasecmp(*_a, *_b);
}
void give_permissions(char *command, char **array, int val)
{
    qsort(array, val, sizeof(char *), cmpfunc);
    char path[M];
    strcat(command, "/");
    //  printf("%s\n",command);
    char cmd[5] = {'d', 'r', 'w', 'x', '-'};
    for (int i = 0; i < val; i++)
    {
        // int color=-1;
        strcpy(path, command);
        strcat(path, array[i]);
        //  printf("%s\n",path);
        struct stat f = {0};
        if (stat(path, &f) == 0)
        {
            if (S_ISDIR(f.st_mode))
            {
                printf("%c", cmd[0]);
                //  color=1;
            }
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IRUSR)
                printf("%c", cmd[1]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IWUSR)
                printf("%c", cmd[2]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IXUSR)
            {
                printf("%c", cmd[3]);
                // color=2;
            }
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IRGRP)
                printf("%c", cmd[1]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IWGRP)
                printf("%c", cmd[2]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IXGRP)
                printf("%c", cmd[3]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IROTH)
                printf("%c", cmd[0]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IWOTH)
                printf("%c", cmd[2]);
            else
                printf("%c", cmd[4]);
            if (f.st_mode & S_IXOTH)
                printf("%c", cmd[3]);
            else
                printf("%c", cmd[4]);
            printf("\t");
            char mtime[80];
            time_t t = f.st_mtime;
            struct tm lt;
            localtime_r(&t, &lt);
            strftime(mtime, sizeof mtime, "%b %d %Y %H:%M", &lt);
            struct passwd *pw = getpwuid(f.st_uid);
            struct group *gr = getgrgid(f.st_gid);
            printf("%ld\t", f.st_nlink);
            printf("%s %s %ld %s ", pw->pw_name, gr->gr_name, f.st_size, mtime);
            if (S_ISDIR(f.st_mode))
            {
                 if(checkfd!=1){
                printf("\033[0;34m");
                printf("%s\n", array[i]);
                printf("\033[0m");
                }
                else printf("%s\n",array[i]);
                // printf("%s\n", array[i]);
            }
            else if (f.st_mode & S_IXUSR)
            {
                if(checkfd!=1){
                printf("\033[0;32m");
                printf("%s\n", array[i]);
                printf("\033[0m");
                }
                else printf("%s\n",array[i]); 
                           }
            else
                printf("%s\n", array[i]);
        }
    }
}
void sort_colour(char **file, char *dir, int size)
{
    // printf("Hhhh\n");
    // printf(Hhhhssss\n");
    qsort(file, size, sizeof(char *), cmpfunc);
    //   for(int i=0;i<size;i++) printf("%s\n",file[i]);
    char dire[M];
    // printf("vaaaaaaa\n");
    for (int i = 0; i < size; i++)
    {
        strcpy(dire, dir);
        strcat(dire, "/");
        strcat(dire, file[i]);
        //  printf("%s\n", dire);
        struct stat d = {0};
        if (stat(dire, &d) == 0)
        {
            if (S_ISDIR(d.st_mode))
            {
                // printf("isdir");
                if(checkfd!=1){
                printf("\033[0;34m");
                printf("%s\n", file[i]);
                printf("\033[0m");
                }
                else printf("%s\n",file[i]);
            }
            else if (d.st_mode & S_IXUSR)
            {
              
               if(checkfd!=1){
                printf("\033[0;32m");
                printf("%s\n", file[i]);
                printf("\033[0m");
                }
                else printf("%s\n",file[i]);  // printf("isfile");
               
            }
            else
                printf("%s\n", file[i]);
        }
    }
}
void execute_ls(char **command, int no_of_words, char *dir_init, int var[])
{
    // printf("%s\n",command[1]);
    //   printf("%d\n",no_of_words);

    // for (int i = 0; i < 8; i++)  printf("%d ", var[i]);
    struct dirent *files;
    DIR *dir;
    char *file[filesize];
    int cnt = 0;
    if (no_of_words == 1)
    {
        dir = opendir("."); // ls
        while ((files = readdir(dir)) != NULL)
        {
            if (files->d_name[0] != '.')
            {
                file[cnt] = files->d_name;
                cnt++;
                // printf("%s\n", files->d_name);
            }
        }
        char direc[M];
        getcwd(direc, M);
        sort_colour(file, direc, cnt);
        closedir(dir);
    }
    else if (no_of_words == 2)
    {
        //  printf("hhhh\n");
        if (var[7] == 1)
        {

            if (var[1] == 1 && var[0] == 0) // ls -l
            {
                dir = opendir(command[1]);
                if (dir == NULL)
                {
                    FILE *fpath = fopen(command[1], "r");
                    if (fpath == NULL)
                        printf("no such directory or file exists\n");
                    else
                    {
                        //  printf("hhhh\n");
                        char *file[filesize];
                        file[0] = command[1];
                        char dire[M];
                        getcwd(dire, M);
                        //   strcat(dire,"/");
                        //  strcat(dire,command[1]);
                        //  printf("hhhhhhhhhhhh\n");
                        give_permissions(dire, file, 1);
                        return;
                    }
                }
                else
                {
                    // printf("%s\n",dir);
                    int total = 0;
                    char *dire, *abs_dir;
                    char *file[filesize];
                    dire = malloc(M);
                    abs_dir = malloc(M);
                    int cnt = 0;
                    while ((files = readdir(dir)) != NULL)
                    {
                        struct stat directory = {0};
                        char *direc = malloc(M);
                        strcpy(direc, dir_init);
                        strcat(direc, "/");
                        strcat(direc, command[1]);
                        strcat(direc, "/");
                        strcpy(abs_dir, direc);
                        strcat(abs_dir, files->d_name);
                        // printf("%s\n",abs_dir);
                        if (files->d_name[0] != '.')
                        {
                            file[cnt] = files->d_name;
                            cnt++;

                            if (files->d_name[0] != '.')
                                if (stat(abs_dir, &directory) == 0)
                                    total += directory.st_blocks;
                        }
                    }

                    printf("total %d\n", total / 2);
                    char *direc = getcwd(dire, M);
                    strcat(direc, "/");
                    strcat(direc, command[1]);
                    // printf("%s\n",direc);
                    give_permissions(direc, file, cnt);
                    closedir(dir);
                    return;
                }
            }
            if (var[0] == 1 && var[1] == 0)
            {

                dir = opendir(command[1]); // ls -a
                if (dir == NULL)
                {
                    FILE *fpath = fopen(command[1], "r");
                    if (fpath == NULL)
                        printf("no such directory or file exists\n");
                    else
                    {
                        //  printf("hhhh\n");
                        //   strcat(dire,"/");
                        //  strcat(dire,command[1]);
                        //  printf("hhhhhhhhhhhh\n");
                        //    give_permissions(dire,file,1);
                        printf("%s\n", command[1]);
                        return;
                    }
                }
                else
                {
                    printf("%s:\n", command[1]);
                    char *file[filesize];
                    int cnt = 0;
                    while ((files = readdir(dir)) != NULL)
                    {
                        file[cnt] = files->d_name;
                        cnt++;
                        //  printf("%s\n", files->d_name);
                    }
                    char temp[M], temp1[M];
                    getcwd(temp, M);
                    strcat(temp, "/");
                    strcat(temp, command[1]);
                    sort_colour(file, temp, cnt);
                    closedir(dir);
                    return;
                }
                if (var[0] == 1 && var[1] == 1)
                {
                    dir = opendir(command[1]);
                    if (dir == NULL)
                    {
                        FILE *fpath = fopen(command[1], "r");
                        if (fpath == NULL)
                            printf("no such directory or file exists\n");
                        else
                        {
                            //  printf("hhhh\n");
                            char *file[filesize];
                            file[0] = command[1];
                            char dire[M];
                            getcwd(dire, M);
                            //   strcat(dire,"/");
                            //  strcat(dire,command[1]);
                            //  printf("hhhhhhhhhhhh\n");
                            give_permissions(dire, file, 1);
                            return;
                        }
                    }
                    else
                    {
                        int total = 0;
                        char *dire, *abs_dir;
                        char *file[filesize];
                        dire = malloc(M);
                        abs_dir = malloc(M);
                        int cnt = 0;
                        while ((files = readdir(dir)) != NULL)
                        {
                            struct stat directory = {0};
                            char *direc = malloc(M);
                            strcpy(direc, dir_init);
                            strcat(direc, "/");
                            strcat(direc, command[1]);
                            strcat(direc, "/");
                            strcpy(abs_dir, direc);
                            strcat(abs_dir, files->d_name);
                            file[cnt] = files->d_name;
                            cnt++;
                            if (stat(abs_dir, &directory) == 0)
                                total += directory.st_blocks;
                        }

                        printf("total %d\n", total / 2);
                        char *direc = getcwd(dire, M);
                        strcat(direc, "/");
                        strcat(direc, command[1]);
                        give_permissions(direc, file, cnt);
                        closedir(dir);
                        return;
                    }
                }
            }
            else
            {

                dir = opendir(command[1]);
                if (dir == NULL)
                {
                    FILE *fpath = fopen(command[1], "r");
                    if (fpath == NULL)
                        printf("no such directory or file exists\n");
                    else
                    {
                        char path[M];
                        //   getcwd(path,M);
                        //  strcat(path,"/");
                        // strcat(path,command[1]);
                        printf("%s\n", command[1]);
                    }
                }
                else
                {
                    int cnt = 0;
                    char *file[filesize];
                    printf("%s:\n", command[1]);
                    while ((files = readdir(dir)) != NULL)
                        if (files->d_name[0] != '.')
                        {
                            file[cnt] = files->d_name;
                            cnt++;
                            // printf("%s\n", files->d_name);
                        }
                    // qsort(file, cnt, sizeof(char *), cmpfunc);
                    // for(int i=0;i<cnt;i++) printf("%s\n",file[i]);
                    char dire[M];
                    getcwd(dire, M);
                    strcat(dire, "/");
                    strcat(dire, command[1]);
                    sort_colour(file, dire, cnt);
                }
                closedir(dir);
            }
        }
        else if (var[7] != 1)
        {
            if (var[2] == 1)
            {
                execute_ls(command, 1, dir_init, var); // ls .
                return;
            }
            if (var[3] == 1)
            {
                dir = opendir("./.."); // ls ..
                int cnt = 0;
                char *file[filesize];
                while ((files = readdir(dir)) != NULL)
                {
                    if (files->d_name[0] != '.')
                    {
                        file[cnt] = files->d_name;
                        cnt++;
                        // printf("%s\n", files->d_name);
                    }
                }
                char temp[M], temp1[M];
                getcwd(temp, M);
                chdir("./..");
                getcwd(temp1, M);
                sort_colour(file, temp1, cnt);
                chdir(temp);
                closedir(dir);
                return;
            }
            if (var[0] == 1)
            {
                // printf("lll\n");
                dir = opendir("."); // ls -a
                int cnt = 0;
                char *file[filesize];

                while ((files = readdir(dir)) != NULL)
                {
                    file[cnt] = files->d_name;
                    cnt++;
                    // printf("%s\n", files->d_name);
                }
                char temp[M], temp1[M];
                getcwd(temp, M);
                chdir(".");
                getcwd(temp1, M);
                sort_colour(file, temp1, cnt);
                chdir(temp);
                closedir(dir);
                return;
            }
            if (var[1] == 1) // ls -l
            {
                // printf("%s:\n",command[1]);
                dir = opendir(".");
                int total = 0;
                char *dire, *abs_dir;
                char *file[filesize];
                dire = malloc(M);
                abs_dir = malloc(M);
                int cnt = 0;
                while ((files = readdir(dir)) != NULL)
                {
                    struct stat directory = {0};
                    char *direc = getcwd(dire, M);
                    strcat(direc, "/");
                    strcpy(abs_dir, direc);
                    strcat(abs_dir, files->d_name);
                    // printf("%s\n",abs_dir);
                    if (files->d_name[0] != '.')
                    {
                        file[cnt] = files->d_name;
                        cnt++;

                        if (files->d_name[0] != '.')
                            if (stat(abs_dir, &directory) == 0)
                                total += directory.st_blocks;
                    }
                }

                printf("total %d\n", total / 2);
                char *direc = getcwd(dire, M);
                give_permissions(direc, file, cnt);
                closedir(dir);
                return;
            }
            if (var[4] == 1)
            {
                dir = opendir(dir_init);
                char *file[filesize];
                int cnt = 0;
                while ((files = readdir(dir)) != NULL)
                {
                    if (files->d_name[0] != '.')
                    {
                        file[cnt] = files->d_name;
                        cnt++;
                    }
                    //   printf("%s\n", files->d_name);
                }
                sort_colour(file, dir_init, cnt);
                closedir(dir);
                return;
            }
            if (var[5] == 1 || var[6] == 1)
            {
                dir = opendir(".");
                int total = 0;
                char *dire, *abs_dir;
                char *file[filesize];
                dire = malloc(M);
                abs_dir = malloc(M);
                int cnt = 0;
                while ((files = readdir(dir)) != NULL)
                {
                    struct stat directory = {0};
                    char *direc = getcwd(dire, M);
                    strcat(direc, "/");
                    strcpy(abs_dir, direc);
                    strcat(abs_dir, files->d_name);
                    file[cnt] = files->d_name;
                    cnt++;
                    if (stat(abs_dir, &directory) == 0)
                        total += directory.st_blocks;
                }

                printf("total %d\n", total / 2);
                char *direc = getcwd(dire, M);
                give_permissions(direc, file, cnt);
                closedir(dir);
                return;
            }
            else
            {
                dir = opendir(command[1]);
                if (dir == NULL)
                {
                    FILE *fpath = fopen(command[1], "r");
                    if (fpath == NULL)
                        printf("no such directory or file exists\n");
                    else
                    {
                        printf("%s\n", command[1]);
                    }
                }
                else
                {
                    int cnt = 0;
                    char *file[filesize];
                    printf("%s:\n", command[1]);
                    while ((files = readdir(dir)) != NULL)
                    {
                        if (files->d_name[0] != '.')
                        {
                            file[cnt] = files->d_name;
                            cnt++;
                            //  printf("%s\n", files->d_name);
                        }
                    }
                    char path[M];
                    getcwd(path, M);
                    strcat(path, "/");
                    strcat(path, command[1]);
                    sort_colour(file, path, cnt);
                    return;
                }
                closedir(dir);
            }
        }
    }
    else
    {
        if (no_of_words == 3 && var[0] == 1 && var[1] == 1)
        {
            dir = opendir(".");
            int total = 0;
            char *dire, *abs_dir;
            char *file[filesize];
            dire = malloc(M);
            abs_dir = malloc(M);
            int cnt = 0;
            while ((files = readdir(dir)) != NULL)
            {
                struct stat directory = {0};
                char *direc = getcwd(dire, M);
                strcat(direc, "/");
                strcpy(abs_dir, direc);
                strcat(abs_dir, files->d_name);
                file[cnt] = files->d_name;
                cnt++;
                if (stat(abs_dir, &directory) == 0)
                    total += directory.st_blocks;
            }

            printf("total %d\n", total / 2);
            char *direc = getcwd(dire, M);
            give_permissions(direc, file, cnt);
            closedir(dir);
            return;
        }
        else
        {
            // printf("jjjj\n");
            for (int i = 1; i < no_of_words; i++)
            {
                // printf("%s\n",command[i]);
                // if (command[i] == '-a')
                //     command[1] = command[i];
                if (strcmp(command[i], "-a") == 0)
                    var[0] = 1;
                else if (strcmp(command[i], "-l") == 0)
                    var[1] = 1;
                else
                {
                    command[1] = command[i];
                    // printf("%s\n",command[1]);
                    var[7] = 1;
                    char dirg[M];
                    getcwd(dirg, M);
                    execute_ls(command, 2, dirg, var);
                }

                // execute_ls(command, 2, dir_init, var);
            }
        }
    }
}