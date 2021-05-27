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
int inflag = 0;
int outflag = 0;
char *in;
char*out;
FILE *in_descriptor;
FILE *out_descriptor;


int kill(pid_t pid, int sig);



typedef struct process{
    cmdLine* cmd;                         /* the parsed command line*/
    pid_t pid; 		                  /* the process id that is running the command*/
    int status;                           /* status of the process: RUNNING/SUSPENDED/TERMINATED */
    struct process *next;	                  /* next process in chain */
} process;

void freeProcessList(process* process_list)
{
    if (process_list!=NULL)
    {  
        freeCmdLines(process_list->cmd);
        freeProcessList(process_list->next);
        FREE(process_list);
        process_list=NULL;
    }
}

// struct fd_pair pipe();

void detect_flags(int argc, char** argv)
{
    for (int i=1;i<argc;i++)
    {
        if (strncmp(argv[i], "-d", 2)==0)
        {
            dflag = 1;
        }
        else if (strncmp(argv[i], "<",1 )==0)
        {
            inflag = 1;
            in = argv[i+1];
        }
        else if (strncmp(argv[i], ">", 1)==0)
        {
            outflag = 1;
            out = argv[i+1];
        }
    }
}
void open_files(){
    if (inflag == 1)
    {
        in_descriptor = fopen(in , "r+");
    }
    if (outflag == 1)
    {
        out_descriptor = fopen(out , "r+");
    }
    
}
void close_files(){
   if (inflag == 1)
    {
        fclose(in_descriptor);
    }
    if (outflag == 1)
    {
        fclose(out_descriptor);
    } 
}


void printDebugInf(cmdLine *pCmdLine)
{
    fprintf(stderr,"-----------------debug-------------------\n");
    fprintf(stderr,"%s%d\n", "PID: ",getpid());
    fprintf(stderr,"%s%s\n", "Executing command: ", pCmdLine->arguments[0]);
    fprintf(stderr,"-----------------debug-------------------\n");
}

int create_pipe(cmdLine *cmd, process** process_list){
    int fd[2];
    int num;
    char ans[1000];

    if (num =  pipe(fd) == -1 )
    {
        perror("pipe -error");
        exit(1);
    }
    int f = fork();
    if (f == 0)
    {
    
    printf("%s\n","in son");
    read(fd[0] , ans , 1000);
    printf("%s\n" , ans);
    //printf("%d\n" , fd[0]);
    //printf("%d\n" , fd[1]);
    //printf("%d" , f);
    freeCmdLines(cmd);
    freeProcessList(*process_list);
    _exit(0);
    }
    else
    {
        printf("%s\n","in father");
        char phrase[SIZE];
        char message[SIZE];
        printf("%s" , "please type a sentence : ");
        scanf("%s", phrase);
        //printf("%s\n" , phrase);
        //printf("%d\n%s\n" , f , "really?");
        write(fd[1] , phrase , sizeof(phrase));
    }
    
    return num;
    
}

void updateProcessList(process **process_list)
{
    process* curr=*process_list;
    int wait_res;
    int status;
    int statusToUpdate=RUNNING;
    while(curr!=NULL)
    {
        statusToUpdate=curr->status;
        wait_res=waitpid(curr->pid,&status, WNOHANG /*terminate*/| WUNTRACED /*stop*/ | WCONTINUED/*continue*/ );
        if (wait_res==-1)
        {
            statusToUpdate=TERMINATED;
        }
        if(wait_res!=0)
        {
            if (WIFEXITED(status) || WIFSIGNALED(status))//Terminated
            {
                statusToUpdate=TERMINATED;   
            }
            else if(WIFSTOPPED(status))//suspended
            {
                statusToUpdate=SUSPENDED; 
            }
            else if (WIFCONTINUED(status))
            {
                statusToUpdate=RUNNING;
            }
            updateProcessStatus(*process_list, curr->pid, statusToUpdate);
        }
        
        curr=curr->next;
    }
}

