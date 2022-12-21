# include "headers.h"
void execute_pinfo(char **command, int no_of_words, char *dir_init)
{
    long int processId, garb, val;
    char value;
    char path[1000], array[1000], garbage[1000];
    if (no_of_words == 1)
    {
        processId = getpid();
    }
    else if (no_of_words == 2)
    {
        processId = atoi(command[1]);
    }
    printf("pid : %ld\n", processId);
    long long int tpgid = -1, pgrp = -1;
    sprintf(path, "/proc/%ld/stat", processId);
    FILE *fp1 = fopen(path, "r");
    fscanf(fp1, "%*s %*s %c %*s %lld %*s %*s %lld %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s", &value, &pgrp, &tpgid);
    if (pgrp == tpgid)
        printf("process status : %c+\n", value);
    else
        printf("process status : %c\n", value);

    fclose(fp1);
    sprintf(path, "/proc/%ld/statm", processId);
    FILE *fp2 = fopen(path, "r");
    fscanf(fp2, "%ld", &val);
    fclose(fp2);
    printf("memory : %ld\n", val);
    sprintf(path, "/proc/%ld/exe", processId);
    readlink(path, array, 1000);
    int len = strlen(dir_init);
    char *parse = strstr(array, dir_init);
    if (parse)
    {
        printf("executable path : %s\n", &parse[len]);
    }
    else
    {
        printf("executable path : %s\n", array);
    }
}
