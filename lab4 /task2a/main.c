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

int inflag = 0, outflag = 0, dflag = 0;  
char *input;
char *output;
int in_param = 0;
int out_param = 1;
int fd;
int dflag;

typedef struct dirent0{
    int inode;
    int offset;
    short d_reclen;
    char d_name[1];
} dirent0;

enum{
    DT_UNKNOWN = 0,
# define DT_UNKNOWN	DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO	DT_FIFO
    DT_CHR = 2,
# define DT_CHR		DT_CHR
    DT_DIR = 4,
# define DT_DIR		DT_DIR
    DT_BLK = 6,
# define DT_BLK		DT_BLK
    DT_REG = 8,
# define DT_REG		DT_REG
    DT_LNK = 10,
# define DT_LNK		DT_LNK
    DT_SOCK = 12,
# define DT_SOCK	DT_SOCK
    DT_WHT = 14
# define DT_WHT		DT_WHT
};

char* parse_file_type(char d_type) { /* function that returns the name of the file type */
    if(d_type == DT_REG)
        return "regular";
    else if(d_type == DT_DIR)
        return "directory";
    else if(d_type == DT_FIFO)
        return "FIFO";
    else if(d_type == DT_SOCK)
        return "socket";
    else if(d_type == DT_LNK)
        return "symlink";
    else if(d_type == DT_BLK)
        return "block dev";
    else if(d_type == DT_CHR)
        return "char dev";
    else
        return "bla-bla";
}


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
        in_param = system_call(SYS_CLOSE ,in_param , 0 , 0777);
    }
    if (outflag != 0)
    {
        out_param = system_call(SYS_OPEN , out_param , 1 , 0777);
    }
        
}
void parse(int fd , char *buff){
    int runner = 0;
    int count = 0;
    char d_type;
    struct dirent0 *ent;
    count = system_call(SYS_GETDENTS , fd , buff , 8192);
    if (count <= 0)
    {
        system_call(1 , 0x55 , "error-get");
    }
    while(runner < count){
        ent = (struct dirent0 *) (buff + runner); 
        d_type = *(buff + runner + ent->d_reclen - 1);
        system_call(SYS_WRITE ,STDOUT , ent->d_name , strlen(ent->d_name));
        system_call(SYS_WRITE , STDOUT , "\n" , 1);
        runner = runner + ent->d_reclen;
    }


}

int main (int argc , char* argv[], char* envp[]){
char *flag = "0";
    if (argc >1)
    {
        detact_flags(argc , argv);
    }
    char buf[BUF_SIZE];
    fd = system_call(SYS_OPEN , "." , 0 , 0777);
    if (fd <= 0)
    {
        system_call(1 , 0x55 , "error-open");
    }
    parse(fd , buf);
    
return 0;
}