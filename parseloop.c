#include "parseloop.h"
#include "bitop.h"
#include "chordgen.h"
#include "chordprint.h"
#include "dodecseries.h"
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
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <stdlib.h>
#include "genfuncs.h"


void dodecparse(char* line, S_USERINFO* user_saved){
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}
    if(line[i]==10 || line[i]=='\0'){ printf("dodec parse error\n"); return;}

    if(!strncmp(&line[i],"rand",4)){
        generic_rand(&line[i+4], 'd');
    }else if (!strncmp( &line[i], "save", 4)){
        if(!strstr(line, "0")){ //checks if a scale is passed
          if(tmp_saved_dodec){
            printf("no serie passed; saving last random serie generated\n");
            print_serie(tmp_saved_dodec); 
            save_dodec(tmp_saved_dodec, user_saved);
            tmp_saved_dodec=0;
          }else{
            printf("no serie parsed and no temporary serie in memory; nothing will be done\n");
          }
        }else{
          char * tmp = set_to_first_bracket(&line[i+4]);
          if(tmp){
            dodec_to_save=parse_serie(line);
            printf("serie parsed as : \n");
            print_serie(dodec_to_save);
            save_dodec(dodec_to_save, user_saved);
          }else printf("runtime error in dodec save {..}\n");
        }
    }else if (!strncmp (&line[i], "print", 4)){
      generic_print_uinfo(&print_saved_serie, &print_dodec_env,&line[i+4], user_saved);

    }else if(!strncmp(&line[i], "remove",6)){         
      succes=generic_remove(&remove_dodec, &line[i+6], user_saved);

    }else if(!strncmp(&line[i], "invert",6)){         
      generic_dodec_dodec(&inverse_serie, &nth_inv, &line[i+6], user_saved);

    }else if(!strncmp(&line[i], "retro",5)){         
        generic_dodec_dodec(&retrograde_serie, &nth_retrograde, &line[i+5], user_saved);

    }else if(!strncmp(&line[i], "retroinv",8)){         
        generic_dodec_dodec(&retrograde_inverse_serie, &nth_retrograde_inverse, &line[i+8], user_saved);

    }else if(!strncmp(&line[i], "prime",5)){         
        generic_dodec_dodec(&first_prime, &nth_prime, &line[i+5], user_saved);

    }else if(!strncmp(&line[i], "matrix",6)){         
        
    }else{
      printf("runtime error in dodec\n");
    }
} 

void scaleparse(char * line , S_USERINFO* user_saved){//handles the scale parsing
    
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}
    if(line[i]==10 || line[i]=='\0'){ printf("scale parse error\n"); return;}

    if (!strncmp(&line[i], "rand",4)) {
      generic_rand(&line[i+4], 's');
    } else if(!strncmp(&line[i], "print",5)){ 
          succes=generic_print_uinfo(&print_saved_scale , &print_scl_env,&line[i+5], user_saved); 

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
    }else if(!strncmp(&line[i], "remove",6)){         
         succes=generic_remove(&remove_scale, &line[i+6], user_saved);
            
    }else if (!strncmp(&line[i],"invert" , 6)){
       succes=generic_scl_scl(&get_inverse_scale , &line[i+6], user_saved);

    }  else if(!strncmp(&line[i], "comp",4)){
       succes=generic_scl_scl(&get_complementary_scale, &line[i+4], user_saved);

    } else if(!strncmp(&line[i], "prime",5)){
       succes=generic_scl_scl(&get_prime_scale, &line[i+5], user_saved);

    }else if(!strncmp(&line[i], "nearby",6)){
       succes=generic_scl_scl(&generate_nearby_scale, &line[i+6], user_saved);
    } else if(!strncmp(&line[i], "intv",4)){
        i+=4;
        while(NEUTRAL_CHAR(line[i])) i++; 
        
        
        if(!strncmp(&line[i], "struct", 6)) {
            i+=6;
            while (NEUTRAL_CHAR(line[i]))  i++;
            
            if(line[i]=='{'){
              //printf("%s\n", &line[i]);
              generated_scale=parse_scale(&line[i]);
            
              if( ! (generated_scale&ERROR_FLAG)){
                generated_intv_struct= get_interval_struct(generated_scale);
                printf("interval struct of parsed scale is:\n");
                print_intv_struct(generated_intv_struct);
              }else{
                printf("please parse a valid scale\n");
              }
            }else if(!strncmp(&line[i], "saved", 5)){
              i+=5;
              while(NEUTRAL_CHAR(line[i])){
                i++;
              }
              indexx=parse_index(&line[i]);
              if(indexx!=-1){
                generated_scale=get_saved_scale(user_saved, indexx); 
                if( !( generated_scale & ERROR_FLAG)){
                  generated_intv_struct=get_interval_struct(generated_scale);
                  printf("interval struct of saved scale is:");
                  print_intv_struct(generated_intv_struct);
                }else{
                  printf("placeholder error in intv struct saved\n");
                }
              }
            }else if(END_OF_LINE_CHAR(line[i])){
              if(tmp_saved_scale){
                generated_intv_struct=get_interval_struct(tmp_saved_scale);
                printf("interval struct of tmp saved scale is:\n"); 
                print_intv_struct(generated_intv_struct);
              }else printf("no temporary saved scale to retrieve\n");
            }else printf("runtime error in scale intv struct\n");

        }else if(!strncmp(&line[i], "vector",6)){
          i+=6;
            while (NEUTRAL_CHAR(line[i]))  i++;
            
            if(line[i]=='{'){
              //printf("%s\n", &line[i]);
              generated_scale=parse_scale(&line[i]);
            
              if( ! (generated_scale&ERROR_FLAG)){
                generated_intv_vect= generate_intv_vect(generated_scale, get_length_kerni(generated_scale));
                printf("interval vect of parsed scale is:\n");
                print_intv_vect(generated_intv_vect);
              }else{
                printf("please parse a valid scale\n");
              }
            }else if(!strncmp(&line[i], "saved", 5)){
              i+=5;
              while(NEUTRAL_CHAR(line[i])){
                i++;
              }
              indexx=parse_index(&line[i]);
              if(indexx!=-1){
                generated_scale=get_saved_scale(user_saved, indexx); 
                if( !( generated_scale & ERROR_FLAG)){
                  generated_intv_vect= generate_intv_vect(generated_scale, get_length_kerni(generated_scale));
                  printf("interval vect of saved scale is:\n");
                  print_intv_vect(generated_intv_vect);
                }else{
                  printf("placeholder error in intv vect saved\n");
                }
              }
            }else if(END_OF_LINE_CHAR(line[i])){
              if(tmp_saved_scale){
                generated_intv_vect=generate_intv_vect(tmp_saved_scale, get_length_kerni(tmp_saved_scale));
                printf("interval vect of tmp saved scale is:\n"); 
                print_intv_vect(generated_intv_vect);
              }else printf("no temporary saved scale to retrieve\n");
            }else printf("runtime error in scale intv struct\n");

        }else printf("runtime error in scale intv\n");
    }else {
        printf("runtime scaleparse error\n");
    }   
}

