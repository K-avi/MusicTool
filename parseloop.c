#include "parseloop.h"
#include "bitop.h"
#include "globals.h"
#include "parsing.h"
#include "init.h"
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
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("syntax error\n"); return;}

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

    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("syntax error\n"); return;}

    if (!strncmp(&line[i], "rand",4)) {

      printf("%d",parse_scale_length(line));

      length= parse_scale_length(line);
      if(length==13) length=rand()%12;
      
      tmp_saved_scale=generate_ran_scale(length);

      
      if(tmp_saved_mode) free(tmp_saved_mode);
	  tmp_saved_mode=generate_modes(tmp_saved_scale);

	  print_scale(tmp_saved_scale);
	  print_modes(tmp_saved_mode);

    

    }else if (!strncmp(&line[i], "scale",5)) {

      

      begin=set_to_beginning(line);
      if(begin!=NULL){

        if (tmp_saved_mode)free(tmp_saved_mode); 
        tmp_saved_mode=generate_modes(parse_scale(begin));
        print_modes(tmp_saved_mode);

      }else {
        printf("no scale parsed; harmonisation operation isn't possible; please pass a valid scale\n");
      }
     

    } else if(!strncmp(&line[i], "print ",6)){

          indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; no scale will be printed, please pass an integer from 1 to the number of scales saved\n");
          else print_saved_modes(user_saved, indexx);
          

    }else if(!strncmp(&line[i], "saved scale",9)){ //this is wrong

       //need to make sure that the scale ur trying to retrieve exists
        if(tmp_saved_mode) free(tmp_saved_mode);
        tmp_saved_mode=generate_modes(tmp_saved_scale);

        print_modes(tmp_saved_mode);

    
      

    }else if(!strncmp(&line[i], "save as scale ",13)){

        //A FINIR
        SIGNED_LENGTH l1= parse_index(line);
        SIGNED_LENGTH l2= parse_next(line);
        if( l1 == -1 || l2 == -1) printf("indexes J or/and I are invalid, please parse valid indexes");
        else{

          S_SCALE scl_tmp= get_scale_of_modes(user_saved, l1, l2-1);
          printf("scale retrieved is \n");
          print_scale(scl_tmp);
        
          if( scl_tmp== ERROR_FLAG) printf("placeholder error in save modes as scale \n");
          else{
            save_scale(scl_tmp, user_saved);
          }
        }

     
    }else if(!strncmp(&line[i], "save",4)){
      
      if(strstr(line, "0")!=NULL){

        printf("\nscale parsed as\n" );
        tmp_saved_scale=parse_scale(line);

        print_scale(tmp_saved_scale);
        printf("\nand saved at index %d\n", user_saved->modes_num);

        if (parsed_modes) free(parsed_modes);
        parsed_modes=generate_modes(tmp_saved_scale);
        printf("parsed is %p\n", parsed_modes);

        save_modes(parsed_modes,user_saved);
      
      }else if (tmp_saved_mode){

        printf("\nsmodes in memory as\n" );
        print_modes(tmp_saved_mode);
        printf("\nand saved at index %d\n", compt_harmo++);
        save_modes(tmp_saved_mode,user_saved);
        
      }else{
        printf("\nno scale saved in tmp and no scale parsed; nothing will be saved\n"); 
      }
    }else if(!strncmp(&line[i], "remove ",7)){
          
          indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_modes(user_saved, indexx); compt_harmo--;}
          

    }else {
        printf("syntax error\n");
    }
    
	
}


void chprogparse(char * line){

}

void helpparse(char * line){
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ 
        printf("MusicTool is a simple interpreter that does music oriented operations.\nMusicTool currently supports 3 types of commands.\ncommand starting with the keyword \"scale\" do operations on scales.\ncommands starting with the keyword \"harmo\" do operations on harmonised scales.\nCommand starting with the keyword \"chprog\" do operations on chord progressions.\nTo see the list of functions for each keyword please type \"help\" followed by one of the 3 keywords.\nIf you wish to quit MusicTool, simply type \"quit\"\n");
    }else if(!strncmp(&line[i], "scale", 5)){
        printf("\ntype 'scale rand x' to generate a scale of x length with x being an integer between 1 and 12\n");
        printf("\ntype 'scale rand' to generate a scale of a random length \n");
        printf("\ntype 'scale save { 0 .... }' to save the scale you passed after it if  save scale is called without argument, the last generated scale will be saved\n");
        printf("\ntype 'scale print n' to print the nth scale you saved\n");
        printf("\ntype 'scale remove n' to remove the scale saved at index n\n");

    }else if(!strncmp(&line[i], "harmo", 5)){
        printf("\ntype 'harmo rand x' to generate an harmonised scale of length x with x being an integer between 1 and 12\n");
        printf("\ntype 'harmo rand x' to generate an harmonised scale of random length\n");
        printf("\ntype 'harmo scale { 0 ... }' to harmonise a scale passed as argument \n");
        printf("\ntype 'harmo saved scale n' to harmonise the nth scale you saved\n");
        printf("\ntype 'save modes { ... }' to harmonise and save a scale passed as argument. If no scale is passed the last harmonized scale is saved\n");
        printf("\ntype 'print n' to print the harmonised scale saved at index n \n");
        printf("\ntype 'save as scale J I' to save the Ith scale of the Jth mode as a scale, nothing is saved if J n I arent given\n");
        printf("\ntype 'remove n' to remove the modes saved at index n\n");
    }

}

void clearglobals(){
    
    if(tmp_saved_mode) free(tmp_saved_mode);
    if(parsed_modes) free(parsed_modes);
    if( modes) free(modes);
    if(begin) free(begin);
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
        harmoparse(&line[i]+5);
        printf("  >>>");
      }else if(!strncmp(&line[i], "chprog", 6)){
        chprogparse(&line[i]);
        printf("  >>>");
      }else if(!strncmp(&line[i], "help",4)){
        helpparse(&line[i+4]);
        printf("  >>>");
      }else if(!strncmp(&line[i],"quit",4)){
        printf("\nYou have exited MusicTool\n");
        clearglobals();
        break;
      }else if (line[0]==10){
        printf("  >>>");
      }else {
        printf("syntax error\n  >>>");
      }
    }
}