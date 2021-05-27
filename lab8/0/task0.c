#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define  NAME_LEN  128
#define  BUF_SZ    10000

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
struct stat fd_stat;
void *map_start;
Elf32_Ehdr *header;
int fd ;
int dflag = 0;

typedef struct {
  char debug_mode1;
  char file_name[NAME_LEN];
  int unit_size;
  unsigned char mem_buf[BUF_SZ];
  size_t mem_count;
  /*
   .
   .
   Any additional fields you deem necessary
  */
} state;

struct fun_desc {
  char *name;
  void (*fun)(state* s);
};
 
  void map(state * s, void (*f) (state*)){
  f(s);
}

void print_menu(struct fun_desc menu[]){


    for (int i = 0; i <= 5; i++)
    {
        printf("%d%c%s\n" , i , ')' , menu[i].name);
    }
}

void print_debug(state *s){
    printf("%s%d%s%s%s%d\n" ,"unit size: ", s->unit_size ,  
                            " file name: ", s->file_name ,
                            " mem_count: ", s->mem_count);
};

void toogle_Debug_Mode(state* s){//0
    if (dflag == 0)
    {
        dflag = 1;
        printf("%s\n" , "Debug flag now on");
    }
    else
    {
        dflag = 0;
        printf("%s\n" , "Debug flag now off");
    }
}

void Examine_ELF_File(state* s){//1
    char file_name[256];
    printf("%s\n" , "please enter ELF file name");
    if(fgets(file_name , BUF_SZ , stdin) != NULL){
        //file_name[strlen(file_name)-1] = 0;
    }
    file_name[strcspn(file_name , "\n")] = 0;
    //file_name[strcspn(file_name , "\n")] = 0;
    //file_name[strcspn(file_name , "\n")] = 0;
    if (dflag = 1)
    {
        printf("%s%s\n" , "Debug: file name set to: " , file_name);
    }
    if((fd  = open(file_name ,O_RDWR, 0666))  <= 0){
        perror("error - open file");
        exit(0);
    }
    if(fstat(fd, &fd_stat) != 0) {
            perror("error - stat failed");
            exit(-1);
        }  
    map_start = mmap(0 , fd_stat.st_size , PROT_READ | PROT_WRITE, MAP_SHARED , fd , 0 );
    if (map_start == MAP_FAILED)
    {
        printf("%d\n" ,fd);
        perror("mmap-faild");
        exit(-1);
    }
    header = (Elf32_Ehdr*)map_start;
    //printf( "%s\n%s\n","whatttttttt" ,header->e_machine);
    printf("Bytes 1,2,3 of the magic: %x %x %x\n",header->e_ident[0],header->e_ident[1], header->e_ident[2]);
    printf("The data encoding scheme of the object file: %d\n", header->e_ident[5]);
    printf("Entry point: 0x%X\n", header->e_entry);
    printf("The file offset in which the section header table resides: %d\n", header->e_shoff);
    printf("The number of section header entries: %d\n", header->e_shnum);
    printf("The size of each section header entry: %d\n", header->e_shentsize);
    printf("The file offset in which the program header table resides: %d\n", header->e_phoff);
    printf("The number of program header entries: %d\n", header->e_phnum);
    printf("The size of each program header entry: %d\n", header->e_phentsize);

}
void Print_Section_Names(state* s){//2
      
}
void Print_Symbols(state* s){//3
    
}

char* unit_to_format_deci(int unit) {
    static char* formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
    return formats[unit-1];
}    

void Relocation_Tables(state* s){//4

}

void quit(state* s){
    if (dflag == 1)
    {printf("%s\n" , "quitting");
    }
    exit(0);
}

int main(int argc, char **argv){
    struct fun_desc menu[] = {{"Toggle Debut Mode" , toogle_Debug_Mode} ,
                                 {"Examine_ELF_File" , Examine_ELF_File} ,
                                 {"Print Section Names" ,Print_Section_Names} ,
                                 {"Print Symbols" , Print_Symbols} ,
                                 {"Relocation Tables" , Relocation_Tables} ,
                                 {"quit" , quit},
                                 { NULL , NULL}};
    state *mystate = malloc(sizeof(state));
    mystate->unit_size = 1;
    //mystate->file_name[0] = " ";
    //initial(mystate);
    while(1){
        printf("%s\n" , "Please choose a function");
        //mystate->file_name = malloc(NAME_LEN);
        //mystate->mem_buf = malloc(BUF_SZ);
        print_menu(menu);
        int length = sizeof(menu) / sizeof(menu[0]);
        char c = fgetc(stdin);
        int num =  c - '0';
        while (num < 0  || num > 8)
        {
            num = fgetc(stdin)-'0';
        }
        fgetc(stdin);
        printf("%s%d\n" , "Option : " , num);
        if (num < 0 || num > length-1)
        {
            printf("%s" , "Not within bounds");
            exit(1);
        }
        else
        {
            printf("%s\n" , "Within bounds");
            //printf("%d\n" , num);
        }
        map(mystate , menu[num].fun);
        //printf("%d" , num);
        //char* temp = carray;
        //carray = map(carray ,5, menu[num].fun );
        //free(temp);

        printf("Done.\n");  
    }
    return 1;
}

