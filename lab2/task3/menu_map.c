#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fun_desc {
  char *name;
  char (*fun)(char);
};
 
char censor(char c) {
  if(c == '!')
    return '.';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  for (int i = 0; i < array_length; i++)
  {
      mapped_array[i] = f(array[i]);
  }
  
  return mapped_array;
}

char encrypt(char c){
    if (c < 0x20 | c > 0x7e)
    {
        
    }
    else
    {
        c = c+3;
    }
    
return c;
}

char decrypt(char c){
    if (c < 0x20 | c > 0x7e)
    {
        
    }
    else
    {
        c = c-3;
    }
    
return c;
}

char cprt(char c){
    //printf("out\n");
    if (c < 0x20 | c > 0x7e)
    {
        //printf("in\n");
        printf("%c\n" ,'.');
    }
    else
    {
        printf("%c\n" , c);
    }
    return c;
    
}
char my_get(char c){
    return fgetc(stdin);
}

void print_menu(struct fun_desc menu[]){
    for (int i = 0; i < 5; i++)
    {
        printf("%d%c%s\n" , i , ')' , menu[i].name);
    }
}

 
int main(int argc, char **argv){
    char * carray = malloc(5);
    char * arr = "Hey!";
    while(1){
        printf("%s\n" , "Please choose a function");
        struct fun_desc menu[] = {{"Censor" , censor} , {"Encrypt" , encrypt} , {"Decrypt" , decrypt} , {"Print string" , cprt } , {"Get string" , my_get} , { NULL , NULL}};
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
        char* temp = carray;
        carray = map(carray ,5, menu[num].fun );
        free(temp);

        printf("Done.\n");  
    }
    

    
}
