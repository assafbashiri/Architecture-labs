#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "LineParser.h"
//#include "LineParser.c"
#include "linux/limits.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/wait.h>
#define TERMINATED  -1
#define RUNNING 1
#define SUSPENDED 0
#ifndef NULL
    #define NULL 0
#endif
#define SIZE 20
#define FREE(X) if(X) free((void*)X)
int dflag = 0;
int status;
pid_t first;
pid_t second; 

void waitForChildren() { 
    if(dflag == 1)
        fprintf(stderr, "parent_process>waiting for child processes to terminate…\n");
   
    if(waitpid(first, &status, 0) == -1) { // wait for termination of first child
         perror("error-waitpid 1");
         exit(1);
    } 
    if(waitpid(second, &status, 0) == -1) { // wait for termination of second child
         perror("error-waitpid 1");
         exit(1);
    } 
}



void detect_flags(int argc, char** argv)
{
    for (int i=1;i<argc;i++)
    {
        if (strncmp(argv[i], "-d", 2)==0)
        {
            dflag = 1;
        }
    }
}
void run_child_1(int *fd){
    char *comand[3] = {"ls" , "-l" , NULL};
    if(dflag == 1)
        fprintf(stderr, "child1>redirecting stdout to the write end of the pipe…\n");
    close(1);
    int new_pipe1 = dup(fd[1]);
    close(fd[1]);
    if(dflag == 1)
        fprintf(stderr, "child1>going to execute cmd: …\n");
    if(execvp(comand[0] , comand)==-1) //execvp failed
        {
        printf("%s\n" , "bad2");
        perror("execvp - child");
        exit(1);
        }
}
void run_child_2(int *fd){
    char *comand[4] = {"tail" , "-n" , "2"  , NULL};
    if(dflag == 1)
        fprintf(stderr, "child2>redirecting stding to the read end of the pipe…\n");
    close(0);
    int new_pipe2 = dup(fd[0]);
    close(fd[0]);
    if(dflag == 1)
        fprintf(stderr, "child2>going to execute cmd: …\n");
    if(execvp(comand[0] , comand)==-1) //execvp failed
    {
        printf("%s\n" , "bad3");
        perror("execvp - child");
        exit(1);
    }
}


void execute(){
    int fd[2];
    int num;
    if (num =  pipe(fd) == -1 )
    {
        printf("%s\n" , "bad1");
        perror("pipe -error");
        exit(1);
    }
    if(dflag == 1)
        fprintf(stderr, "parent_process>forking…\n");
    if((first = fork()) == -1){
        perror("erroe in forking");
        exit(1);
    }
    if (first == 0)
    {
        if(dflag == 1){
            fprintf(stderr, "parent_process>created process with id: %d\n", getpid());
        }
        run_child_1(fd);
    }
    if(dflag == 1)
            fprintf(stderr, "parent_process>closing the write end of the pipe…\n");
    close(fd[1]);
    if((second = fork()) == -1){
        perror("erroe in forking");
        exit(1);
    }       
    if (second == 0)
    {
        if(dflag == 1){
            fprintf(stderr, "parent_process>created process with id: %d\n", getpid());
        }
        run_child_2(fd);
    }
    if(dflag == 1)
                fprintf(stderr, "parent_process>closing the read end of the pipe…\n");
    close(fd[0]);
    waitpid(first , NULL ,0);
    waitpid(second , NULL , 0);
    
}







int main (int argc, char** argv)
{
    detect_flags(argc , argv);
    execute();
    
    return 0;
}
