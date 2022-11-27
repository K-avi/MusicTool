
#ifndef RAND_H
#define RAND_H

#include "types.h"

extern S_CHORD_PROG * generate_chord_prog(S_SCALE scale, LENGTH length);

extern TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads);

#endif