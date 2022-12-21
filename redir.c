#include "headers.h"
char *redir(char *command)
{
    char *tmp=malloc(M);
    strcpy(tmp,command);
    char *array[M];
    int i = 0;
    int in=-1, out=-1;
    int gg = -1; 
 //   printf("jjjjjjjj\n");
    array[i] = strtok(command, " ");
    while (array[i] != NULL)
    {
        if (strcmp(array[i], "<") == 0)
        {
            in = i;
        }
        else if (strcmp(array[i], ">") == 0)
        {
            out = i;
        }
        else if (strcmp(array[i], ">>") == 0)
        {
            gg = 0;
            out = i;
        }
        array[++i] = strtok(NULL, " ");
    }
  //  printf("hhhhhhh\n");
    if(out == -1)
        out = i + 1;
    if (in > out)
    {
        printf("syntax error\n");
         return "";
    }

//printf("i %d\n",i);
    if (out < i)
    {
        int fd;

        if (gg == 0)
            fd = open(array[out + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(array[out + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
          //printf("fd %d\n",fd);
        if (fd < 0)
            printf("Error in opening file\n");
        else {
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            close(fd);
            return "";
        }
        close(fd);
        }
        //printf("grgrgrgrrg\n");
    }
    else if (out == i || in == 0)
        return "";
//printf("harrrrrrr\n");
    char *temps=malloc(M);
    strcpy(temps, "");
    int len=0;
    int length=strlen(tmp);
    if(out<i&&in<=0){
    //    fprintf(stderr,"%s\n","jjjjjjj");
    for (int k = out; k < i; k++)
    {
      //  fprintf(stderr,"%s\n",array[k]);
        len+=strlen(array[k]);

    }
    strncpy(temps,tmp,length-(len+1));
    }
     if (in > 0&&out >=i)
    {
        //printf("57\n");
        //printf("%d\n",in);
     //   fprintf(stderr,"%s\n","jjjjjjjgggg");
        for(int k=0;k<i;k++) {
            //if(k>=i && k < last-1) strcat(temps," ");
            if(strcmp(array[k],"<")!=0) {
                strcat(temps,array[k]);
                strcat(temps," ");
            }
        }
  
    }
 else if(out <i && in >0) {
// fprintf(stderr,"%s\n","jjjjjjjhhhhhhhh");
    //   for(int k=0;k<i;k++) {
    //         if(strcmp(array[k],"<")==0||strcmp(array[k],">")==0||strcmp(array[k],">>")==0) ;
    //         else{
    //             strcat(temps,array[k]);
    //             strcat(temps," ");
    //         }
    //     }
    for(int k=0;k<out;k++) {
        if(strcmp(array[k],"<")!=0) strcat(temps,array[k]);
        strcat(temps," ");
    }
}
//fprintf(stderr,"%s\n",temps);
    return temps;
}
