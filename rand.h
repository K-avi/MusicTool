
#ifndef RAND_H
#define RAND_H

#include "types.h"

extern S_TRIAD_PROG * generate_chord_prog(S_SCALE scale, LENGTH length);

extern TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads);

extern PITCH_CLASS_SET select_rand_degree(PITCH_CLASS_SET deg);

extern TRIADS_IN_SCALE select_rand_triads(TRIADS_IN_SCALE triads);

extern S_CHPROG* generate_ext_chprog( char * args);

#endif