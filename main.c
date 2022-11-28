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
#include "chordgen.h"
#include "chordloop.h"

int main()
{
  
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
   
 
  //initialises the user saved info structure
  user_saved=malloc(sizeof(S_USERINFO));
  init_userinfo(user_saved);

  /* Intializes random number generator */
  time_t t;
  srand((unsigned) time(&t));



  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  printf("Welcome to MusicTool! Type 'help' for more informations...\n");



	char line[256];

  printf("  >>>");

	while (true) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin)){
			continue;
		
    }
		if (strstr(line, "scale mode")!=NULL) {
            ScaleLoop();
			continue;
		} else if (strstr(line, "chord mode")!=NULL)	{

            chordloop();
			continue;
		} else if (strstr(line, "help")!=NULL)	{

			printf("\ntype 'quit' to exit MusicTool \n");
			printf("\ntype 'exit' to exit MusicTool \n");
			printf("\ntype 'scale mode' to enter Scale Mode\n");
			printf("\ntype 'chord mode' to enter Chord Mode\n");
      printf("  >>>");

			continue;
		} else if(strstr(line, "quit")!=NULL)	{
         free_userinfo(user_saved);
		    printf("\nYou have exited MusicTool\n");

			break;
		} else if(strstr(line, "exit")!=NULL)	{
         free_userinfo(user_saved);
		    printf("\nYou have exited MusicTool\n");

			  exit(0);

		} else{
      printf("command not parsed correctly\n");
      printf("  >>>");
    }
	}

	return 0;

}
