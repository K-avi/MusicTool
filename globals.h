#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"



extern  S_USERINFO * user_saved;
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



extern S_CHORD_BOOK  chord_book; //the default chorg prog book.
extern CPT nb_entries;  //nb entries currently in chord_book 
extern CPT nb_entries_max; //maxnum of entries in chordbook

#endif
