#ifndef CHORDGEN_H_INCLUDED
#define CHORDGEN_H_INCLUDED

#include "types.h"

extern CHORD_BITS triads_at_fund (S_SCALE  scale); //only for test 
extern TRIADS_IN_SCALE triads_at_fund( S_SCALE scale); //only for test
extern TRIADS_IN_SCALE * get_triads( S_SCALE scale);

extern TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads); //maybe just for tests

extern DEGREES * get_degrees( S_SCALE scale);

extern TRIADS_IN_SCALE * get_triads_length( S_SCALE scale, LENGTH length);// same as get triads but without calculating the length
extern DEGREES * get_degrees_length( S_SCALE scale ,LENGTH length);//same as get degrees but without calculating the length of the scale

extern  CPT nb_deg( TRIADS_IN_SCALE* scl_triads, LENGTH length);

extern S_CHORD_PROG* chprogdup(  S_CHORD_PROG* source);
#endif
