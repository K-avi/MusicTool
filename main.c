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
#include "user_info.h"
#include "globals.h"
#include "copy.h"
#include "misc.h"
#include "chordgen.h"

int main()
{

    EXIT_INFO=false;
    time_t t;

    
    S_SCALE * maj_scale= malloc(sizeof(S_SCALE));

    maj_scale=parse_scale( "Harmo_Scale 024579b");
    
    print_scale(maj_scale);
    /*
    S_MODES *maj_modes =malloc(sizeof(S_MODES));
    maj_modes= generate_modes(maj_scale);
    print_modes(maj_modes);
    printf("\nprint 1\n" );
    printf("\nprint 1 %d \n", maj_modes->length );
    S_MODES *cop_modes =malloc(sizeof(S_MODES));
    copy_modes( cop_modes , maj_modes);

    print_modes(cop_modes);
   print_modes(maj_modes);

   


    CHORD_BITS chord= triads_at_fund(maj_scale);
    printf("\n%d chords are\n", chord );

    */
    
    //initialises the user savec info structure
    user_saved=malloc(sizeof(S_USERINFO));
    init_userinfo(user_saved);

  /*
    //copy_scale(user_saved->saved_scales->scales[0], maj_scale);
    save_scale(maj_scale, user_saved);
    char* str= "blbla 0";
    printf("%s",set_to_num(str));
    printf("%d num is,",atoi(set_to_num(str)));
    print_scale(user_saved->saved_scales->scales[0]);*/

    

  
    /* Intializes random number generator */
    srand((unsigned) time(&t));


    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    printf("Welcome to ScaleGen! Type 'help' for more informations...\n");



	char line[256];

  printf("  >>>");

	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin)){
			continue;
		/*if (line[0] == '\n')


			continue;*/
    }
		if (strstr(line, "Scale_Mode")!=NULL) {
            ScaleLoop();
			continue;
		} else if (strstr(line, "Chord_Mode")!=NULL)	{

            printf("\nchord mode isn't implemented yet\n");
            printf("  >>>");

			continue;
		} else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit MusicTool \n");
			printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'Scale_Mode' to enter Scale Mode\n");
			printf("\ntype 'Chord_Mode' to enter Chord Mode\n");
      printf("  >>>");

			continue;
		} else if(strstr(line, "quit")!=NULL)	{
        clear_userinfo(user_saved );
		    printf("\nYou have exited MusicTool\n");

			break;
		} else if(strstr(line, "exit")!=NULL)	{
        clear_userinfo(user_saved );
		    printf("\nYou have exited MusicTool\n");

			  exit(0);

		} else{
      printf("command not parsed correctly\n");
      printf("  >>>");
    }

		if(EXIT_INFO==true) break;

	}
  

 // clear_userinfo(user_saved);
	return 0;

}