void harmoparse (char * line , S_USERINFO* user_saved ){

    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("runtime harmoparse error\n"); return;}

    if (!strncmp(&line[i], "rand",4)) {
      generic_rand(&line[i+4], 'h');
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
          
         generic_remove( &remove_modes , &line[i+7], user_saved);
    }else if(!strncmp(&line[i], "print",5)){
          generic_print_uinfo( &print_saved_modes, &print_modes_env, &line[i+5], user_saved);

    }else {
        printf("runtime harmoparse error 2\n");
    }
    
    
}


void chprogparse(char * line , S_USERINFO* user_saved){
    
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ printf("runtime chprogparse error\n"); return;}
    
    if(!strncmp(&line[i], "rand",4)){
        generic_rand(&line[i+4], 'c');  

    }else if(!strncmp(&line[i], "save",4)) {
         
         i+=4;
         while(NEUTRAL_CHAR(line[i])) i++;
         if(line[i]=='['){
            S_CHORD_PROG * ch_parsed= str_to_chord_prog(&line[i]);
            if(!ch_parsed){
                printf("couldn't parse a chord prog, please pass a correct chord prog\n");

            }else{
              save_chprog(ch_parsed, user_saved);
              free_chord_prog(ch_parsed);
            }
         }else if(END_OF_LINE_CHAR(line[i])){
         
            if(tmp_chprog){
              save_chprog(tmp_chprog, user_saved);
              // printf("chord prog saved at index %d\n", user_saved->progs_num);

              //printf("in save chprog %p\n", tmp_chprog);
              print_chord_prog(tmp_chprog);
              free_chord_prog(tmp_chprog);
              tmp_chprog=NULL;

            }else{
              printf("no temporary prog saved\n");
            }
            }else printf("runtime error in chprog save\n");
        
      } else if(!strncmp(&line[i], "print",5)) {
          generic_print_uinfo(&print_saved_prog, print_env, &line[i+5], user_saved);

      }  else if(!strncmp(&line[i], "remove ",7)){
          generic_remove(&remove_chprog, &line[i+7], user_saved);  

      }else if(!strncmp(&line[i], "toscale",7 )){

          i+=7;
          while (NEUTRAL_CHAR(line[i])) {
            i++;
          }
          if(line[i]=='['){
            //printf("%s\n", &line[i]);
            free_chord_prog(generated_chprog);
            generated_chprog=str_to_chord_prog(&line[i]);
            
            if(generated_chprog!=NULL){
              tmp_saved_scale=PCS_TO_SCALE(chprog_to_pcs(generated_chprog));
              printf("the scale containing the chprog parsed is:");
              print_scale(tmp_saved_scale);
            }else{
              printf("please parse a valid chprog\n");
            }
          }else if(!strncmp(&line[i], "saved", 5)){
            i+=5;
            while(NEUTRAL_CHAR(line[i])){
              i++;
            }
            indexx=parse_index(&line[i]);
            if(indexx!=-1){
              free_chord_prog(generated_chprog);
              generated_chprog=duplicate_chprog(get_chprog(user_saved, indexx)); 
              
              if(generated_chprog!=NULL){
                tmp_saved_scale=PCS_TO_SCALE(chprog_to_pcs(generated_chprog));
                printf("the scale containing the chprog at index parsed is:");
                print_scale(tmp_saved_scale);
              }else{
                printf("placeholder error in inverse saved\n");
              }
            }
          }else if(END_OF_LINE_CHAR(line[i])){
            if(tmp_chprog){
              tmp_saved_scale= PCS_TO_SCALE(chprog_to_pcs(tmp_chprog));
              printf("the scale containing the chprog in tmp_chprog is:"); 
              print_scale(tmp_saved_scale);
            }else printf("no temporary saved scale to retrieve\n");
          }else printf("runtime error in scale inverse\n");
      }
}

