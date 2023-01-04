#ifndef CHORDGEN_H 
#define CHORDGEN_H 

#include "types.h"

extern CHORD_DEGREES get_degrees( S_SCALE scale);
extern void free_chord_prog(S_CHORD_PROG* source);

extern TRIADS_IN_SCALE triads_at_fund( S_SCALE scale);

extern DEGREES get_deg_from_chdeg( CHORD_DEGREES deg); 

extern CHORD generate_chord(TRIADS_IN_SCALE triads, CHORD_DEGREES deg);

extern bool equals_chprog( S_CHORD_PROG* chpr1, S_CHORD_PROG* chpr2);

#endif