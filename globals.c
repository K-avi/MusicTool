#include "globals.h"
#include "types.h"
#include <stdlib.h>

S_USERINFO * user_data=NULL ; //user_saved stuff

CPT nb_entries=0;  //nb entries currently in chord_book 
CPT nb_entries_max=0; //maxnum of entries in chordbook

unsigned short compt_scale=0; //counts how many stuff were saved to print them; might have to make a global
unsigned short compt_harmo=0; //counts how many stuff were saved to print them; might have to make a global

NOTE triads[4][3]= { {0,4,7}, {0,3,7}, {0,3,6}, {0,4,8}}; 


bool succes=0;

//scale globals
S_SCALE tmp_saved_scale;
S_SCALE scale_to_save=0;
S_SCALE generated_scale=0;
LENGTH length=0;
SIGNED_LENGTH indexx=-1; //there's an index function in string.h so I had to rename the global n could not think of a better name
S_INTERVAL_STRUCTURE generated_intv_struct=0;
S_INTERVAL_VECTOR generated_intv_vect=0;
//harmo globals
 S_MODES tmp_saved_mode= NULL , parsed_modes=NULL;
 char* begin=NULL;
 S_MODES modes=NULL;

//chprog globals
S_CHORD_PROG * tmp_chprog=NULL;
S_CHORD_PROG* generated_chprog=NULL;
SIGNED_LENGTH l1=-1, l2=-1;

//dodec globals 
S_DODEC tmp_saved_dodec=0;
S_DODEC generated_dodec=0, dodec_to_save=0; 

