#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define  NAME_LEN  128
#define  BUF_SZ    10000

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
struct stat fd_stat;
void *map_start;
Elf32_Ehdr *header;
int fd ;
int dflag = 0;

char* typeOf(int type){

    switch(type){
        case SHT_NULL : return "NULL";
            break;
        case SHT_PROGBITS : return "PROGBITS";
            break;
        case SHT_SYMTAB : return "SYMTAB";
            break;
        case SHT_STRTAB : return "STRTAB";
            break;
        case SHT_RELA : return "RELA";
            break;
        case SHT_HASH : return "HASH";
            break;
        case SHT_DYNAMIC : return "DYNAMIC";
            break;
        case SHT_NOTE : return "NOTE";
            break;
        case SHT_NOBITS : return "NOBITS";
            break;
        case SHT_REL : return "REL";
            break;
        case SHT_SHLIB : return "SHLIB";
            break;
        case SHT_DYNSYM : return "DYNSYM";
            break;
        case SHT_INIT_ARRAY : return "INIT_ARRAY";
            break;
        case SHT_FINI_ARRAY : return "FINI_ARRAY";
            break;
        case SHT_PREINIT_ARRAY : return "PREINIT_ARRAY";
            break;
        case SHT_GROUP : return "GROUP";
            break;
        case SHT_SYMTAB_SHNDX : return "SYMTAB_SHNDX";
            break;
        case SHT_NUM : return "NUM";
            break;
        case SHT_LOOS : return "LOOS";
            break;
        case SHT_GNU_LIBLIST : return "LIBLIST";
            break;
        case SHT_CHECKSUM : return "CHECKSUM";
            break;
        case SHT_LOSUNW : return "LOSUNW";
            break;
        case SHT_SUNW_COMDAT : return "COMDAT";
            break;
        case SHT_SUNW_syminfo : return "SYMINFO";
            break;
        case SHT_GNU_verdef : return "VERDRF";
            break;
        case SHT_GNU_verneed : return "VERNEED";
            break;
        case SHT_GNU_versym : return "VERSYM";

            break;

        case SHT_LOPROC : return "LOPROC";

            break;

        case SHT_HIPROC : return "HIPROC";

            break;

        case SHT_LOUSER : return "LOUSER";

            break;

        case SHT_HIUSER : return "HIUSER";

            break;

        case SHT_GNU_HASH : return "GNU_HASH";

        default: return "";

    }
}

typedef struct {
  char debug_mode1;
  char file_name[NAME_LEN];
  int unit_size;
  unsigned char mem_buf[BUF_SZ];
  size_t mem_count;
  /*
   .
   .
   Any additional fields you deem necessary
  */
} state;

struct fun_desc {
  char *name;
  void (*fun)();
};
 
  void map( void (*f) ()){
  f();
}

void print_menu(struct fun_desc menu[]){


    for (int i = 0; i <= 5; i++)
    {
        printf("%d%c%s\n" , i , ')' , menu[i].name);
    }
}

void toogle_Debug_Mode(){//0
    if (dflag == 0)
    {
        dflag = 1;
        printf("%s\n" , "Debug flag now on");
    }
    else
    {
        dflag = 0;
        printf("%s\n" , "Debug flag now off");
    }
}

