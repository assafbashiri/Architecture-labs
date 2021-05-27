#include "util.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SYS_GETDENTS 141
#define BUF_SIZE 1024   

void justPrint(){
    char buff[1] = "_";
    while(buff[0] != "\n"){
        system_call(SYS_READ , STDIN , buff , 1);
        system_call(SYS_WRITE , STDOUT , buff , 1);

    }
}
void encode(){
    char buff[1] = "_";
    while(buff[0] != "\n"){
        system_call(SYS_READ , STDIN , buff , 1);
        if (buff[0] <=  'Z' && buff[0] >= 'A')
        {
            buff[0] = buff[0]+32;
            
        }
        
        system_call(SYS_WRITE , STDOUT , buff , 1);

    }
}
int main (int argc , char* argv[], char* envp[]){
    system_call(SYS_WRITE , STDOUT , argv[1] , 2);
char *flag = "0";
    if (argc >1)
    {
        flag = argv[1];
        encode();
    }
    else
    {
        justPrint();
    }
  



/*
    int output;
  char * str = "abcd";
  char str1[120];
  /*str = itoa(argc);*/
  /*system_call(SYS_WRITE , STDOUT , "good morning" , 12);*/
  /*str = "good morning";*/


  /*str = "good morning";
  system_call(SYS_WRITE , STDOUT , str ,strlen(str));
  str = "abcde";
  system_call(SYS_WRITE , STDOUT , "\n" ,1);

  system_call(SYS_WRITE , STDOUT , str ,strlen(str));
    system_call(SYS_WRITE , STDOUT , "\n" ,1);

  output = system_call(SYS_OPEN,"aba" , 0 , 0644);
  if (output <= 0)
  {
        system_call(SYS_WRITE , STDOUT , "bad" ,3);
        system_call(SYS_WRITE , STDOUT , "\n" ,1);

  }
  else
  {
      char *st = itoa(output);
        system_call(SYS_WRITE , STDOUT , "good" ,4);
        system_call(SYS_WRITE , STDOUT , "\n" ,1);
        system_call(SYS_WRITE , STDOUT , st ,strlen(st));
        system_call(SYS_WRITE , STDOUT , "\n" ,1);
  }
  int num = system_call(SYS_READ , output ,str1 , 12);
  if (num == 0 )
  {
        system_call(SYS_WRITE , STDOUT , "error-1" ,7);
  }
  if (num < 0 )
  {
        system_call(SYS_WRITE , STDOUT , "error-2" ,7);
  }
  char *st = itoa(num);
    system_call(SYS_WRITE , STDOUT , st ,2);
     system_call(SYS_WRITE , STDOUT , "\n" ,1);
    system_call(SYS_WRITE , STDOUT , str1 ,strlen(str1));

  

  
  system_call(SYS_WRITE,STDOUT, str,strlen(str));
  system_call(SYS_WRITE,STDOUT," arguments \n", 12);
  for (i = 0 ; i < argc ; i++)
    {
      system_call(SYS_WRITE,STDOUT,"argv[", 5);
	  str = itoa(i); 
      system_call(SYS_WRITE,STDOUT,str,strlen(str));
      system_call(SYS_WRITE,STDOUT,"] = ",4);
      system_call(SYS_WRITE,STDOUT,argv[i],strlen(argv[i]));
      system_call(SYS_WRITE,STDOUT,"\n",1);
    }
   */
  return 0;
}
