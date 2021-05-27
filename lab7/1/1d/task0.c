#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define  NAME_LEN  128
#define  BUF_SZ    10000

typedef struct {
  char debug_mode;
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
  //char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  f(s);
  
  //return mapped_array;
}

void print_menu(struct fun_desc menu[]){
    for (int i = 0; i <= 7; i++)
    {
        printf("%d%c%s\n" , i , ')' , menu[i].name);
    }
}
void print_debug(state *s){
    printf("%s%d%s%s%s%d\n" ,"unit size: ", s->unit_size ,  
                            " file name: ", s->file_name ,
                            " mem_count: ", s->mem_count);
};
void initial(state *s){
    s->debug_mode = 0;
    //s->mem_count = 0;
    //s->unit_size = 0;
}

void toogle_Debug_Mode(state* s){
    if (s->debug_mode == 0)
    {
        s->debug_mode = 1;
        printf("%s\n" , "Debug flag now on");
    }
    else
    {
        s->debug_mode = 0;
        printf("%s\n" , "Debug flag now off");
    }
    
    
    //printf("\n" "toogle... to do");
}

void set_File_Name(state* s){
    char ans[128];
    printf("%s\n" , "please enter file name");
    fgets(s->file_name , NAME_LEN , stdin);
    s->file_name[strcspn(s->file_name , "\n")] = 0;
    //memcpy(s->file_name , ans , sizeof(ans));
    if (s->debug_mode = 1)
    {
        printf("%s%s\n" , "Debug: file name set to: " , s->file_name);
    }
}
void set_Unit_Size(state* s){
    printf("%s\n" , "please insert szie (option is 1 ,2 or 4)");
    char c = fgetc(stdin);
    int num = c -'0';
    if (num == 4 || num == 3 || num ==1)
    {
        s->unit_size = num;
        if (s->debug_mode == 1)
        {
            printf("%s%d\n" , "Debug: size set to: " , num);
        }
    }
    else
        fprintf(stderr , "%s\n" , "invalid number");
    
    
    //printf("\n" "set unit... to do");
}
void load_Into_Memory(state* s){
    printf("%s\n" , s->file_name);
    int num = 0;
    char *ans[128];
    int location; 
    int size = 0;
    if (s->file_name[0] == "")
    {
        fprintf(stderr , "%s\n" , "file has name");
    }
    if (s->file_name[0] == NULL)
    {
        printf("%s\n" , "here");
    }
    FILE *reader  = fopen(s->file_name ,"r");
    if ( reader == NULL)
    {
        fprintf(stderr , "%s\n" , "cant open file");
        return;
    }
    printf("%s\n" , "please enter <location>  <length>");
    fgets(ans , NAME_LEN , stdin);
    printf("%d\n" , reader);
    printf("%s\n" , "good job");
    sscanf(ans , "%x%d" , &location , &size);
    printf("0x%x\n%d\n" , location , size);
    printf("%s\n" , "good job1");
    fseek(reader , location , SEEK_SET);
    printf("%s\n" , "good job2");
    fread(s->mem_buf , size , s->unit_size ,  reader);
    printf("%s%d%s\n" , "loaded " , size , " units into memory");
}
char* unit_to_format_hexa(int unit) {
    static char* formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    return formats[unit-1];
}
char* unit_to_format_deci(int unit) {
    static char* formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
    return formats[unit-1];
}    

void memory_Deslplay(state* s){
    char *ans[128];
    int address; 
    int size;
    unsigned char *addr;
    unsigned char *addr1;
    unsigned char *end;
    unsigned char *end1;

    printf("%s\n" , "please enter <address>  <length>");
    fgets(ans , NAME_LEN , stdin);
    printf("%s\n" , "good job");
    sscanf(ans , "%x%d" , &address , &size);
    if (address == 0)
        addr = (unsigned char*)s->mem_buf;
    else
        addr = (unsigned char*)address;    
    end = (unsigned char*)addr+s->unit_size*size;
    end1 = end;
    addr1 = addr;
    printf("%s\n%s\n" , "Hexadecimal" , "==========");
    while(addr < end){
        int runner = *((int*)(addr));
        printf(unit_to_format_hexa(s->unit_size), runner);
        addr = addr+s->unit_size;
    }
    printf("%s\n%s\n" , "Decimal" , "==========");
    while(addr1 < end1){
        int runner = *((int*)(addr1));
        printf(unit_to_format_deci(s->unit_size), runner);
        addr1 = addr1+s->unit_size;
    }
}
void save_Into_File(state* s){
    char *ans[128];
    int source_address; 
    int target_address;
    unsigned char *addr;
    unsigned char *end;
    int size;
    FILE *out;
    FILE *in;
    printf("%s\n" , "please enter <source-address> <target-address>  <length>");
    fgets(ans , NAME_LEN , stdin);
    sscanf(ans , "%x%x%d" , &source_address, &target_address, &size);
    if (source_address == 0)
        addr = (unsigned char*)s->mem_buf;
    else
        addr = (unsigned char*)source_address; 
    end = (unsigned char*)addr+s->unit_size*size;
    //while(addr < end){
    out = fopen(s->file_name , "r+");
    fseek(out , target_address , SEEK_SET);
    fwrite(addr , size , s->unit_size , out);
    //}
    fclose(out);
}
void memory_Modify(state* s){
    char *ans[128];
    int address; 
    unsigned char *addr;
    unsigned char *end;
    int value;
    printf("%s\n" , "please enter <location> <val> ");
    fgets(ans , NAME_LEN , stdin);
    sscanf(ans , "%x%x" , &address,  &value);
    memcpy(&s->mem_buf+address , &value , s->unit_size);
}
void quit(state* s){
    if (s->debug_mode == 1)
    {printf("%s\n" , "quitting");
    }
    exit(0);
}

int main(int argc, char **argv){
    struct fun_desc menu[] = {{"Toggle Debut Mode" , toogle_Debug_Mode} ,
                                 {"Set File Name" , set_File_Name} ,
                                 {"Set Unit Size" , set_Unit_Size} ,
                                 {"Load Into Memory" , load_Into_Memory } ,
                                 {"Memory Display" , memory_Deslplay} ,
                                 {"Save Into File" , save_Into_File },
                                 {"Memory Modify" , memory_Modify},
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

