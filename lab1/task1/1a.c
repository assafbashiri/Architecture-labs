#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    //printf("0");
    int flag = 0;
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
            //printf("hey you");
            if (strncmp(argv[i],"-i",2)==0)
            {
                flag = 1;
            }
            
         }
    }
    //printf("1");
    if (debug == 1)
            fprintf(stderr, "-D\n");

    if(mode == 1 && flag == 0)
        lowerToUpper(output, debug,"", flag);
    if(mode == 1 && flag ==1)
        lowerToUpper(output, debug,argv[index], flag);
    if(mode ==2 && flag ==0){

        encode(output , argv[index],"",flag);
    }
    if(mode ==2 && flag == 1){
        //printf("%s" , argv[index]);
        //printf("%s" , argv[index+1]);
        encode(output , argv[index],argv[index+1],flag);
    }
        return 0;


}
void encode(FILE * output , char symbol[] , char file[] ,int flag){
    char str[strlen(file)];
    //int length = 0 ;
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
            fprintf(output , "%c" , before);
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
            fprintf(output , "%c" , after);
            
        }
        
        
    }
    
    
    
    
}




void lowerToUpper(FILE * output, int debug, char file[] ,int flag) 
{
    char before, after;
    int counter=0;
    char str[strlen(file)];
    FILE *fp  = stdin;
    if (flag == 1)
    {
        strncpy(str , file+2 , strlen(file)-1);
        fp = fopen("input" , "r");
    }
    while((before = fgetc(fp)) != EOF)
    {
        after = before;
        if(before >= 'A' && before <= 'Z')
            {
            after=after+32;
            counter=counter+1;
            }
        if((debug == 1) && (before != '\n')) // if debug flag is on print the ascii values of the characters before and after the change 
            fprintf(stderr, "%d \t %d \n", before, after);

        
        if (debug == 1 && after == '\n')//finish the string
        {
         
            fprintf(stderr, "The number of letters is: %d\n" , counter);
            counter = 0;//restart the counter for the next string
        }
        fprintf(output, "%c", after);
    
    }      
    
}