#include "globals.h"
#include "types.h"
#include <stdlib.h>

S_USERINFO * user_saved=NULL ;

unsigned short compt_scale=0; //counts how many stuff were saved to print them; might have to make a global
unsigned short compt_harmo=0; //counts how many stuff were saved to print them; might have to make a global

NOTE triads[4][3]= { {0,4,7}, {0,3,7}, {0,3,6}, {0,4,8}}; 
