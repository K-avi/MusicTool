#ifndef CHORDGEN_H_INCLUDED
#define CHORDGEN_H_INCLUDED

#include "types.h"
#include "bitop.h"

CHORD_BITS triads_at_fund (S_SCALE  scale); //only for test 
TRIADS_IN_SCALE triads_at_fund( S_SCALE scale); //only for test
TRIADS_IN_SCALE * get_triads( S_SCALE scale);

TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads); //maybe just for tests

#endif
