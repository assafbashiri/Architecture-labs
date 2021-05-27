#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc ,  char ** argv){
    int iarray[] = {1,2,3};
    char carray[] = {'a','b','c'};
    int* iarrayPtr;
    char* carrayPtr;
    iarrayPtr = iarray;
    carrayPtr = carray;
    for (int i = 0; i < 3; i++)
    {
        printf("%d" , *iarrayPtr);
        iarrayPtr+=1;
    }
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%c" , *carrayPtr);
        carrayPtr+= 1;
    }printf("\n");
    int *p;
    printf("%p\n" , p);
    
return 0 ;
}