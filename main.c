#include "headers.h"
char *back_ground[10000000] = {NULL};
int s = 0, fbg = 0;
int tim ;
int main(int argc, char *argv[])
{
    char *input_find,*output_find,*find;
    char buffer_directory[M], buffer_user[M], buffer_second_user[M];
    getcwd(buffer_directory, M);
    getlogin_r(buffer_user, M);
    gethostname(buffer_second_user, M);
    char histore[21][M];
    char temp[M];
    int var;
    FILE *fp = fopen("his_store.txt", "r");

    if (fp == NULL)
    {

        FILE *fp2 = fopen("his_store.txt", "w");
        fclose(fp2);
        fp = fopen("his_store.txt", "r");
    }

    int val = 0;
    while (fscanf(fp, "%[^\n]%*c", temp) != EOF)
    {

        strcpy(histore[val], temp);
        val++;
    }
    // printf("Ggggggggg\n");
    fclose(fp);

    while (1)
    {
        int times;
        int time=0;
         L7:     
        for (int i = 0; i < 5; i++)
            check[i] = 0;
        char abs_directory[N];
        getcwd(abs_directory, N);
        if (abs_directory != NULL)
        {
            // checkfg=-1;
            char *parse;
            int len = strlen(buffer_directory);
            parse = strstr(abs_directory, buffer_directory);
            if (time!=0)
            {
                if (parse)
                {
                    printf("<%s@%s:~%s took %ds>", buffer_user, buffer_second_user, &parse[len], time);
                }
                else
                {
                    printf("<%s@%s:%s took %ds>", buffer_user, buffer_second_user, abs_directory, time);
                }
            }
            else
            {
                if (parse)
                {
                    printf("<%s@%s:~%s>", buffer_user, buffer_second_user, &parse[len]);
                }
                else
                {
                    printf("<%s@%s:%s>", buffer_user, buffer_second_user, abs_directory);
                }
            }
            time = 0;
            
        }
        else
        {
            perror("error in reading current directory");
            exit(EXIT_FAILURE);
        }
        char input[N];
        // fgets(input, N, stdin);
        scanf("%[^\n]%*c", input);
        int strln = strlen(input);
        char inputs[N];
        strcpy(inputs, input);
        inputs[strln] = '\0';
        //     printf("%s\n",input);
        val = history_store(input, histore, val);
        char *input_args[N];
        char delims[] = "';','&'";
        // tok=strtok(input,delims);
         int gob = dup(1), gob1 = dup(0);
        int i = 0;
        char temp[M];
        strcpy(temp,input);
        temp[strln]='\0';
        input_find=strstr(temp,"<");
        output_find=strstr(temp,">");
        find=strstr(temp,">>");
        checkfd=0;
        f1=0,f2=0;
         if(input_find!=NULL || output_find!=NULL || find!=NULL) f1=1;
         if(strstr(input,"|")) f2=1;
         if(f1==1&&f2==1){
             f2=1,f1=0;
         }
         if(f2){
             ///fprintf(stderr,"%s\n","jjjjjjjjjjj");
         execute_pipe(input);
         dup2(gob, STDOUT_FILENO);
            close(gob);
            dup2(gob1, STDIN_FILENO);
            close(gob1);
         goto L7;
     }
     if(f1)   {
        // fprintf(stderr,"%s\n","kkkkkkkkkkk");
         checkfd=1;
         strcpy(input,redir(temp));
     }
    //  if(f3){

    //  }
     //char t[M];
     char inputfd[M];
     strcpy(inputfd,input);
  //   fprintf(stderr,"%s\n","main");
  //  fprintf(stderr,"%s\n",input);
        input_args[i] = strtok(input, delims);
        while (input_args[i] != NULL)
        {
           //  printf("%s\n",input_args[i]);
            i++;
            input_args[i] = strtok(NULL, delims);
           
        }
        //fprintf(stderr,"%d\n",i);
        for (int j = 0; j < i; j++)
        {
            fbg = 0;
            char *command_args[N];
            char del_ims[] = "' ','\t','\n'";
            int cnt = 0;
            command_args[cnt] = strtok(input_args[j], del_ims);
            while (command_args[cnt] != NULL)
            {
                cnt++;
                command_args[cnt] = strtok(NULL, del_ims);
              //   printf("%s\n",input_args[cnt]);
            }
         //   for(int k=0;k<cnt;k++) printf("kk %s\n",command_args[k]);
         //  fprintf(stderr,"125%s\n",command_args[0]);
            if (strcmp(command_args[0], "cd") == 0)
                execute_cd(command_args, cnt, buffer_directory);
            else if (strcmp(command_args[0], "echo") == 0)
                execute_echo(command_args, cnt);
            else if (strcmp(command_args[0], "pwd") == 0)
                execute_pwd(command_args);
            else if (strcmp(command_args[0], "ls") == 0)
            {
                int var[8] = {0};
                char cmd_handlers[][5] = {"-a", "-l", ".", "..", "~", "-a-l", "-al", "-la"};
                for (int i = 1; i < cnt; i++)
                {
                    for (int j = 0; j < 8; j++)
                        if (strcmp(command_args[i], cmd_handlers[j]) == 0)
                            var[j] = 1;
                }
                execute_ls(command_args, cnt, buffer_directory, var);
            }
            else if (strcmp(command_args[0], "history") == 0)
                print_history(histore, val);
            else if (strcmp(command_args[0], "pinfo") == 0)
                execute_pinfo(command_args, cnt, buffer_directory);
            else if (strcmp(command_args[0], "exit") == 0)
            {
                exit(0);
            }
            else if (strcmp(command_args[0], "discover") == 0)
            {
                char dire[M];
                getcwd(dire, M);
                char cmd_handler[][3] = {".", "..", "~", "-f", "-d"};
                for (int i = 1; i < cnt; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (strcmp(command_args[i], cmd_handler[j]) == 0)
                            check[j] = 1;
                        //  else check[6]++;
                    }
                }
                execute_discover(command_args, cnt, dire, buffer_directory, " ", 2);
            }
            // else if(strcmp(command_args[0],"jobs")==0){
            //     execute_jobs(command_args,cnt);
            // }
            else
            {
                // printf("%s\n",inputs);
                // printf("kkkkk\n");
                if(checkfd==1) {
                  
                   time= fg_function(inputfd);
                //    printf("%d\n",time);
                //    times=time;
                }
               else {
                    time=  fg_function(inputs);
                    // printf("%d\n",time);
                    // times=time;
               }
                //  goto L7;
            }
            dup2(gob, STDOUT_FILENO);
            close(gob);
            dup2(gob1, STDIN_FILENO);
            close(gob1);
           goto L7;
            
        }
    }
    return 0;
}