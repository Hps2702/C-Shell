#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <limits.h>
#define N 100000
#define M 10000
#define filesize 1000
char dir_store[N];
int check[5];
int checkfd;
char *back_ground[10000000];
char pid_array[1000];
int s ,fbg;
int tim;
time_t t1, t2;
int f1,f2,f3;
char *redir(char *command);
void execute_discover(char **command, int no_of_words, char *curdir_init, char *dir_init, char mess[], int flag);
void execute_pwd(char **command);
void signalhandler();
int fg_function(char *ans);
void execute_echo(char **command, int no_of_words);
void execute_pinfo(char **command, int no_of_words, char *dir_init);
int history_store(char *add_command, char command[21][M], int no_of_words);
void print_history(char command[21][M], int no_of_words);
void call_func(char **command, char *path_init, char *dir_init, char mess[], int val);
void give_permissions(char *command, char **array, int val);
void sort_colour(char **file, char *dir, int size);
void execute_ls(char **command, int no_of_words, char *dir_init, int var[]);
void execute_cd(char **command, int no_of_words, char *dir_init);
void execute_pipe(char *command);
void pipe_execution(int in, int out, char *command);