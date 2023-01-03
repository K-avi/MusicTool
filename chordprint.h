#ifndef CHORDPRINT_H
#define CHORDPRINT_H

#include <stdio.h>
#include "types.h"
extern void print_chord_prog( S_CHORD_PROG * chord_prog);
extern void fprint_chord_prog(FILE* f , S_CHORD_PROG * chord_prog);

extern char * chord_to_str(CHORD chord);
#endif