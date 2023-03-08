#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"
#include <stdbool.h>



extern  S_USERINFO * user_data;


extern bool EXIT_INFO;
extern unsigned short compt_scale;
extern unsigned short compt_harmo;


/*
extern NOTE triads[4][3];
#define MAJ 0 //macros to index the triads array
#define MIN 1
#define DIM 2
#define AUG 3 
*/
/* irrelevant*/


extern bool succes;

//scale globals
extern S_SCALE tmp_saved_scale ;
extern S_SCALE scale_to_save ;
extern S_SCALE generated_scale;
extern LENGTH scl_length;
extern SIGNED_LENGTH indexx, index2; //there's an index function in string.h so I had to rename the global n could not think of a better name
extern S_INTERVAL_STRUCTURE generated_intv_struct;
extern S_INTERVAL_VECTOR generated_intv_vect;
//harmo globals
extern  S_MODES tmp_saved_mode, parsed_modes;
extern  char* begin;
extern  S_MODES modes;

//triad prog globals
extern S_TRIAD_PROG * tmp_triad;
extern S_TRIAD_PROG* generated_triad;
extern SIGNED_LENGTH l1, l2;


//ch prog globals
extern S_CHPROG * tmp_prog;
extern S_CHPROG* generated_prog;
extern SIGNED_LENGTH l3, l4;

//dodec globals 
extern S_DODEC tmp_saved_dodec;
extern S_DODEC generated_dodec, dodec_to_save ; 
extern S_DODEC* tmp_matrix;


//syntaxcheck global

extern bool _syntaxcheck;

//progbook globals 

extern S_DEGREE_PROG * parsed_prog_deg;

extern PROGBOOK * progbook;
extern unsigned int _book_realloc;
extern unsigned int _booksize_default;
extern unsigned int _book_realloc_small;
extern unsigned int _book_init_small;

#endif
