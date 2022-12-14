#include "parseloop.h"
#include "bitop.h"
#include "chordgen.h"
#include "chordprint.h"
#include "globals.h"
#include "parsing.h"
#include "init.h"
#include "rand.h"
#include "scalegen.h"
#include "syntaxcheck.h"
#include "types.h"
#include "user_info.h"
#include "parsing.h"
#include "harmo.h"
#include "writeenv.h"
#include <stdbool.h>
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

void scaleparse(char * line , S_USERINFO* user_saved){//handles the scale parsing
    
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("scale parse error\n"); return;}

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
          if(indexx==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_scale(user_saved, indexx);}
             
    } else {
        printf("runtime scaleparse error\n");
        
    }
}

void harmoparse (char * line , S_USERINFO* user_saved ){

    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("runtime harmoparse error\n"); return;}

    if (!strncmp(&line[i], "rand",4)) {


      length= parse_scale_length(line);
      if(length==13) length=rand()%12;
      
      tmp_saved_scale=generate_ran_scale(length);

      
      if(tmp_saved_mode) free(tmp_saved_mode);
	  tmp_saved_mode=generate_modes(tmp_saved_scale);

	  print_scale(tmp_saved_scale);
	  print_modes(tmp_saved_mode);

    

    }else if (!strncmp(&line[i], "scale",5)) {

      

      begin=set_to_first_bracket(line);
      if(begin!=NULL){

        if (tmp_saved_mode)free(tmp_saved_mode); 
        tmp_saved_mode=generate_modes(parse_scale(begin));
        print_modes(tmp_saved_mode);

      }else {
        printf("no scale parsed; harmonisation operation isn't possible; please pass a valid scale\n");
      }
     


     
    }else if(!strncmp(&line[i], "saved",5)){
        i+=5; 
        indexx= parse_index(&line[i]);
        if(indexx>user_saved->scales_num) { 
          printf("index passed greater than num of scale saved, please pass a valid index; current num of scales is %d\n", user_saved->scales_num);
        }else{
          tmp_saved_scale= get_saved_scale(user_saved,  indexx);
          if(tmp_saved_scale!=ERROR_FLAG) {
             if(tmp_saved_mode) free(tmp_saved_mode); 
             tmp_saved_mode= generate_modes(tmp_saved_scale); 
             print_modes(tmp_saved_mode);
          }else{ printf("something went wrong\n");}
        }
        

    }else if(!strncmp(&line[i], "save",4)){

    
      i+=4;

      while(NEUTRAL_CHAR(line[i])) i++;
      if(!strncmp (&line[i], "as",2)){
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
      }
      else if(strstr(line, "0")!=NULL){

        printf("\nscale parsed as" );
        tmp_saved_scale=parse_scale(line);
        print_scale(tmp_saved_scale);

        if (parsed_modes) free(parsed_modes);
        parsed_modes=generate_modes(tmp_saved_scale);

        save_modes(parsed_modes,user_saved);
      
      }else if (tmp_saved_mode){

        printf("\nsmodes in memory as\n" );
        print_modes(tmp_saved_mode);
        save_modes(tmp_saved_mode,user_saved);
        
      }else{
        printf("\nno scale saved in tmp and no scale parsed; nothing will be saved\n"); 
      }
    }else if(!strncmp(&line[i], "remove ",7)){
          
          indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_modes(user_saved, indexx); compt_harmo--;}
          

    }else if(!strncmp(&line[i], "print ",5)){
          
          indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; nothing will be printed, please pass an integer from 1 to the number of harmo saved\n");
          else{
            print_modes(get_modes(user_saved, indexx));
          }
          

    }else {
        printf("runtime harmoparse error 2\n");
    }
    
    
}


