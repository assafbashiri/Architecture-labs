#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    unsigned char* sig;
} virus;


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
    for (int i = 0; i < 2; i++)
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


int main(int argc, char **argv) {
    struct fun_desc menu[] = { {"Load signatures",loadVirus} , {"Print signatures",list_print} , {NULL,NULL} };
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
        /*
        //reader = fopen("signatures-L" , "r");
        //output = fopen("output" , "w");
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
        */
    }
    /*
    fclose(output);
    fclose(reader);
    */
    return 0;
} 