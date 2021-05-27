#include <stdio.h>
#include <stdlib.h>


typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    unsigned char* sig;
} virus;

virus* readVirus(FILE* reader){
    struct virus *v = malloc(555);
    fread(v , sizeof(char) , 18 , reader);
    char buffer[v->SigSize];
    fread(buffer , sizeof(char) , v->SigSize , reader); 
    v->sig = buffer;
    return v;
    
}


//this function receives a file pointer and returns a virus* that 
//represents the next virus in the file. To read from a file

void printVirus(virus* virus, FILE* output){
    fprintf(output , "%s%s\n" ,"Virus name: ",virus->virusName);
    fprintf(output , "%s%d\n" , "Virus size: ",virus->SigSize);
    fprintf(output , "%s\n" ,"signature:");
    for (int i = 0; i < virus->SigSize; i++)
    {
        fprintf(output,"%02x " ,*(virus->sig+i) & 0xff);
    }
    fprintf(output , "\n");
    

}
// this function receives a pointer to a virus and a pointer to an output file. The function
// prints the virus to the given output file. It prints the virus name (in ASCII), the virus 
//signature length (in decimal), and the virus signature (in hexadecimal representation)


void printHex( char buffer[] , int length){
    for (int i = 0; i < length; i++)
    {
        printf("%02x " , buffer[i]  & 0xff);
    }
    
}



int main(int argc, char **argv) {
    FILE* reader = fopen("signatures-L" , "r");
    FILE* output = fopen("output" , "w");
    char buff[4];
    fread(buff , sizeof(char) , 4 , reader);
    int counter = 0;
    while (1)
    {
    virus* vir = readVirus(reader);
    if (vir->SigSize == 0)
    {
        exit(1);
    }
    
    printVirus(vir , output);
    free(vir);
    }
    fclose(output);
    fclose(reader);
    return 0;
}  