#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "scalegen.h"
#include "scaleloop.h"
#include "user_info.h"
#include "init.h" //maybe useless
#include "parsing.h"
#include "globals.h"
#include "harmo.h"
#include "copy.h"
#include "misc.h"


static void ScaleGenerationLoop(){

    printf("\n Welcome to Scale Generation Mode, type 'help' for more informations\n");
    printf("  >>>");
     //counts how many stuff were saved to print them; might have to make a global
    S_SCALE * tmp_saved_scale= malloc(sizeof(S_SCALE));
    init_scale(tmp_saved_scale);
    char line[256];
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))	continue;

		if (strstr(line, "Gen_Rand_Scale")!=NULL) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

			scale=generate_ran_scale(parse_scale_length(line));

      copy_scale(tmp_saved_scale, scale);

			print_scale(tmp_saved_scale);
			free(scale);

      printf("  >>>");
			continue;

    } else if (strstr(line, "save_scale")!=NULL){

      if(!strstr(line, "0")){


        printf("\nscale parsed as\n" );
        print_scale(tmp_saved_scale);
        printf("\nand saved at index %d\n", compt_scale++);

        save_scale(tmp_saved_scale,user_saved);

        printf("  >>>");
      }else {
        tmp_saved_scale=parse_scale(line);
        printf("\nscale parsed as\n" );
        print_scale(tmp_saved_scale);
        printf("\nand saved at index %d\n", compt_scale++);

        save_scale(tmp_saved_scale,user_saved);

        printf("  >>>");
      }
      continue;

		} else if(strstr(line, "print_saved_scale")!=NULL){
        print_scale( user_saved->saved_scales->scales[atoi(set_to_num(line))]);

        printf("  >>>");


    } else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit Scale Generation Mode \n");
      printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'Gen_Rand_Scale x' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
			printf("\ntype 'Gen_Rand_Scale' to generate a scale of a random length \n");
      printf("\ntype 'save_scale [SCALE]' to save the scale you passed after it if  save scale is called without argument, the last generated scale will be saved\n");
      printf("\ntype 'print_saved_scale x' to print the xth scale you saved\n");

      printf("  >>>");
			continue;
		} else if(strstr(line, "quit")!=NULL)	{

        free(tmp_saved_scale);
		    printf("\nYou have exited Scale Generation Mode\n");

        printf("  >>>");
			break;
		}else if(strstr(line, "exit")!=NULL)	{
        clear_userinfo(user_saved );
		    printf("\nYou have exited MusicTool\n");

			  exit(0);

		} else {
      printf("command not parsed correctly\n");

      printf("  >>>");
    }

		if(EXIT_INFO==true) break;

	}

};

