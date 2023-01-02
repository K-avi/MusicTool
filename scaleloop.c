#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitop.h"
#include "types.h"
#include "scalegen.h"
#include "scaleloop.h"
#include "user_info.h"
#include "parsing.h"
#include "harmo.h"
#include "globals.h"
#include "init.h" //maybe useless


static void ScaleGenerationLoop(){

    printf("\n Welcome to Scale Generation Mode, type 'help' for more informations\n");
    printf("  >>>");
      
      //globals
    S_SCALE tmp_saved_scale=0;
    S_SCALE scale_to_save=0;
    LENGTH length=0;
    SIGNED_LENGTH index=-1;
      //overkill but usefull 
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[256];
    
     while (true) {

      fflush(stdin);
      memset(&line[0], 0, 256*sizeof(char));

      fflush(stdout);
      if (!fgets(line, 256, stdin))	continue;

      if (strstr(line, "rand")!=NULL) {

        length=parse_scale_length(line);

        if(length==13){ //checks wether a length was retrieved from the line
          printf("\ngenerating scale of random length \n");
          tmp_saved_scale=generate_ran_scale(rand()%12);
        }else{
          tmp_saved_scale=generate_ran_scale(length);
        }
        print_scale(tmp_saved_scale);

        printf("  >>>");
        continue;

      } else if(strstr(line, "print saved scale")!=NULL){
          
          index=parse_index(line);
          if(index==-1) printf("index not recognised; no scale will be printed, please pass an integer from 1 to the number of scales saved\n");
          else{print_saved_scale(user_saved, index);}
          
          printf("  >>>");
          continue;

      }else if (strstr(line, "save")!=NULL){

        if(!strstr(line, "0")){ //checks if a scale is passed
          if(tmp_saved_scale){
            printf("no scale passed; saving last random scale generated\n");
            print_scale(tmp_saved_scale);
            
            save_scale(tmp_saved_scale, user_saved);
          }else{
            printf("no scale parsed and no temporary saved scale in memory; nothing will be done\n");
          }
        }else{
          scale_to_save=parse_scale(line);
          printf("scale parsed as : \n");
          print_scale(scale_to_save);
          save_scale(scale_to_save, user_saved);
        }

        printf("  >>>");
        continue;

      }  else if(strstr(line, "remove scale")!=NULL){
          
          index=parse_index(line);
         // printf("%d",index);
          if(index==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_scale(user_saved, index);}
          
          printf("  >>>");
          continue;

      } else if (strstr(line, "help")!=NULL)	{

        printf("\ntype 'quit' to exit Scale Generation Mode \n");
        printf("\ntype 'exit' to exit MusicTool \n");
        printf("\ntype 'rand x' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
        printf("\ntype 'rand' to generate a scale of a random length \n");
        printf("\ntype 'save { 0 .... }' to save the scale you passed after it if  save scale is called without argument, the last generated scale will be saved\n");
        printf("\ntype 'print saved scale n' to print the nth scale you saved\n");
        printf("\ntype 'remove scale n' to remove the scale saved at index n\n");

        printf("  >>>");
        continue;
      } else if(strstr(line, "quit")!=NULL)	{

          printf("\nYou have exited Scale Generation Mode\n");
          printf("  >>>");
        break;
      }else if(strstr(line, "exit")!=NULL)	{

          printf("\nYou have exited MusicTool\n");
          exit(0);

      } else {
        printf("syntax error\n");
        printf("  >>>");
      }
    }
}


static void ScaleHarmonizationLoop(){

    printf("\n Welcome to Scale Harmonization Mode, type 'help' for more informations\n");
    printf("  >>>");

    //initialises variables used in the loop for harmonization purposes.
    S_MODES tmp_saved_mode= NULL , parsed_modes=NULL;
    S_SCALE  tmp_saved_scale= 0;
    LENGTH length=0;
    SIGNED_LENGTH index=-1;
    char* begin=NULL;
    S_MODES modes=NULL;

  //initialises variables used in the loop for scale generation purposes

    char line[256];

	while (true) {

		memset(&line[0], 0, sizeof(line));
		fflush(stdout);
		if (!fgets(line, 256, stdin)) continue;

		if (strstr(line, "harmo rand")!=NULL) {

      printf("%d",parse_scale_length(line));

      length= parse_scale_length(line);
      if(length==13) length=rand()%12;
      
      tmp_saved_scale=generate_ran_scale(length);

      
      if(tmp_saved_mode) free(tmp_saved_mode);
			tmp_saved_mode=generate_modes(tmp_saved_scale);

			print_scale(tmp_saved_scale);
			print_modes(tmp_saved_mode);

      printf("  >>>");

			continue;

    }else if (strstr(line, "harmo scale")!=NULL) {

      

      begin=set_to_beginning(line);
      if(begin!=NULL){

        if (tmp_saved_mode)free(tmp_saved_mode); 
        tmp_saved_mode=generate_modes(parse_scale(begin));
        print_modes(tmp_saved_mode);

      }else {
        printf("no scale parsed; harmonisation operation isn't possible; please pass a valid scale\n");
      }
      printf("  >>>");
			continue;

		} else if(strstr(line, "print scale")!=NULL){
          
          index=parse_index(line);
          if(index==-1) printf("index not recognised; no scale will be printed, please pass an integer from 1 to the number of scales saved\n");
          else{print_saved_scale(user_saved, index);}
          
          printf("  >>>");
          continue;


    } else if(strstr(line, "print modes")!=NULL){

          index=parse_index(line);
          if(index==-1) printf("index not recognised; no scale will be printed, please pass an integer from 1 to the number of scales saved\n");
          else print_saved_modes(user_saved, index);
          
          printf("  >>>");
          continue;

    }else if(strstr(line, "harmo saved scale")!=NULL){

       //need to make sure that the scale ur trying to retrieve exists
        if(tmp_saved_mode) free(tmp_saved_mode);
        tmp_saved_mode=generate_modes(tmp_saved_scale);

        print_modes(tmp_saved_mode);

        printf("  >>>");
        continue;

    }else if(strstr(line, "save modes")!=NULL){
      
      if(strstr(line, "0")!=NULL){

        printf("\nscale parsed as\n" );
        tmp_saved_scale=parse_scale(line);

        print_scale(tmp_saved_scale);
        printf("\nand saved at index %d\n", compt_harmo++);

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
      printf("  >>>");
      continue;

    }else if(strstr(line, "save mode as scale")!=NULL){

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

        printf("  >>>");
        continue;
     
    }else if(strstr(line, "remove scale")!=NULL){
          
          index=parse_index(line);
          if(index==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_scale(user_saved, index); }
          
          printf("  >>>");
          continue;

    }else if(strstr(line, "remove modes")!=NULL){
          
          index=parse_index(line);
          if(index==-1) printf("index not recognised; no scale will be removed, please pass an integer from 1 to the number of scales saved\n");
          else{remove_modes(user_saved, index); compt_harmo--;}
          
          printf("  >>>");
          continue;

     }   else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit Scale Harmonization Mode \n");
      printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'harmo rand' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
			printf("\ntype 'harmo scale { 0 ... }' to harmonise a scale written as a string of hexadecimal integers between 0 and B \n");
      printf("\ntype 'print scale n' to print the xth scale you saved\n");
      printf("\ntype 'harmo scale n' to harmonise the nth scale you saved\n");
      printf("\ntype 'save modes { ... }' to harmonise and save the scale typed in place of [scale] if a scale isn't passed, the last harmonized scale is saved\n");
      printf("\ntype 'print modes n' to print the harmonised scale saved at index n \n");
      printf("\ntype 'save mode as scale ( J , I )' to save the Ith scale of the Jth mode as a scale, nothing is saved if J n I arent given\n");
      printf("\ntype 'remove scale n' to remove the scale saved at index n\n");
      printf("\ntype 'remove modes n' to remove the modes saved at index n\n");

      printf("  >>>");
			continue;
		} else if(strstr(line, "quit")!=NULL)	{

        if (tmp_saved_mode) free(tmp_saved_mode);
        if(parsed_modes) free(parsed_modes);
		    printf("\nYou have exited Scale Harmonization Mode\n");
        printf("  >>>");
			  break;

		}else if(strstr(line, "exit")!=NULL)	{
        //clear_userinfo(user_saved );

        if (tmp_saved_mode) free(tmp_saved_mode);
        if(parsed_modes) free(parsed_modes);
		    printf("\nYou have exited MusicTool\n");
			  exit(0);

		} else {
      printf("syntax error\n");
      printf("  >>>");
    }
	}
}



void ScaleLoop(){
    //loop used when entering the scale generating/ editing mode

    printf("\n Welcome to Scale Mode, type 'help' for more informations\n");
    char line[256];

    printf("  >>>");

	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin)) continue;
		if (line[0] == '\n') continue;
		if (strstr(line, "gen scale")!=NULL) {
      ScaleGenerationLoop();
			continue;
		} else if (strstr(line, "harmo scale")!=NULL)	{
      ScaleHarmonizationLoop();
			continue;
		} else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit Scale Mode \n");
      printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'gen scale' to enter Scale Generation Mode\n");
			printf("\ntype 'harmo scale' to enter Scale Harmonisation mode \n");

      printf("  >>>");
			continue;
		} else if(strstr(line, "quit")!=NULL)	{

		    printf("\nYou have exited Scale_Mode\n");
        printf("  >>>");
			  break;
		} else if(strstr(line, "exit")!=NULL)	{
    
		    printf("\nYou have exited MusicTool\n");
			  exit(0);

		} else {
      printf("command not parsed correctly\n");
      printf("  >>>");
    }
	}
}
