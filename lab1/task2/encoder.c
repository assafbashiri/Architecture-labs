#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    int flag = 0;
    int oflag = 0;
    int index = 0;
    FILE * output = stdout;
    int debug = 0; // debug flag
    int mode = 1; // 1 = lower to upper case mode, 2 = encode mode
    if(argc > 1) // if there are no arguments then mode is lower to upper case by default 
    {
        for(int i=1; i<argc; i++)
        {
            
            if(strncmp(argv[i],"-D",2)==0) // debug
            {
                debug = 1;
            }
            if ((strncmp(argv[i] , "-e",2)==0)| strncmp(argv[i] , "+e",2)==0)
            {
                mode = 2;
                index = i;
            }
            if (strncmp(argv[i],"-i",2)==0)
            {
                flag = 1;
            }
            if (strncmp(argv[i],"-o",2)==0)
            {
                oflag = 1;
            }

            
         }
    }
    if (debug == 1)
            fprintf(stderr, "-D\n");
    if(mode == 1 && flag == 0 && oflag == 0){
        upperToLower(output, debug,"", "" , 0 , 0);
    }
    if(mode == 1 && flag ==1 && oflag == 0){
        printf("here?");
        upperToLower(output, debug,argv[1],"", flag , 0);
    }
    if(mode == 1 && flag ==1 && oflag == 1){
        upperToLower(output, debug,argv[1],argv[2], flag , oflag); 
    } 
    else if(mode == 1 && flag ==0 && oflag == 1){
        upperToLower(output, debug,"",argv[1], 0 , oflag);  
    }
    if(mode == 2 && flag == 0 && oflag == 0){

        encode(output , argv[index],""," ", 0 , 0);
    }
    else if(mode ==2 && flag == 1 && oflag == 0){
        encode(output , argv[index],argv[index+1],"",flag , 0);
    }
    else if (mode == 2 && flag == 1 && oflag == 1)
    {

        //check
        encode(output , argv[index] , argv[index+1] , argv[index+2] , flag , oflag);
    }
    else if (mode ==2 && flag ==0 && oflag ==1)
    {
        encode(output , argv[index] , "" , argv[index+1] , 0 , oflag);
    }
    
    
        return 0;


}
void encode(FILE * output , char symbol[] , char file[], char printTo[] ,int flag ,int oflag){
    printf("helppppppp");
    char str[strlen(file)];
    char out[strlen(printTo)];
    FILE *fp  = stdin;
    if (flag == 1)
    {
        strncpy(str , file+2 , strlen(file)-1);
            if ((fp = fopen(str,"r")) == NULL)
            {
             printf("ERROR opening th file");
             exit(1);
            }
    }
    if (oflag ==1)
    {
        strncpy(out , printTo+2 , strlen(printTo)-1);
        if ((output = fopen(out,"w")) == NULL)
            {
             printf("ERROR opening the writting file");
             exit(1);
            }
    }
    char function = symbol[0];
    char append = symbol[2];
    char before,after;
    int incre = 0;
    if (append >=48 && append <= 57)
    {
        incre = append - 48;
    }
    else if (append >=65 && append <=70)
    {
        incre = append - 55;
    }
    else{
        return;
    }
    while ((before = fgetc(fp)) != EOF)
    {
        if (before == '\n')
        {
            if(oflag != 1)
                fprintf(output , "%c" , before);
            else
            {
                fputc(before , output);
                fclose(output);
                fclose(fp);
            }
            
        }
        else
        {
            if (function == '+')
            {
                after = before+incre;
            }
            else
            {
                after = before-incre;
            }
            if(oflag != 1)
                fprintf(output , "%c" , after);
            else
            {
                fputc(after , output);
            }
            
            
        }
        
        
    }
    
    
    
    
}




void upperToLower(FILE * output, int debug, char file[],char printTo[] ,int flag , int oflag) 
{
    char before, after;
    int counter = 0;
    char str[strlen(file)];
    char out[strlen(printTo)];
    printf("\n%d\n%d\n" , flag , oflag);
    FILE *fp  = stdin;
    if (flag == 1)
    {
        strncpy(str , file+2 , strlen(file)-1);
            if ((fp = fopen(str,"r+")) == NULL)
            {
            printf("\n%s\n" , str);
             printf("ERROR opening th file");
             exit(1);
            }
    }
    if (oflag == 1)
    {
        strncpy(out , printTo+2 , strlen(printTo)-1);
        if ((output = fopen("out","w+")) == NULL)
            {
             printf("ERROR opening the writting file");
             exit(1);
            }
    }
    while((before = fgetc(fp)) != EOF)
    {
        after = before;
        if(before >= 'A' && before <= 'Z')
            {
            after=after+32;
            counter=counter+1;
            }
        if((debug == 1) && (before != '\n')){ // if debug flag is on print the ascii values of the characters before and after the change 
                fprintf(stderr, "%d \t %d \n", before, after);  

        }
        
        if (debug == 1 && after == '\n')//finish the string
        {
         
            fprintf(stderr, "\nThe number of letters is: %d\n\n" , counter);
            counter = 0;//restart the counter for the next string
        }
        if (debug != 1 && after == '\n' && oflag ==1)
        {
            //fprintf(output, "%c", after);
            fclose(output);
        }
        
        fprintf(output, "%c", after);
        
        
    
    }      
    
}