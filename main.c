#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "scalegen.h"
#include "types.h"
#include "init.h"
#include "scaleloop.h"
#include "harmo.h"
#include "parsing.h"


int main()
{

    QUIT_INFO=false;
    time_t t;

    /*char * str="Harmo_Scale 024579b";

    S_SCALE* maj_scale;
    maj_scale=malloc(sizeof(S_SCALE));
    maj_scale=parse_scale(str);

    print_scale(maj_scale);


    S_MODES * modes;
    modes=malloc(sizeof(S_MODES));

    modes=generate_modes(maj_scale);

    print_modes(modes);*/


    /* Intializes random number generator */
    srand((unsigned) time(&t));


    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    printf("Welcome to ScaleGen! Type 'help' for more informations...\n");



	char line[256];
	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "Scale_Mode",8)) {
            ScaleLoop();
			continue;
		} else if (!strncmp(line, "Chord_Mode",10))	{

            printf("\nchord mode isn't implemented yet\n");
			continue;
		} else if (!strncmp(line, "help",4))	{

			printf("\ntype 'quit' to exit Scale_Gen \n");
			printf("\ntype 'Scale_Mode' to enter Scale Mode\n");
			printf("\ntype 'Chord_Mode' to enter Chord Mode\n");
			continue;
		} else if(!strncmp(line, "quit",4))	{
		    printf("\nYou have exited Scale Generator\n");
			break;
		}

		if(QUIT_INFO==true) break;

	}

	return 0;

}