void updateProcessStatus(process* process_list, int pid, int status)
{
    process* curr=process_list;
    while(curr!=NULL && curr->pid!=pid)
    {
        curr=curr->next;
    }
    if (curr!=NULL)
    {
        curr->  status=status;
    }
    else
    {
        fprintf(stderr, "status not found");
    }
    
}

char* checkStatus(process* curr)
{
    int status;
    status=curr->status;
    return status == RUNNING ? "Running" : status == TERMINATED ? "Terminated" :  status == SUSPENDED ? "Suspended" : "fail";
}

void printProcessList(process** process_list)
{
    updateProcessList(process_list);
    printf("%s\t%s\t%s\n", "PID","Command", "STATUS");
    process* curr=*process_list;
    process* prev=NULL;

    while(curr!=NULL)
    {
        printf("%d\t%s\t%s\n", (curr)->pid,curr->cmd->arguments[0], checkStatus(curr));
        if(curr->status==TERMINATED && prev==NULL)//have to delete the first
        {

            freeCmdLines(curr-> cmd);
            *process_list=curr->next;
            free(curr);
            curr=*process_list;
           
        }
        else if(curr->status==TERMINATED)//delete not the first
        {
            freeCmdLines(curr->cmd);

            //deleting the curr node
            prev->next=curr->next;
            FREE(curr);
            curr=prev->next;
        }
        else
        {
            prev=curr;
            curr=(curr)->next;
        }
        
        
    }
    if (prev == NULL && curr==NULL)
    {
        *process_list=NULL;
    }
}

void addProcess(process** process_list, cmdLine* cmd, pid_t pid)
{
    process* toAdd = malloc(sizeof(process));
    toAdd->cmd=cmd;
    toAdd->next=NULL;
    toAdd->pid=pid;
    toAdd->status=RUNNING; //check
    if (*process_list==NULL)
    {
         *process_list=toAdd;
    }
    else
    {
        process* curr=*process_list;
        while (curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next = toAdd; 
    }
    
}


void execute(cmdLine *pCmdLine, process** process_list)
{   
    int pid;
    int pidSusRes;
    int pidKill;
    int status;
    int waitVal;
    int pidSuspend;
    int timeSuspend;
    int pidKillRes;
    int isSuspend;
    if (pCmdLine==NULL)
    {
        return;   
    }
    if(strncmp(pCmdLine->arguments[0], "cd", 2) == 0 )
    {
        if(chdir(pCmdLine->arguments[1])== -1 )
        {
            perror("cd");
        }
        freeCmdLines(pCmdLine);
    }
    else
    {
        pid = fork();
        if(pid!=-1)
        {
            if (pid==0)//child - the new process
            {
                open_files();
            
                if(execvp(pCmdLine->arguments[0],pCmdLine->arguments)==-1) //execvp failed
                {
                    perror("execvp - child");
                    freeProcessList(*process_list);

                    freeCmdLines(pCmdLine);
                    _exit(1);
                }

                freeCmdLines(pCmdLine);
                freeProcessList(*process_list);
                close_files();
                _exit(0);
            }
                       
            
            else //parent
            {
                
                
                

            }
            
        
        }
        else //fork failed
        {
            perror("fork"); 
        }
        
    }
    
   
}

int main (int argc, char** argv)
{
    int debugMode;
    process* process_list=NULL;
    struct cmdLine *cmd=NULL;
    char buf[PATH_MAX];
    char input[2048];
    detect_flags(argc, argv);
    while(1) //Will only stop if "quit" is entered by the user
    {        
        //int a = create_pipe(cmd,process_list);
       // printf("%d\n" , a);
        getcwd(buf, PATH_MAX);
        //printf("%s\n",buf);
        fgets(input,2048, stdin);
        if(strncmp(input, "quit", 4)==0) //Stopping Condition
        {
            //freeProcessList(process_list);
            exit(0);
        }
        cmd=parseCmdLines(input);
        //printf("%s\n" , cmd->inputRedirect);
        if(dflag==1)
        {
            printDebugInf(cmd);
        }
        execute(cmd,&process_list);
     
    }
    return 0;
}