void chprogparse(char * line , S_USERINFO* user_saved){
    
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("runtime chprogparse error\n"); return;}
    
    if(!strncmp(&line[i], "rand",4)){

        l1=parse_index(line);
        l2=parse_next(line);
        if(tmp_chprog) {

          
            free_chord_prog(tmp_chprog);
        }

     
        if(l1==-1){
        
            tmp_chprog=generate_chord_prog(generate_ran_scale((rand()%4+7)), rand()%10+1);//generates rand chprog from scale between 7 and 12 length
        }else if(l2==-1){
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , rand()%10+1   );
        }else{
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , l2   );
        }
        
        if(!tmp_chprog) printf("couldn't generate a chord prog with given parameters; please try other ones\n");
        else print_chord_prog(tmp_chprog);
       
      }else if(!strncmp(&line[i], "save [",6)) {

         S_CHORD_PROG * ch_parsed= str_to_chord_prog(line);
         if(!ch_parsed){
            printf("couldn't parse a chord prog, please pass a correct chord prog\n");

         }else{
           save_chprog(ch_parsed, user_saved);
           free_chord_prog(ch_parsed);
         }
       
      }else if(!strncmp(&line[i], "save",4)) {

         
         if(tmp_chprog){
           save_chprog(tmp_chprog, user_saved);
          // printf("chord prog saved at index %d\n", user_saved->progs_num);

           //printf("in save chprog %p\n", tmp_chprog);
           print_chord_prog(tmp_chprog);
           free_chord_prog(tmp_chprog);
           tmp_chprog=NULL;

         }else{
           printf("no temporary scale saved\n");
         }
        
      } else if(!strncmp(&line[i], "print ",6)) {

         
         indexx=parse_index(line);
          if(indexx==-1) printf("index not recognised; no chprog will be printed, please pass an integer from 1 to the number of scales saved\n");
          else{print_saved_prog(user_saved, indexx);}
        

      }  else if(!strncmp(&line[i], "remove ",7)){
          
          indexx=parse_index(line);
         // printf("%d",index);
          if(indexx==-1  || indexx==0) printf("index not recognised; no chprog will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_chprog(user_saved, indexx);}
         

      }
}

void helpparse(char * line ){ //prints the informations corresponding to a string starting by help passed from command line
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ 
        printf("MusicTool is a simple interpreter that does music oriented operations.\nMusicTool currently supports 5 types of commands.\ncommand starting with the keyword \"scale\" do operations on scales.\ncommands starting with the keyword \"harmo\" do operations on harmonised scales.\nCommand starting with the keyword \"chprog\" do operations on chord progressions.\nCommands starting with read do file parsing.\nCommands starting with write do file writing.\nTo see the list of functions for each keyword please type \"help\" followed by one of the 5 keywords.\nIf you wish to quit MusicTool, simply type \"quit\"\n");
    }else if(!strncmp(&line[i], "scale", 5)){
      
        printf("\ntype 'scale rand x' to generate a scale of x length with x being an integer between 1 and 12\ntype 'scale rand' to generate a scale of a random length\ntype 'scale save { 0 .... }' to save the scale you passed after it if  save scale is called without argument, the last generated scale will be saved\ntype 'scale print n' to print the nth scale you saved\ntype 'scale remove n' to remove the scale saved at index n\n");

    }else if(!strncmp(&line[i], "harmo", 5)){
       
        printf("\ntype 'harmo rand x' to generate an harmonised scale of length x with x being an integer between 1 and 12\ntype 'harmo rand' to generate an harmonised scale of random length\ntype 'harmo scale { 0 ... }' to harmonise a scale passed as argument \ntype 'harmo saved scale n' to harmonise the nth scale you saved\ntype 'save { ... }' to harmonise and save a scale passed as argument. If no scale is passed the last harmonized scale is saved\ntype 'print n' to print the harmonised scale saved at index n \ntype 'save as scale J I' to save the Ith scale of the Jth mode as a scale, nothing is saved if J n I arent given\ntype 'remove n' to remove the modes saved at index n\n");        
    }else if(!strncmp(&line[i], "chprog",6 )){
       

        printf("\ntype 'chprog rand x y' to generate a chord prog of length x using a scale of length y\ntype 'chprog rand x' to generate a chord prog of length x using a scale of a random length\ntype 'chprog rand' to generate a chord prog of a random length from a scale of random length \ntype 'chprog save [ I, IIm, .... ]' to save the chprog you passed after it if  save chprog is called without argument, the last generated chprog will be saved\ntype 'chprog print n' to print the nth chprog you saved\ntype 'chprog remove n' to remove the chprog saved at index n\n");
       // printf("\ntype 'extract scale n' to extract the scale from the chprog saved at index n\n");
        //printf("\ntype 'extract scale [I......]' to extract the scale from the chprog passed as argument\n");
    }else if(!strncmp(&line[i], "read",4 )){
      
        printf("\ntype : \"read command [filename]\" to interpret commands from a file. The file must begin with \"MusicTool:command\"\ntype: \"read env [filename]\" to load an environment from a file. The file must begin with \"MusicTool:environment\"\n");
    }else if(!strncmp(&line[i], "write",4 )){
        
        printf("\ntype : \"write env [filename]\" to write the current environment to a file. If the file already exists, it must begin with \"MusicTool:env\". If it doesn't , a new file is created.\n");
   
    }else {
        printf("runtime helpparse error\n");
    }

}

