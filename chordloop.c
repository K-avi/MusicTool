#include "chordloop.h"
#include "chordprint.h"
#include "globals.h"
#include "types.h"
#include "user_info.h"
#include "parsing.h"
#include "chordgen.h"
#include "rand.h"
#include "scalegen.h"
#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void chordloop(){

    
    printf("\n Welcome to Chord Mode, type 'help' for more informations\n");
    printf("  >>>");

    //overkill but usefull 
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[256];

    S_CHORD_PROG * tmp_chprog=NULL;
    SIGNED_LENGTH index=-1 , l1=-1, l2=-1;

    while (true){

      fflush(stdin);
      memset(&line[0], 0, 256*sizeof(char));

      fflush(stdout);
      if (!fgets(line, 256, stdin))	continue;

      if(strstr(line, "fullrand")){

        l1=parse_index(line);
        l2=parse_next(line);
        if(tmp_chprog) {

          printf("in fullrand %p\n", tmp_chprog);
            free_chord_prog(tmp_chprog);
        }

       // printf("%d, %d\n", l1, l2);
        if(l1==-1){
        
            tmp_chprog=generate_chord_prog(generate_ran_scale((rand()%4+7)), rand()%10+1);//generates rand chprog from scale between 7 and 12 length
        }else if(l2==-1){
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , rand()%10+1   );
        }else{
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , l2   );
        }
        
        if(!tmp_chprog) printf("couldn't generate a chord prog with given parameters; please try other ones\n");
        else print_chord_prog(tmp_chprog);
        printf("  >>>");
        continue;

      }else if(strstr(line, "save chprog [")) {

         S_CHORD_PROG * ch_parsed= str_to_chord_prog(line);
         if(!ch_parsed){
            printf("couldn't parse a chord prog, please pass a correct chord prog\n");

         }else{
           save_chprog(ch_parsed, user_saved);
           printf("chord prog saved at index %d\n", user_saved->progs_num);

           printf("in save chprog [ %p\n", ch_parsed);
           free_chord_prog(ch_parsed);
         }
         printf("  >>>");
         continue;
      }else if(strstr(line, "save chprog")) {

         
         if(tmp_chprog){
           save_chprog(tmp_chprog, user_saved);
           printf("chord prog saved at index %d\n", user_saved->progs_num);

           printf("in save chprog %p\n", tmp_chprog);
           print_chord_prog(tmp_chprog);
           free_chord_prog(tmp_chprog);
           tmp_chprog=NULL;

         }else{
           printf("no temporary scale saved\n");
         }
         printf("  >>>");
         continue;
      } else if(strstr(line, "print chprog ")) {

         
         index=parse_index(line);
          if(index==-1) printf("index not recognised; no chprog will be printed, please pass an integer from 1 to the number of scales saved\n");
          else{print_saved_prog(user_saved, index);}
          
          printf("  >>>");
          continue;

      }  else if(strstr(line, "remove chprog")!=NULL){
          
          index=parse_index(line);
         // printf("%d",index);
          if(index==-1) printf("index not recognised; no chprog will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_chprog(user_saved, index);}
          
          printf("  >>>");
          continue;

      }else if (strstr(line, "help")!=NULL)	{

        printf("\ntype 'quit' to exit Chord Mode \n");
        printf("\ntype 'exit' to exit MusicTool \n");
        //printf("\ntype 'coherand x y' to generate a chord prog of length x using a scale of length y using a book of prebuilt chordprogs\n");
        //printf("\ntype 'coherand x' to generate a chord prog of length x using a scale of rand length using a book of prebuilt chordprogs\n");
        printf("\ntype 'fullrand x y' to generate a chord prog of length x using a scale of length y\n");
        printf("\ntype 'fullrand x' to generate a chord prog of length x using a scale of a random length\n");
        printf("\ntype 'fullrand' to generate a chord prog of a random length from a scale of random length \n");
        printf("\ntype 'save [ I, IIm, .... ]' to save the chprog you passed after it if  save chprog is called without argument, the last generated scale will be saved\n");
        printf("\ntype 'print saved chprog n' to print the nth chprog you saved\n");
        printf("\ntype 'remove chprog n' to remove the chprog saved at index n\n");
       // printf("\ntype 'extract scale n' to extract the scale from the chprog saved at index n\n");
        //printf("\ntype 'extract scale [I......]' to extract the scale from the chprog passed as argument\n");

        printf("  >>>");
        continue;
      } else if(strstr(line, "quit")!=NULL)	{

          if(tmp_chprog){

            printf("in quit %p\n", tmp_chprog);
            free_chord_prog(tmp_chprog);
          }

          printf("\nYou have exited Chord Mode\n");
          printf("  >>>");
        break;
      }else if(strstr(line, "exit")!=NULL)	{
          
          if(tmp_chprog){

            printf("in exit %p\n", tmp_chprog);
            free_chord_prog(tmp_chprog);
          }

          printf("\nYou have exited MusicTool\n");
          free_userinfo(user_saved);

          exit(0);

      } else {
        printf("syntax error\n");
        printf("  >>>");
      }
    }
}
