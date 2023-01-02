#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "scalegen.h"
#include "types.h"
#include "init.h"
#include "parseloop.h"
#include "harmo.h"
#include "parsing.h"
#include "user_info.h"
#include "globals.h"
#include "chordgen.h"


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


  printf("Welcome to MusicTool! Type 'help' for more informations\n");
  printf("  >>>");

  parseloop();

  free_userinfo(user_saved);
  return 0;
}