void clearglobals(){
    
    if(tmp_saved_mode) free(tmp_saved_mode);
    if(parsed_modes) free(parsed_modes);
    if( modes) free(modes);
  
}

void file_environment_parseloop(char * filename, S_USERINFO * user_info){//might change behavior of env command to make it also work in command line
//syntax checking ugly af; will have to redo smtg more coherent at some point


   if(!filename){
        printf("null pointer as filename\n");
        return;
    }

    ushort k=0; 
 
    
    while(filename[k]==' ' && filename[k]!=10 && filename[k]!='\0'){ k++;}

    if(filename[k]=='\n' || filename[k]=='\0'){
      printf("please pass a filename as argument");
      return;
    }

    char* name_start= &filename[k];
    



    int i= strcspn(name_start, " \n\t#"), j=strlen(name_start);
    
    char* clean_filename;
    if(i!=j){
        clean_filename = malloc(( j) * sizeof(char));
        memcpy(clean_filename, name_start,  j);
        clean_filename[i]='\0'; 

    }else {  clean_filename= strdup(name_start);}

    char * str_syntax_check= file_to_string(clean_filename);

    SYNTAX_ERROR  syntax_flag= env_check(str_syntax_check);
    free(str_syntax_check);
    if(syntax_flag){
   
      printf("syntax error : %s\n",syntax_error_flag_to_str(syntax_flag));
      free(clean_filename);
     
      return ;
    }
    FILE *f=fopen(clean_filename, "r") ;


    if(!f){
        printf("error file \"%s\" doesn't exist; please pass a valid filename as argument.\n", filename);
        free(clean_filename);
        return;
    }
    char line[256];
    fgets(line, 256, f);
   
    if(strncmp(line, "MusicTool:environment", 18)){
        printf("error invalid start of file; please begin your file with \"MusicTool:environment\"\n");
        free(clean_filename);
        fclose(f); 
        return;
    }

    CPT line_num=1;

    while(fgets(line, 256, f)){
        ushort i=0;


      while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
        i++;
      }
      if(line[i]== '\n' || line[i]=='#') { ++line_num; continue;//empty line or comment
        
      }else if(!strncmp(&line[i], "env scale", 9)){

        //check that '(' is the next not space \t \n character

        printf("1");
        char* tmp= &line[i+9];
        ushort line_env= line_num+1;
        u_char nxt_chr= next_not_blank_comment( tmp, '(');


        if(nxt_chr==1){
         while(fgets(line, 256,f) && !(next_not_blank_comment(line, ')')==1) ){
            i=0;
            while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
               i++;
            }
            if(line[i]== '\n' || line[i]=='#' || line[i]=='\0') { 
              ++line_num; continue;//empty line or comment
            }else{
              save_scale( parse_scale(&line[i]), user_info);
            }

          }
          if(!f){
            free(clean_filename);
            fclose(f);
            return;
          }
        }else if(nxt_chr==2) {
          while(fgets(line, 256, f)){

            
            nxt_chr= next_not_blank_comment(line, '(');
         
            if(nxt_chr==1){
            

              while(fgets(line, 256,f) && (next_not_blank_comment(line, ')')!=1)){
               
                i=0;
                while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
                  i++;
                }
                if(line[i]== '\n' || line[i]=='#') { 
                  ++line_num; continue;//empty line or comment
                }else{
                  
                  save_scale( parse_scale(&line[i]), user_info);
                }

              }
              if(!f){
                free(clean_filename);
                fclose(f);
                return;
              }else{break;}
            }else if( nxt_chr==2){
              continue;
            }else{
            
               printf("runtime error at line: %d no open parentheses after scale env\n", line_num);
               free(clean_filename);
               fclose(f);
               return;
            }
            line_num++;
          }
        }else{
           printf("runtime error at line %d\n", line_num+1);
          free(clean_filename);
          fclose(f);
          return;
        }
        

      }else if(!strncmp(&line[i], "env harmo", 9)){
        //check that '(' is the next not space \t \n character
        char* tmp= &line[i+9];
        ushort line_env= line_num+1;
        u_char nxt_chr= next_not_blank_comment( tmp, '(');
        S_MODES tmp_modes= NULL;

        if(nxt_chr==1){
         while(fgets(line, 256,f) && !(next_not_blank_comment(line, ')')==1) ){
            i=0;
            while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
               i++;
            }
            if(line[i]== '\n' || line[i]=='#' || line[i]=='\0') { 
              ++line_num; continue;//empty line or comment
            }else{
              tmp_modes=generate_modes(parse_scale(&line[i]));
              save_modes( tmp_modes, user_info);
              free(tmp_modes);
              
            }

          }
          if(!f){
            free(clean_filename);
            fclose(f);
            return;
          }
        }else if(nxt_chr==2) {
          while(fgets(line, 256, f)){
            nxt_chr= next_not_blank_comment(line, '(');
           
            if(nxt_chr==1){
              while(fgets(line, 256,f) && (next_not_blank_comment(line, ')')!=1)){
               
                i=0;
                while( (line[i]==' ' || line[i]=='\t') && line[i]!=10 ){
                  i++;
                }
                if(line[i]== '\n' || line[i]=='#') { 
                  ++line_num; continue;//empty line or comment
                }else{
                  tmp_modes=generate_modes(parse_scale(&line[i]));
                  save_modes( tmp_modes, user_info);
                  free(tmp_modes);
                }

              }
              if(!f){
                free(clean_filename);
                fclose(f);
                return;
              }
            }else if( nxt_chr==2){
              continue;
            }else{
               printf("runtime error at line: %d no open parentheses after harmo env\n", line_env);
               free(clean_filename);
               fclose(f);
               return;
            }
            line_num++;
          }
        }else{
           printf("runtime error at line %d\n", line_num+1);
          free(clean_filename);
          fclose(f);
          return;
        }
      }else if(!strncmp(&line[i], "env chprog", 9)){
          //check that '(' is the next not space \t \n character
        char* tmp= &line[i+10];
        ushort line_env= line_num+1;
        u_char nxt_chr= next_not_blank_comment( tmp, '(');
        S_CHORD_PROG *tmp_chprog=NULL;

        if(nxt_chr==1){
         while(fgets(line, 256,f) && !(next_not_blank_comment(line, ')')==1) ){
            i=0;
            while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
               i++;
            }
            if(line[i]== '\n' || line[i]=='#' || line[i]=='\0') { 
              ++line_num; continue;//empty line or comment
            }else{
             
              
              tmp_chprog=str_to_chord_prog(&line[i]);
              save_chprog( tmp_chprog, user_info);
              free_chord_prog(tmp_chprog);
              
            }

          }
          if(!f){
            free(clean_filename);
            fclose(f);
            return;
          }
        }else if(nxt_chr==2) {
          while(fgets(line, 256, f)){
            nxt_chr= next_not_blank_comment(line, '(');
           
            if(nxt_chr==1){
              while(fgets(line, 256,f) && (next_not_blank_comment(line, ')')!=1)){
               
                i=0;
                while( (line[i]==' ' || line[i]=='\t') && line[i]!='\n' ){
                  i++;
                }
                if(line[i]== '\n' || line[i]=='#') { 
                  ++line_num; continue;//empty line or comment
                }else{
                  tmp_chprog=str_to_chord_prog(&line[i]);
                  //printf("%s\n", line);
                  print_chord_prog(tmp_chprog);
                  save_chprog( tmp_chprog, user_info);
                  free_chord_prog(tmp_chprog);
                }

              }
              if(!f){
                free(clean_filename);
                fclose(f);
                return;
              }
            }else if( nxt_chr==2){
              continue;
            }else{
               printf("runtime error at line: %d no open parentheses after chprog env\n", line_env);
               free(clean_filename);
               fclose(f);
               return;
            }
            line_num++;
          }
        }else{
           printf("runtime error at line %d\n", line_num+1);
          free(clean_filename);
          fclose(f);
          return;
        }
      }else {
        printf("runtime error at line %d\n", line_num+1);
        free(clean_filename);
        fclose(f);
        return;
      }
      line_num++;

    }
    free(clean_filename);
    fclose(f);
    printf("environment loaded succesfully!\n");
}

