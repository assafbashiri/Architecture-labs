#include "util.h"

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
int inflag = 0, outflag = 0, dflag = 0;  
char *input;
char *output;
int in_param = 0;
int out_param = 1;


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

void detact_flags(int argc , char *argv[]){
    int i = 1;
        for (i = 1; i < argc; i++)
        {
            if (strncmp(argv[i] , "-i" , 2) == 0)
            {
                inflag = 1;
                input = argv[i];
            }
            if (strncmp(argv[i] , "-o" , 2) == 0)
            {
                outflag = 1;
                output = argv[i];
            }
            if (strncmp(argv[i] , "-D" , 2) == 0)
            {
                dflag = 1;
            }
            
            
            
            
            
        }
}
void open_files(int argc , char *argv[]){
    if (inflag != 0)
    {
        in_param = system_call(SYS_OPEN ,input+2 , 0 , 0777);
    }
    if (outflag != 0)
    {
        out_param = system_call(SYS_OPEN , output+2 , 1 , 0777);
    }
}

void close_files(int argc , char *argv[]){
    if (inflag != 0)
    {
        in_param = system_call(SYS_CLOSE ,in_param);
    }
    if (outflag != 0)
    {
        out_param = system_call(SYS_CLOSE , out_param);
    }
}

int main (int argc , char* argv[], char* envp[]){
char *flag = "0";
    if (argc >1)
    {
        detact_flags(argc , argv);
    }
    open_files(argc , argv);
    if (dflag == 1)
    {
        if (inflag == 0)
        {
            encode_user();
        }
        else
        {
            encode_file();
        }
        
        
    }
    else
    {
        if (inflag == 0)
        {
            encode_user();
        }
        else
        {
            encode_file();
        }
        
    }

    
    
    
  
close_files(argc , argv);
return 0;
}