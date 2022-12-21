#include "headers.h"
void execute_pwd(char **command)
{
    char *cur_wd = malloc(N);
    getcwd(cur_wd, N);
    strcpy(dir_store, cur_wd);
    printf("%s\n", cur_wd);
   // fprintf(stderr,"%s\n",cur_wd);
}