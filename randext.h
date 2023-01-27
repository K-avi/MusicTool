
#ifndef RANDEXT_H
#define RANDEXT_H

#include "types.h"

//extern S_CHORD_PROG * generate_chord_prog(S_SCALE scale, LENGTH length);

extern TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads);

extern PITCH_CLASS_SET select_rand_degree(PITCH_CLASS_SET deg);



#endif