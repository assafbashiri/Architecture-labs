#include "util.h"
#include <dirent.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SYS_GETDENTS 141
#define BUF_SIZE 1024 

int pflag = 0, aflag = 0, dflag = 0;  
char *input;
char *output;
int in_param = 0;
int out_param = 1;

typedef struct dirent0{
    int inode;
    int offset;
    short d_reclen;
    char d_name[1];
} dirent0 ;
/*

void justPrint_user(){
    char buff[1] = "_";
    while(buff[0] != "\n"){
        system_call(SYS_READ , in_param , buff , 1);
        system_call(SYS_WRITE , out_param , buff , 1);
    }
}
void justPrint_file(){
    int size = 1;
    char buff[1] = "_";
    while(size > 0){
        size = system_call(SYS_READ , in_param , buff , 1);
        if (size == 0)
        {
            break;
        }
        
        system_call(SYS_WRITE , out_param , buff , 1);
    }
}

void encode_user(){
    char buff[1] = "_";
    while(buff[0] != "\n"){
        system_call(SYS_READ , in_param , buff , 1);
        if (buff[0] <=  'Z' && buff[0] >= 'A')
        {
            buff[0] = buff[0]+32;
            
        }
        
        system_call(SYS_WRITE , out_param , buff , 1);

    }
}

void encode_file(){
    int size = 1;
    char buff[1] = "_";
    while(size != 0){
        size = system_call(SYS_READ , in_param , buff , 1);
        if (buff[0] <=  'Z' && buff[0] >= 'A')
        {
            buff[0] = buff[0]+32;
            
        }
        if (size == 0)
        {
            break;
        }
        system_call(SYS_WRITE , out_param , buff , 1);

    }
}
*/
void detact_flags(int argc , char *argv[]){
    int i = 1;
        for (i = 1; i < argc; i++)
        {
            if (strncmp(argv[i] , "-p" , 2) == 0)
            {
                pflag = 1;
                input = argv[i]+2;
            }
            if (strncmp(argv[i] , "-a" , 2) == 0)
            {
                aflag = 1;
                output = argv[i];
            }
            if (strncmp(argv[i]+2 , "-D" , 2) == 0)
            {
                dflag = 1;
            }
            
            
            
            
            
        }
}
/*
void open_files(int argc , char *argv[]){
    if (inflag != 0)
    {
        in_param = system_call(SYS_OPEN ,input+2 , 0 , 0777);
    }
    if (outflag != 0)
    {
        out_param = system_call(SYS_OPEN , output+2 , 1 , 0777);
    }
    /*
    char *str = itoa(in_param);
        system_call(SYS_WRITE , STDOUT , input , 2);
    system_call(SYS_WRITE , STDOUT , "\n" , 1);
    
}


void close_files(int argc , char *argv[]){
    if (inflag != 0)
    {
        in_param = system_call(SYS_CLOSE ,in_param , 0 , 0777);
    }
    if (outflag != 0)
    {
        out_param = system_call(SYS_OPEN , out_param , 1 , 0777);
    }
        
}
*/

int main (int argc , char* argv[], char* envp[]){
char *flag = "0";
    if (argc >1)
    {
        detact_flags(argc , argv);
    }
    /*open_files(argc , argv);*/
    if (dflag == 1)
    {
        /*
        if (inflag == 0)
        {
            encode_user();
        }
        else
        {
            encode_file();
        }
        */
        
        
    }
    else
    {
        /*
        if (inflag == 0)
        {
            justPrint_user();
        }
        else
        {
            justPrint_file();
        }
        */
        
    }

    
    
    
  
close_files(argc , argv);
return 0;
}