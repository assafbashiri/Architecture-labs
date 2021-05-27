#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 
 char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  for (int i = 0; i < array_length; i++)
  {
      mapped_array[i] = f(array[i]);
  }
  
  return mapped_array;
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


void toogle_Debug_Mode(state* s){
    if (s->debug_mode == 0)
    {
        s->debug_mode = 1;
        printf("\n" , "Debug flag now on");
    }
    else
    {
        s->debug_mode = 0;
        printf("\n" , "Debug flag now off");
    }
    
    
    //printf("\n" "toogle... to do");
}
void set_File_Name(state* s){
    char *ans[128];
    printf("\n" , "please enter file name");
    fgets(ans , 128 , stdin);
    memcpy(s->file_name , ans , sizeof(ans));
    if (s->debug_mode = 1)
    {
        printf("%s%s\n" , "Debug: filr name set to: " , s->file_name);
    }
    
    //printf("\n" "set file... to do");
}
void set_Unit_Size(state* s){
    printf("\n" , "please insert szie (option is 1 ,2 or 4)");
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
        fprintf(stderr , "\n" , "invalid number");
    
    
    //printf("\n" "set unit... to do");
}
void load_Into_Memory(state* s){
    printf("\n" "load... to do");
}
void memory_Deslplay(state* s){
    printf("\n" "memory desplay... to do");
}
void save_Into_File(state* s){
    printf("\n" "save into... to do");
}
void memory_Modify(state* s){
    printf("\n" "memory modify... to do");
}
void quit(state* s){
    if (s->debug_mode == 1)
    {printf("\n" , "quitting");
    }
    
    exit(0);
}

int main(int argc, char **argv){
    char * carray = malloc(5);
    while(1){
        printf("%s\n" , "Please choose a function");
        struct fun_desc menu[] = {{"Toggle Debut Mode" , toogle_Debug_Mode} ,
                                 {"Set File Name" , set_File_Name} ,
                                 {"Set Unit Size" , set_Unit_Size} ,
                                 {"Load Into Memory" , load_Into_Memory } ,
                                 {"Memory Display" , memory_Deslplay} ,
                                 {"Save Into File" , save_Into_File },
                                 {"Memory Modify" , memory_Modify},
                                 {"quit" , quit},
                                 { NULL , NULL}};
        
        print_menu(menu);
        int length = sizeof(menu) / sizeof(menu[0]);
        int num = fgetc(stdin);
        num =  num - '0';
        while (num == -38 || num == 20)
        {
            num = fgetc(stdin)-'0';
        }
        
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
        //printf("%d" , num);
        //char* temp = carray;
        //carray = map(carray ,5, menu[num].fun );
        //free(temp);

        printf("Done.\n");  
    }
    return 1;
}

