#include "globals.h"
#include "types.h"
#include <stdlib.h>

S_USERINFO * user_data=NULL ; //user_saved stuff

CPT nb_entries=0;  //nb entries currently in chord_book 
CPT nb_entries_max=0; //maxnum of entries in chordbook

unsigned short compt_scale=0; //counts how many stuff were saved to print them; might have to make a global
unsigned short compt_harmo=0; //counts how many stuff were saved to print them; might have to make a global

NOTE triads[4][3]= { {0,4,7}, {0,3,7}, {0,3,6}, {0,4,8}}; 