void Examine_ELF_File(){//1
    char file_name[256];
    printf("%s\n" , "please enter ELF file name");
    if(fgets(file_name , BUF_SZ , stdin) != NULL){
    }
    file_name[strcspn(file_name , "\n")] = 0;
    if (dflag = 1)
    {
        printf("%s%s\n" , "Debug: file name set to: " , file_name);
    }
    if((fd  = open(file_name ,O_RDWR, 0666))  <= 0){
        perror("error - open file");
        exit(0);
    }
    if(fstat(fd, &fd_stat) != 0) {
            perror("error - stat failed");
            exit(-1);
        }  
    map_start = mmap(0 , fd_stat.st_size , PROT_READ | PROT_WRITE, MAP_SHARED , fd , 0 );
    if (map_start == MAP_FAILED)
    {
        printf("%d\n" ,fd);
        perror("mmap-faild");
        exit(-1);
    }
    header = (Elf32_Ehdr*)map_start;
    printf("Bytes 1,2,3 of the magic: %x %x %x\n",header->e_ident[0],header->e_ident[1], header->e_ident[2]);
    printf("The data encoding scheme of the object file: %d\n", header->e_ident[5]);
    printf("Entry point: 0x%X\n", header->e_entry);
    printf("The file offset in which the section header table resides: %d\n", header->e_shoff);
    printf("The number of section header entries: %d\n", header->e_shnum);
    printf("The size of each section header entry: %d\n", header->e_shentsize);
    printf("The file offset in which the program header table resides: %d\n", header->e_phoff);
    printf("The number of program header entries: %d\n", header->e_phnum);
    printf("The size of each program header entry: %d\n", header->e_phentsize);

}
void Print_Section_Names(){//2
    if (fd <= 0)
    {
       perror("file not found\n");
       exit(1);
    }
    Elf32_Shdr *section_start = map_start + header->e_shoff; // first section, e_shoff = section header table offset
    Elf32_Shdr * section_name_start = section_start + header->e_shstrndx; // specific section header, section header table index of the entry associated with the section name string table
    char* section_names_start_pointer = map_start + section_name_start->sh_offset; // first byte in the section
    char * section_name;
    printf("[index]\tsection_name\tsection_address\tsection_offset\tsection_size\tsection_type\n");
    for(int i = 0; i < header->e_shnum; i++)
    {
        section_name = section_names_start_pointer + section_start[i].sh_name; // section name
        printf("[%2d] %21s %7x\t%7x\t   %7x\t  %10s\n",
            i, section_name, section_start[i].sh_addr, section_start[i].sh_offset, 
                section_start[i].sh_size, typeOf(section_start[i].sh_type));
    }
    if(dflag){
        printf("Section header string table index: %d\n",header->e_shstrndx);
    }  
}
void Print_Symbols(){//3
    if( fd == -1) {
	    perror("error - file not found\n");
        exit(0);  
	}
     int i=0;
    char* section_name;
    char *symbol_table_names_pointer;
    Elf32_Shdr *run_header = (Elf32_Shdr *)(map_start + header->e_shoff);

    Elf32_Sym* symbol_table;
    Elf32_Shdr* symbol_table_names;
    Elf32_Shdr* section_start =/*(Elf32_Shdr*)*/ map_start + header->e_shoff; // first section, e_shoff = section header table offset
    Elf32_Shdr* section_name_start = section_start + header->e_shstrndx; // string table - section header table index of the entry associated with the section name string table
    char* section_names_start_pointer = map_start + section_name_start->sh_offset; // first byte in the section string table
     while((i < header->e_shnum)) { // Section header table entry count
        if ((section_start[i].sh_type == SHT_SYMTAB) || (section_start[i].sh_type == SHT_DYNSYM)) { // is Symbol table or Dynamic linker symbol table
            symbol_table = map_start + section_start[i].sh_offset; // get the symbol table of this section
            symbol_table_names = section_start + section_start[i].sh_link; // Link to section string table, sh_link = the actual section
            symbol_table_names_pointer = map_start + symbol_table_names->sh_offset; // pointer to the actual string table
            if (dflag){
                printf("Size of symbol table is: %x\n", run_header->sh_size);
                printf("Numbers of symbols: %d\n", run_header->sh_size / sizeof(Elf32_Sym));
            }
            printf("index\tvalue\tsection_index\tsection_name\tsymbol_name\n");
            for (int j = 0; j < section_start[i].sh_size / sizeof(Elf32_Sym); j++) {
                Elf32_Sym current_symbol = symbol_table[j];
                // get section name 
                if(symbol_table[i].st_shndx == SHN_UNDEF) // section index
                    section_name = "UND";
                else if(symbol_table[i].st_shndx == SHN_ABS)
                    section_name = "ABS";
                else
                    section_name = section_names_start_pointer + section_start[symbol_table[i].st_shndx].sh_name;

                // print
                printf("%2d: %09x\t %9d\t %9s\t %9s\n",
                    j, current_symbol.st_value, current_symbol.st_shndx, section_name,
                             symbol_table_names_pointer + current_symbol.st_name);
            }
            printf("\n");
        }
        run_header++;
        i++;
    }  
}

char* unit_to_format_deci(int unit) {
    static char* formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
    return formats[unit-1];
}    

void Relocation_Tables(){//4
    if( fd == -1) {
	    perror("error - file not found\n");
        exit(0);  
	}
    Elf32_Shdr* section_start = (Elf32_Shdr *)(map_start + header->e_shoff);
    Elf32_Rel* relocation_tables;
    Elf32_Sym* dynsym_table;
    Elf32_Shdr* dynsym_names;
    Elf32_Rel current_relocation;
    for(int i = 0 ; i < header->e_shnum; i++) {

        if (section_start[i].sh_type == SHT_REL) { // is Relocation entries section
            int index = section_start[i].sh_link; // the section that this symbol belongs too
            dynsym_table = map_start + section_start[index].sh_offset; // pointer to the section table
            dynsym_names = section_start + section_start[index].sh_link;
            relocation_tables = map_start + section_start[i].sh_offset; // get the current relocation table
            char* dynsym_names_pointer = map_start + dynsym_names->sh_offset; 

            printf("offset\t\tinfo\t\ttype\t\tvalue\t\tname\n");
            for (int j=0; j<section_start[i].sh_size / sizeof(Elf32_Rel); j++){
                current_relocation = relocation_tables[j];
                printf("%08x\t%08x\t%4d\t%08x\t%8s\n",
                current_relocation.r_offset, current_relocation.r_info,
                ELF32_R_TYPE(current_relocation.r_info),
                dynsym_table[ELF32_R_SYM(current_relocation.r_info)].st_value, // get the symbol's value (relocation entry) and find it in the dynsym table 
                (char *)(dynsym_names_pointer + dynsym_table[ELF32_R_SYM(current_relocation.r_info)].st_name));
            }
            printf("\n");
        }
    }
}
void quit(){
    if (dflag == 1)
    {printf("%s\n" , "quitting");
    }
    exit(0);
}
int main(int argc, char **argv){
    struct fun_desc menu[] = {{"Toggle Debut Mode" , toogle_Debug_Mode} ,
                                 {"Examine_ELF_File" , Examine_ELF_File} ,
                                 {"Print Section Names" ,Print_Section_Names} ,
                                 {"Print Symbols" , Print_Symbols} ,
                                 {"Relocation Tables" , Relocation_Tables} ,
                                 {"quit" , quit},
                                 { NULL , NULL}};
    while(1){
        printf("%s\n" , "Please choose a function");
        print_menu(menu);
        int length = sizeof(menu) / sizeof(menu[0]);
        char c = fgetc(stdin);
        int num =  c - '0';
        while (num < 0  || num > 8)
        {
            num = fgetc(stdin)-'0';
        }
        fgetc(stdin);
        printf("%s%d\n" , "Option : " , num);
        if (num < 0 || num > length-1)
        {
            printf("%s" , "Not within bounds");
            exit(1);
        }
        else
        {
            printf("%s\n" , "Within bounds");
        }
        map( menu[num].fun);     
        printf("Done.\n");  
    }
    return 1;
}