void file_command_parseloop(char * filename , S_USERINFO* user_saved){//parse MusicTool command from file; file must begin with "MusicTool:commands"
    
    

    if(!filename){
        printf("filename incorrect\n");
        return;
    }

    ushort k=0; 
    while(filename[k]==' ' && filename[k]!=10 && filename[k]!='\0'){ k++;}

    if(filename[k]=='\n' || filename[k]=='\0'){
      printf("please pass a filename as argument");
      return;
    }

    char* name_start= &filename[k];


   // printf("%s\n", &filename[k]);
    

    int i= strcspn(name_start, "\n#\t "), j=strlen(name_start);
    char* clean_filename;
    if(i!=j){
        clean_filename = malloc(( j) * sizeof(char));
        memcpy(clean_filename, name_start,  j);
        clean_filename[i]='\0'; 

    }else {  clean_filename= strdup(filename);}
    
   // printf("%s\n", clean_filename);
    FILE *f=fopen(clean_filename, "r") ;


    if(!f){
        printf("error file \"%s\" doesn't exist; please pass a valid filename as argument.\n", filename);
        free(clean_filename);
        return;
    }
    char line[256];

    
    fgets(line, 256, f);
   

   
    if(strncmp(line, "MusicTool:commands", 18)){
        printf("error invalid start of file; please begin your file with \"MusicTool:commands\"\n");
        free(clean_filename);
        fclose(f); 
        return;
    }

   
    CPT line_num=1;
    ushort l=0;
 
    SYNTAX_ERROR syntax_flag= SYNTAX_OK;

    while(fgets(line, 256, f)){

      l=0;
      syntax_flag=syntaxcheck(line);
      if(syntax_flag) {
       
        printf("syntax error %s at line %d\n", syntax_error_flag_to_str(syntax_flag),line_num+1); 
        free(clean_filename);
        fclose(f);
        
        return;

      }
        
      while( (line[l]==' ' || line[l]=='\t') && line[l]!=10 ){
        l++;
      }
      if(line[l]== 10 || line[l]=='#') { ++line_num; continue;}//empty line or comment
      else if(!strncmp(&line[l], "scale ",6)){
        
        scaleparse(&line[l+6], user_saved);
        
      }else if(!strncmp(&line[l], "harmo",5)){
        harmoparse(&line[l]+5, user_saved);
        
      }else if(!strncmp(&line[l], "chprog", 6)){
        chprogparse(&line[l+6], user_saved);
        
      }else if(!strncmp(&line[l], "help",4)){
        helpparse(&line[l+4]);
      
      }else if(!strncmp(&line[l], "read",4)){
    
        l+=4;
        while(NEUTRAL_CHAR(line[l])) l++;
       

        if(!strncmp(&line[l], "command", 7)){
          
          file_command_parseloop(&line[l+7], user_saved);

        }else if(!strncmp(&line[l], "env",3)){
         
          file_environment_parseloop(&line[l+3],user_saved);
        }
        
      }else {
        printf("runtime file reading error at line %d\n", line_num+1);
        free(clean_filename);
        fclose(f);
        return;
      }
      line_num++;
    }


    free(clean_filename);
    fclose(f);
    printf("file read correctly!\n");
    return;
}





