#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "scalegen.h"
#include "scaleloop.h"
#include "init.h" //maybe useless
#include "parsing.h"

#include "harmo.h"


static void ScaleGenerationLoop(){

    printf("\n Welcome to Scale Generation Mode, type 'help' for more informations\n");


    char line[256];
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "Gen_Rand_Scale",14)) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

			scale=generate_ran_scale(parse_scale_length(line));

			print_scale(scale);
			free(scale);

			continue;

		} else if (!strncmp(line, "help",4))	{

			printf("\ntype 'quit' to exit Scale_Gen \n");
			printf("\ntype 'Gen_Rand_Scale x' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
			printf("\ntype 'Gen_Rand_Scale' to generate a scale of a random length \n");
			continue;
		} else if(!strncmp(line, "quit",4))	{
		    printf("\nYou have exited Scale Generation Mode\n");
			break;
		}

		if(QUIT_INFO==true) break;

	}

};

static void ScaleHarmonizationLoop(){


    printf("\n Welcome to Scale Harmonization Mode, type 'help' for more informations\n");


    char line[256];
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "Harmo_Rand_Scale",16)) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

			scale=generate_ran_scale(parse_scale_length(line));

			print_scale(scale);

			S_MODES*modes= malloc(sizeof(S_MODES));

			modes=generate_modes(scale);

			print_modes(modes);

            free(modes);
			free(scale);

			continue;

        }else if (!strncmp(line, "Harmo_Scale",11)) {

            S_SCALE *scale;
            scale= malloc(sizeof(S_SCALE));

			scale=parse_scale(line);

			S_MODES*modes= malloc(sizeof(S_MODES));

			modes=generate_modes(scale);

			print_modes(modes);

            free(modes);
			free(scale);

			continue;

		} else if (!strncmp(line, "help",4))	{

			printf("\ntype 'quit' to exit Scale_Gen \n");
			printf("\ntype 'Harmo_Rand_Scale x' to generate a scale of x length with x being an integer between 1 and 12 written in hexadecimal\n");
			printf("\ntype 'Harmo_Scale xxxxxxxx' to harmonise a scale written as a string of hexadecimal integers between 0 and B \n");
			continue;
		} else if(!strncmp(line, "quit",4))	{
		    printf("\nYou have exited Scale Generation Mode\n");
			break;
		}

		if(QUIT_INFO==true) break;

	}
};



void ScaleLoop(){
    //loop used when entering the scale generating/ editing mode

    printf("\n Welcome to Scale Mode, type 'help' for more informations\n");

    char line[256];
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "Gen_Scale",9)) {

			ScaleGenerationLoop();

			continue;
		} else if (!strncmp(line, "Harmo_Scale",11))	{

            ScaleHarmonizationLoop();
			continue;
		} else if (!strncmp(line, "help",4))	{

			printf("\ntype 'quit' to exit Scale Mode \n");
			printf("\ntype 'Gen_Scale' to enter Scale Generation Mode\n");
			printf("\ntype 'Harmo_Scale' to enter Scale Harmonisation mode \n");
			continue;
		} else if(!strncmp(line, "quit",4))	{
		    printf("\nYou have exited Scale_Mode\n");
			break;
		}

		if(QUIT_INFO==true) break;

	}

}
