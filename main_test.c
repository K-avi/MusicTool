#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "harmo.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"
#include "scaleloop.h"
#include "init.h"
#include "user_info.h"



int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
   
 

  user_saved=malloc(sizeof(S_USERINFO));
  init_userinfo(user_saved);

/*
  save_scale(1370, user_saved);
  save_scale(1371, user_saved);

  

  S_MODES eccle_modes= generate_modes(1370);
  S_MODES other_modes= generate_modes(1371);

  save_modes(eccle_modes, user_saved);
  save_modes(other_modes, user_saved);


  remove_scale( user_saved, 2);
  //print_saved_scale(user_saved, 2);
  
  remove_modes( user_saved, 2 );
  print_saved_modes(user_saved, 2);
  //ScaleLoop();

  
  if(eccle_modes) free(eccle_modes);
  if(other_modes) free(other_modes);*/
  ScaleLoop();
  free_userinfo(user_saved);
   return 0;

}
