#ifndef GOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "types.h"



extern  S_USERINFO * user_saved;
extern bool EXIT_INFO;
extern unsigned short compt_scale;
extern unsigned short compt_harmo;

extern NOTE triads[4][3];
#define MAJ 0 //macros to index the triads array
#define MIN 1
#define DIM 2
#define AUG 3

#endif
