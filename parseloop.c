#include "parseloop.h"
#include "globals.h"
#include "parsing.h"
#include "scalegen.h"
#include "user_info.h"
#include "parsing.h"
#include "harmo.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>



//scale globals
S_SCALE tmp_saved_scale=0;
S_SCALE scale_to_save=0;
LENGTH length=0;
SIGNED_LENGTH indexx=-1; //there's an index function in string.h so I had to rename the global n could not think of a better name

//harmo globals
 S_MODES tmp_saved_mode= NULL , parsed_modes=NULL;
 char* begin=NULL;
 S_MODES modes=NULL;

//chprog globals
S_CHORD_PROG * tmp_chprog=NULL;
SIGNED_LENGTH l1=-1, l2=-1;

void scaleparse(char * line){//handles the scale parsing
    ushort i=0; 

    while(line[i]==' '){ i++;}

    if (!strncmp(&line[i], "rand",4)) {

        length=parse_scale_length(line);

        if(length==13){ //checks wether a length was retrieved from the line

            
          printf("\ngenerating scale of random length \n");
          tmp_saved_scale=generate_ran_scale(rand()%12);
        }else{
          tmp_saved_scale=generate_ran_scale(length);
        }
        print_scale(tmp_saved_scale);
       
    } else if(!strncmp(&line[i], "print ",6)){
          
          indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; no scale will be printed, please pass an integer from 1 to the number of scales saved\n");
          else{print_saved_scale(user_saved, indexx);}
          
          

    }else if (!strncmp(&line[i], "save",4)){

        if(!strstr(line, "0")){ //checks if a scale is passed
          if(tmp_saved_scale){
            printf("no scale passed; saving last random scale generated\n");
            print_scale(tmp_saved_scale);
            
            save_scale(tmp_saved_scale, user_saved);
            tmp_saved_scale=0;
          }else{
            printf("no scale parsed and no temporary saved scale in memory; nothing will be done\n");
          }
        }else{
          scale_to_save=parse_scale(line);
          printf("scale parsed as : \n");
          print_scale(scale_to_save);
          save_scale(scale_to_save, user_saved);
        }
        

    }  else if(!strncmp(&line[i], "remove",6)){
          
          indexx=parse_index(line);
         // printf("%d",index);
          if(indexx==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_scale(user_saved, indexx);}
          
          
        
    } else {
        printf("syntax error\n");
        
    }
}

void harmoparse (char * line){

}

void chprogparse(char * line){

}

void helpparse(char * line){

}


void parseloop(){ //the main frontend loop function ; relies heavily on the scale n chord loop interpreter function

    printf("\n Welcome to MusicTool, type 'help' for more informations\n");
    printf("  >>>");

    //overkill but usefull 
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[256];

    while (true){

      fflush(stdin);
      memset(&line[0], 0, 256*sizeof(char));

      fflush(stdout);
      if (!fgets(line, 256, stdin))	continue;
      
      ushort i=0;
      while(line[i]==' '){
        i++;
      }
      if(!strncmp(&line[i], "scale ",6)){
        
        scaleparse(&line[i+6]);
        printf("  >>>");
      }else if(!strncmp(&line[i], "harmo",5)){
        harmoparse(&line[i]);
        printf("  >>>");
      }else if(!strncmp(&line[i], "chprog", 6)){
        chprogparse(&line[i]);
        printf("  >>>");
      }else if(!strncmp(&line[i], "help",4)){
        helpparse(&line[i]);
        printf("  >>>");
      }else if(!strncmp(&line[i],"quit",4)){
        printf("\nYou have exited MusicTool\n");
        break;
      }else {
        printf("syntax error\n  >>>");
      }
    }
}