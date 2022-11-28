#ifndef CHORDPROG_H_INCLUDED
#define CHORDPROG_H_INCLUDED

#include "types.h"

extern void set_chord_prog( S_CHORD_PROG * chord_prog, LENGTH length, TRIADS_IN_SCALE * triads, DEGREES* degrees);
extern DEGREES * degrees_with_chords(TRIADS_IN_SCALE * triads, LENGTH length,CPT deg);

extern void free_chord_prog( S_CHORD_PROG * chord_prog);

#endif