
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "progbook.h"
#include "scalegen.h"
#include "types.h"
#include "init.h"
#include "parseloop.h"
#include "harmo.h"
#include "parsing.h"
#include "user_info.h"
#include "globals.h"
#include "triadgen.h"
#include "globals.h"


int main(int argc , char * argv[]){

  if(! (argc==1 || argc==2)){
    printf("%s currently takes only 1 command line argument.\n", argv[0]);
    return 1;
  }else if(argc==2){
    char * command=argv[1];
    if(!strncmp(command, "-syntaxcheck=", 13)){
      if(!strncmp(command+13, "NO", 2)){
        command+=15; 
        while (NEUTRAL_CHAR(*command)) command++;
        if(!END_OF_LINE_CHAR(*command)) {
          printf("invalid arg; please pass -syntaxcheck=YES or -syntaxcheck=NO as arg\n");
          return 2;
        }else{
          _syntaxcheck=0;
          printf("warning: you are currently running MusicTool without syntaxcheck.\nStability and behavior is not guaranteed.\nDo not run MusicTool without syntaxcheck unless you have a very good reason to.\n  >>>");
        }
        
      }else if(!strncmp(command+13, "YES", 3)){
        command+=16; 
        while (NEUTRAL_CHAR(*command)) command++;
        if(!END_OF_LINE_CHAR(*command)) {
          printf("invalid arg; please pass -syntaxcheck=YES or -syntaxcheck=NO as arg\n");
          return 3;
        }else {

          _syntaxcheck=1;
        }
      }else{
         printf("invalid arg; please pass -syntaxcheck=YES or -syntaxcheck=NO as arg\n");
        return 4;
      }
    }else{ 
       printf("invalid arg; please pass -syntaxcheck=YES or -syntaxcheck=NO as arg\n");
       return 4;
    }
  }

  
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  
   
  /* Intializes random number generator */
  time_t t;
  srand((unsigned) time(&t));

  //initialises the user saved info structure
  user_data=malloc(sizeof(S_USERINFO));
  init_userinfo(user_data);

  progbook=malloc(sizeof(PROGBOOK));
  init_book(progbook, 30);

  file_environment_parseloop( "defaultenv.txt", user_data, progbook);


  printf("Welcome to MusicTool! Type 'help' for more informations\n");
  printf("  >>>");

  cmdline_parseloop(user_data, progbook);

  free_userinfo(user_data);
  free_book(progbook);
  return 0;
}