#include "globals.h"
#include "types.h"
#include <stdlib.h>

//structure where u save stuff
S_USERINFO * user_data=NULL ; //user_saved stuff

//structure where functions r stored; mainly used for generics:

ALL_FUNC * funcs_struct= NULL;

/* currently useless
CPT nb_entries=0;  //nb entries currently in chord_book 
CPT nb_entries_max=0; //maxnum of entries in chordbook 
*/


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

