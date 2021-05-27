#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc ,  char ** argv){
    int iarray[] = {1,2,3};
    printf("%p\n" , iarray);//1
    printf("%p\n" , *iarray);//2
    printf("%p\n" , &iarray);//3
    char carray[] = {'a','b','c'};
    printf("%p\n" , carray);//4
    printf("%p\n" , *carray);//5
    printf("%p\n" , &carray);//6
    int* iarrayPtr;
    printf("%p\n" , &iarrayPtr);
    printf("%p\n" , iarrayPtr);
    //printf("%p\n" , *iarrayPtr);
    iarrayPtr = &iarray;
    printf("%p\n" , &iarrayPtr);
    printf("%p\n" , iarrayPtr);
    printf("%d\n" , *iarrayPtr);
    char* carrayPtr;
    printf("%p\n" , carrayPtr);
    printf("%c\n" , *carrayPtr);
    printf("%p\n" , &carrayPtr);
    //iarrayPtr = &iarray;
    //carrayPtr = &carray;
    
return 0 ;
}