void helpparse(char * line ){ //prints the informations corresponding to a string starting by help passed from command line
    ushort i=0; 
    while(line[i]==' ' && line[i]!=10 && line[i]!='\0'){ i++;}

    if(line[i]==10 || line[i]=='\0'){ 
        printf("MusicTool is a simple interpreter that does music oriented operations.\nMusicTool currently supports 5 types of commands.\ncommand starting with the keyword \"scale\" do operations on scales.\ncommands starting with the keyword \"harmo\" do operations on harmonised scales.\nCommand starting with the keyword \"chprog\" do operations on chord progressions.\nCommands starting with read do file parsing.\nCommands starting with write do file writing.\nTo see the list of functions for each keyword please type \"help\" followed by one of the 5 keywords.\nIf you wish to quit MusicTool, simply type \"quit\"\n");
    }else if(!strncmp(&line[i], "scale", 5)){
      
        printf("\ntype 'scale rand x' to generate a scale of x length with x being an integer between 1 and 12\ntype 'scale rand' to generate a scale of a random length\ntype 'scale save { 0 .... }' to save the scale you passed after it if  save scale is called without argument, the last generated scale will be saved\ntype 'scale print n' to print the nth scale you saved\ntype 'scale remove n' to remove the scale saved at index n\n'scale inverse' to calculate the inverse of the scale passed and save it in the tmp saved scale. invert can also be passed w/o argument in which case it will calculate the invert of tmp saved scale or w 'saved n' to calculate the invert of the nth saved scale.\n'scale comp' to calcultate the complementary of a scale and save it in tmp, comp can be passed with a scale argument, \"saved n\" n being the number of the saved scale u want to get the inverse of or w/o argument to calculate the comp of tmp and replace it in tmp\n'scale prime' calculates the prime form of a scale and behaves similarly\n");

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
    free_chord_prog(generated_chprog);
    free_chord_prog(tmp_chprog);
  
}

void file_environment_parseloop(char * filename, S_USERINFO * user_info){//might change behavior of env command to make it also work in command line

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
    int i= strcspn(name_start, "\n#\t "), j=strlen(name_start);
    char* clean_filename;
    if(i!=j){
        clean_filename = malloc(( j) * sizeof(char));
        memcpy(clean_filename, name_start,  j);
        clean_filename[i]='\0'; 

    }else {  clean_filename= strdup(filename);}
    
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
        
      while( (line[l]==' ' || line[l]=='\t') && line[l]!=10 ) l++;

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
      }else if(!strncmp(&line[i], "dodec", 4)){
        dodecparse(&line[i+4] , user_saved);
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
        printf("runtime error\n  >>>");
      }
    }
}

RUNTIME_ERROR parse_command( char * argv[], S_USERINFO * user_info){

  char * keyword= argv[1] ; 
  char* command = argv[2];
  LENGTH len= strlen (argv[2]);

  if(! (keyword &&  command)){
      printf("invalid arguments\n");
      return 1;
  }
  SYNTAX_ERROR syntaxcheck=0;

  if(!strncmp(keyword, "-read",5 )){
        syntaxcheck=filename_check_var(command);
        if(!syntaxcheck){
          printf("in\n");
          file_command_parseloop(command, user_info);
        }
  }else if(!strncmp(keyword, "-scale",5 )){

      syntaxcheck=scalecheck(command);
      if(!syntaxcheck) scaleparse( command, user_info);
  }else if(!strncmp(keyword, "-harmo",6 )){
      syntaxcheck=harmocheck(command);
      if(!syntaxcheck) harmoparse( command, user_info);
  }else if(!strncmp(keyword, "-chprog",7 )){
      syntaxcheck=chprogcheck(command);
      if(!syntaxcheck) chprogparse( command, user_info);
  }else if(!strncmp(keyword, "-dodec",5 )){
      syntaxcheck=dodeccheck(command);
      if(!syntaxcheck) dodecparse( command, user_info);
  }else if(!strncmp(keyword, "-help",5 )){
       syntaxcheck=helpcheck(command);
       if(!syntaxcheck) helpparse( command);
  }
  clearglobals();
  return syntaxcheck;
}