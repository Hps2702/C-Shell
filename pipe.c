#include "headers.h"
int last=0;
 int flag_out=0;
void pipe_execution(int in, int out, char command[])
{   
    // for(int i=0;i<strlen(command);i++){
    //   if(command[i]=='<'||command[i]=='>') {
    //       fprintf(stderr,"%s\n","pipipipiop");
    //       redir(command);
    //       return;
    //   }
    // }
    int pid = fork();
    if(pid<0) perror("error in forking");
    if (pid == 0)//child
    {
        if (in != 0)//redirecting input
        {
            dup2(in, 0);
            close(in);
        }

        if (out != 1 && last == 0&&flag_out==0)//redirecting output
        {
            dup2(out, 1);
            close(out);
        }
        char *flag[M];
      //  int num_flags = 0;
         int i=0;
         flag[i]=strtok(command," ");
        while (flag[i] != NULL)
        {
            i++;
            flag[i]=strtok(NULL," ");
        }
        // if (strcmp(flag[0], "pinfo") == 0)
        //     pinfo(num_flags, flag);
        // else if (strcmp(flag[0], "jobs") == 0)
        //     jobs(num_flags, flag);
        // else
            execvp(flag[0], flag); //if execvp() fails then next lines of code will be execeuted
        perror("");
        exit(0);
    }

    else //parent
    {
        int status;
        waitpid(pid, &status, 0);
        return;
    }
}

void execute_pipe(char command[])
{
    //tokenizing pipes and storing pipe seperated commands in piped_commands
    last = 0;
    char *piped_commands[M];   
    int i=0;
    piped_commands[i]=strtok(command,"|");
    while (piped_commands[i] != NULL)
    {    
        i++;
        piped_commands[i] = strtok(NULL, "|");
    }
    int flides[2], in = 0;
   flag_out=0;
  //executing each piped command with i/o redirection
    for (int j = 0; j < i; j++)
    {
        if (j == i - 1)
            last = 1;
                char pipe_array[strlen(piped_commands[j])];
        for(int k=0;k<strlen(piped_commands[j]);k++){
            if(piped_commands[j][k]=='<') pipe_array[k]=' ';
            else pipe_array[k]=piped_commands[j][k];
            if(pipe_array[k]=='>') flag_out=1;
        }
        pipe_array[strlen(piped_commands[j])]='\0';
        char *temp=strstr(pipe_array,">");
            if(temp) {
            char array[strlen(temp)-1];
            strcpy(array,&temp[1]);
         
       int c;
            for(int k=0;k<strlen(array);k++){
                if(array[k]==' ') c++;
                else if(array[k]!=' ') break;
            }
                 char a_space[M-c];
                 strcpy(a_space,&array[c]);
                 //   printf("hppp %s\n",a_space);
                      //  printf("len %ld\n",strlen(array));
            int fd=open(a_space,O_CREAT| O_WRONLY | O_TRUNC, 0644);
            dup2(fd,STDOUT_FILENO);
          //  printf("vaaaaaaaaaaaaaaaaa");
            close(fd);
            // printf("val %d\n",fd);
            // flides[1]=fd;
        }
        char array[M];
        int k;
        for(k=0;k<strlen(pipe_array);k++){
            if(pipe_array[k]=='>') break;
            array[k]=pipe_array[k];
        }
        strcpy(pipe_array,array);
        //printf("val %d\n",fd);
            // flides[1]=fd;
        pipe_array[k]='\0';
        if (pipe(flides) < 0)
        {
            perror("Error in creating pipe");
        }
        pipe_execution(in, flides[1], pipe_array);//sending the file descriptors for input and output of files
        in = flides[0];
        close(flides[1]);
    }
}