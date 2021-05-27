#include <stdio.h>
#include <stdlib.h>

void printHex( char buffer[] , int length){
    for (int i = 0; i < length; i++)
    {
        printf("%02x " , buffer[i]  & 0xff);
    }
    
}



int main(int argc, char **argv) {
    FILE* reader = fopen(argv[1] , "r+");
    int counter = 0 ;
    char buff[256];
    if (!reader)
    {
        fprintf(stderr , "file nor found");
    }
    else
    {
        counter = fread(buff , sizeof(char) , 256 , reader);
        printHex(buff , counter);
    }
    
    
    return 0;
}