void readparse(char * str ,S_USERINFO* user_saved){
  if(! str ) return; 

  //printf("%s\n", str);
  ushort i=0;
  while(str[i]==' ') i++; 
  if(str[i] =='\n' || str[i]=='\0') return;

  if(!strncmp( str, "command ", 8)){
    file_command_parseloop(&str[i+8], user_saved);
  }else if(!strncmp(&str[i], "env", 3)){
    if(!user_saved) return;
    file_environment_parseloop(&str[i+3], user_saved);
  }
}

void writeparse(char * str , S_USERINFO* user_info){
  ushort i=0; 
  bool ret;
  while(str[i]==' '){i++ ;}

  if(str[i]=='\n' || str[i]=='\0'){
      printf("please give the part of the environment and the name of the file you want to write in\n");
      return;
  }

  if(!strncmp(&str[i], "env", 3)){
    i+=3; 
    while(str[i]==' ') i++; 
    if(str[i]=='\n' || str[i]=='\0'){
      printf("please give the the name of the file you want to save the current environment in\n");
      return;
    }else write_env(&str[i], user_info);

  }else{
    printf("runtime writeparse error\n");
     return;
  }
}

void cmdline_parseloop( S_USERINFO* user_saved){ //the main frontend loop function ; relies heavily on the scale n chord loop interpreter function

   

    //overkill but usefull 
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[256];
    ushort i=0;
   
    SYNTAX_ERROR syntax_error= SYNTAX_OK;

    while (true){
        
          
      i=0;
      fflush(stdin);
      memset(&line[0], 0, 256*sizeof(char));

      fflush(stdout);
      if (!fgets(line, 256, stdin))	continue;
      
      
      while(NEUTRAL_CHAR(line[i])){
        i++;
      }
      syntax_error= syntaxcheck(line);
      if(syntax_error) {
      
       // printf("%d\n", syntax_error);
        printf("syntax error : %s\n",syntax_error_flag_to_str(syntax_error));
        
        printf("  >>>");
        continue;
      }
      if(END_OF_LINE_CHAR(line[i])){
        printf("  >>>");
        continue;
      }
      if(!strncmp(&line[i], "scale ",6)){
        
        scaleparse(&line[i+6], user_saved);
        printf("  >>>");
      }else if(!strncmp(&line[i], "harmo",5)){
        
        harmoparse(&line[i]+5, user_saved);
        printf("  >>>");
      }else if(!strncmp(&line[i], "chprog", 6)){
        chprogparse(&line[i+6] , user_saved);
        printf("  >>>");
      }else if(!strncmp(&line[i], "help",4)){
        helpparse(&line[i+4]);
        printf("  >>>");
      }else if(!strncmp(&line[i],"quit",4)){
        printf("\nYou have exited MusicTool\n");
        clearglobals();
        break;
      }else if(!strncmp(&line[i],"read ",5)){
        readparse(&line[i+5], user_saved);
        printf("  >>>");
      }else if(!strncmp(&line[i],"write ",6)){
        writeparse(&line[i+6], user_saved);
        printf("  >>>");
      }else if (line[0]=='\n'){
        printf("  >>>");
      }else {
        printf("parsing error\n  >>>");
      }
    }
}

