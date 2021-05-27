#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    unsigned char* sig;
} virus;

//FILE *filen = NULL;
char *file_name;

typedef struct link link;
 
struct link {
    link *nextVirus;
    virus *vir;
};

struct fun_desc {
  char *name;
  link* (*fun)(void* , void*);
};

void print_menu(struct fun_desc menu[]){
    for (int i = 0; i < 3; i++)
    {
        printf("%d%c%s\n" , i , ')' , menu[i].name);
    }
}

virus* readVirus(FILE* reader){
    struct virus *v = malloc(sizeof(virus));
    int counter = 0;
    counter = fread(v , sizeof(char) , 18 , reader);
    if (counter == 0)
    {
        return NULL;
    }
    
    v->sig = malloc(v->SigSize*sizeof(unsigned char));
    fread(v->sig , sizeof(char) , v->SigSize , reader); 
    
    return v;  
}

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

link* list_print(void* file , void* virus_list){
    link *vlist = (link*) virus_list;
    FILE *stream = (FILE*) file;
    FILE *output = stdout;
    link *runner = vlist;
    while(runner != NULL){
        printVirus(runner->vir , output);
        runner = runner->nextVirus;
    }
    return vlist;
}
link* list_append(link* virus_list, virus* data){
    link *add = malloc(sizeof(link));
    add->vir = data;
    add->nextVirus = NULL;
    link *curr = virus_list;
    
    if (virus_list == NULL)
    {
        return add;
    }
    
    while (curr->nextVirus != NULL)
    {
        curr = curr->nextVirus;
    }
    curr->nextVirus = add;
    
    return virus_list;
} 

void list_free(link *virus_list);
/* Free the memory allocated by the list. */

link* loadVirus(void *file , void *zibi){
    char buff[256];
    FILE *filename;
    printf("%s\n" , "enter a file name: ");
    if(fgets(buff , 255 , stdin) != NULL)
    {
        buff[strcspn(buff,"\r\n")] = 0;
        filename = fopen(buff , "r");
        if (filename == NULL)
        {
            fprintf(stderr ,"%s\n", "no file");
            exit(1);
        }
    }
    
    link *ll = (link*) zibi;
    
    virus *viru =malloc(sizeof(virus));
    viru->SigSize = 2;
    char buffer[4];
    fread(buffer , sizeof(char) , 4 , filename);
    while (viru != NULL)
    {
    viru = readVirus(filename);
    if (viru == NULL)
    {
        return ll;
    }
    ll = list_append(ll , viru);
    }
    
    return ll;
}
void* print_list(){
    
}
long getFileLength(FILE *file) {
    fseek(file, 0, SEEK_END); 
    long fileLength = ftell(file); 
    fseek(file, 0, SEEK_SET); 
    return fileLength;
}
long isVirus(char *buffer, virus *curr_virus, unsigned long size) { 
    int location = 0;
    while(location < size)
    {
        if(memcmp(curr_virus->sig, buffer+location, curr_virus->SigSize) == 0)
            return location;
        
        location = location + 1;
    }
    return -1;
}

void detect_virus(char *buffer, unsigned int size, link *virus_list, FILE* output){
    link *runner = virus_list;
    while(runner != NULL)
    {
        long location = isVirus(buffer, runner->vir, size);
        if(location != -1)
        {
            fprintf(output, "Starting byte location: %ld\n", location);
            fprintf(output, "Virus name: %s\n", runner->vir->virusName);
            fprintf(output, "Signature size: %d\n\n", runner->vir->SigSize);

        }
        if (runner->nextVirus == NULL)
        {
            runner = NULL;
            break;
        }
        
        runner = runner->nextVirus;
    }
}

link* detect_main(void *file , void* lis){
    link* startL = (link*) lis;  
    FILE *input = fopen(file_name , "r");
    //FILE *input = fopen("infected" , "r");
    long bufferLen = 10000;
    unsigned int size = 0;
    FILE *out = stdout;
    char buffer [bufferLen];
    int fileLen = getFileLength(input);
    fread(buffer , sizeof(char), fileLen , input);
    if(bufferLen < fileLen)
        size = bufferLen;
    else
        size = fileLen;
    detect_virus(buffer , size , startL , out);
    fclose(input);
    return lis;
}


int main(int argc, char **argv) {
    struct fun_desc menu[] = {
         {"Load signatures",loadVirus} ,
        {"Print signatures",list_print} ,
        {"detect virus" , detect_main},
        {NULL,NULL} };
        if (argv[1] != NULL)
        {
            file_name = argv[1];
        }
        
    FILE *reader = NULL;
    FILE *output = NULL;
    FILE *input = stdin;
    link *lis = NULL;
    int choice = 0;
    char buff[10];
    while(1){
        printf("%s\n" , "Please choose a function");
        print_menu(menu);
       if ( fgets(buff , 10 , input)!= NULL)
       {
           buff[strcspn(buff , "\n" )] = 0;
           sscanf(buff , "%d" , &choice);
       }
       else
       {
       }
       lis = menu[choice].fun(input,lis);
    }
    //fclose(killing);
    return 0;
} 