static void ScaleHarmonizationLoop(){

    printf("\n Welcome to Scale Harmonization Mode, type 'help' for more informations\n");
    printf("  >>>");

    S_MODES * tmp_saved_mode= malloc(sizeof(S_MODES));
    init_modes(tmp_saved_mode);

    S_SCALE * tmp_saved_scale= malloc(sizeof(S_SCALE));
    init_scale(tmp_saved_scale);

    char line[256];

	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;

		if (strstr(line, "Harmo_Rand_Scale")!=NULL) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

            printf("  >>>");

			scale=generate_ran_scale(parse_scale_length(line));

			print_scale(scale);

			S_MODES*modes= malloc(sizeof(S_MODES));

			modes=generate_modes(scale);

      copy_modes(tmp_saved_mode, modes);

			print_modes(modes);

      free(modes);
			free(scale);

      printf("  >>>");

			continue;

    }else if (strstr(line, "Harmo_Scale")!=NULL) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

			scale=parse_scale(line);

			S_MODES*modes= malloc(sizeof(S_MODES));

			modes=generate_modes(scale);
      copy_modes(tmp_saved_mode, modes);

			print_modes(modes);

      free(modes);
			free(scale);

      printf("  >>>");

			continue;


		} else if(strstr(line, "print_saved_scale")!=NULL){

      if(line[19]>=48 || line[19]<= 57){
        print_scale( user_saved->saved_scales->scales[atoi(set_to_num(line))]);


      }
          printf("  >>>");

    } else if(strstr(line, "print_saved_modes")!=NULL){

          printf("%s\n", set_to_num(line));

          print_modes(user_saved->saved_modes->modes[atoi(set_to_num(line))]);

          printf("  >>>");

    }else if(strstr(line, "harmo_saved_scale")!=NULL){

          S_MODES*modes= malloc(sizeof(S_MODES));

          modes=generate_modes( user_saved->saved_scales->scales[atoi(set_to_num(line))]);

          print_modes(modes);
          free(modes);


        printf("  >>>");

    }else if(strstr(line, "save_harmonised_scale")!=NULL){

      //not done
      if(strstr(line, "0")!=NULL){


        printf("\nscale parsed as\n" );
        tmp_saved_scale=parse_scale(line);

        print_scale(tmp_saved_scale);
        printf("\nand saved at index %d\n", compt_harmo++);


        save_mode(generate_modes(tmp_saved_scale),user_saved);
        //print_modes(user_saved->saved_modes->modes[2]);

        printf("  >>>");
      }else if (tmp_saved_mode->length!=0 && tmp_saved_mode->length!=1){

        printf("\nscale in memory as\n" );
        print_modes(tmp_saved_mode);
        printf("\nand saved at index %d\n", compt_harmo++);

        save_mode(tmp_saved_mode,user_saved);
        //print_modes(user_saved->saved_modes->modes[2]);

        printf("  >>>");
      }else{
        printf("\nno scale saved in tmp and no scale parsed; nothing will be saved\n");
        printf("  >>>");
      }
      continue;

    }else if(strstr(line, "save_harmo_as_scale")!=NULL){

        //A FINIR
        char* str= set_to_num(line);
        if(str!=NULL && str+1!=NULL){

          char * str01= set_to_num(str+1);

          if(str01!=NULL){
              int a=atoi(str), b=atoi(str01);
              if( a<=user_saved->saved_modes->mode_num){
                if(b<= user_saved->saved_modes->modes[a]->length){
                  //this is dumb
                  S_SCALE * tmp1= make_scale(user_saved->saved_modes->modes[a]->scale[b], user_saved->saved_modes->modes[a]->length );
                  printf("\nscale retrieved is\n" );
                  print_scale(tmp1);
                  printf("  >>>");
                  save_scale(tmp1, user_saved);
                  free(tmp1);

                }else{ printf("\n failed to retrieve scale\n"); printf("  >>>");}
              }else{ printf("\n failed to retrieve scale\n"); printf("  >>>");}
          }else{ printf("\n failed to retrieve scale\n"); printf("  >>>");}
        }


        continue;
      } else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit Scale Harmonization Mode \n");
      printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'Harmo_Rand_Scale x' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
			printf("\ntype 'Harmo_Scale xxxxxxxx' to harmonise a scale written as a string of hexadecimal integers between 0 and B \n");
      printf("\ntype 'print_saved_scale x' to print the xth scale you saved\n");
      printf("\ntype 'harmo_saved_scale x' to harmonise the xth scale you saved\n");
      printf("\ntype 'save_harmonised_scale [scale]' to harmonise and save the scale typed in place of [scale] if a scale isn't passed, the last harmonized scale is saved\n");
      printf("\ntype 'print_saved_modes n' to print the harmonised scale saved at index n \n");
      printf("\ntype 'save_harmo_as_scale J I' to save the Ith scale of the Jth mode as a scale, nothing is saved if J n I arent given\n");

      printf("  >>>");
			continue;
		} else if(strstr(line, "quit")!=NULL)	{
		    printf("\nYou have exited Scale Harmonization Mode\n");

        printf("  >>>");
			break;
		}else if(strstr(line, "exit")!=NULL)	{
        clear_userinfo(user_saved );
		    printf("\nYou have exited MusicTool\n");

			  exit(0);

		} else {
      printf("command not parsed correctly\n");

      printf("  >>>");
    }

		if(EXIT_INFO==true) break;

	}
};



void ScaleLoop(){
    //loop used when entering the scale generating/ editing mode

    printf("\n Welcome to Scale Mode, type 'help' for more informations\n");

    char line[256];

    printf("  >>>");
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (strstr(line, "Gen_Scale")!=NULL) {

			ScaleGenerationLoop();

			continue;
		} else if (strstr(line, "Harmo_Scale")!=NULL)	{

            ScaleHarmonizationLoop();
			continue;
		} else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit Scale Mode \n");
      printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'Gen_Scale' to enter Scale Generation Mode\n");
			printf("\ntype 'Harmo_Scale' to enter Scale Harmonisation mode \n");

      printf("  >>>");
			continue;
		} else if(strstr(line, "quit")!=NULL)	{
		    printf("\nYou have exited Scale_Mode\n");

        printf("  >>>");
			break;
		} else if(strstr(line, "exit")!=NULL)	{
        clear_userinfo(user_saved );
		    printf("\nYou have exited MusicTool\n");

			  exit(0);

		} else {
      printf("command not parsed correctly\n");

      printf("  >>>");
    }

		if(EXIT_INFO==true) break;

	}

}
