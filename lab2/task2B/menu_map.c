#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
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
 
int main(int argc, char **argv){
    char arr1[] = {'H','E','Y','!'};
    int base_len = 5;
char* arr2 = map(arr1, base_len, my_get);
char* arr3 = map(arr2, base_len, encrypt);
char* arr4 = map(arr3, base_len, cprt);
char* arr5 = map(arr3, base_len, decrypt);
char* arr6 = map(arr5, base_len, cprt);
free(arr2);
free(arr3);
free(arr4);
free(arr5);
free(arr6);
}
