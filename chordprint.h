#ifndef CHORDPRINT_H 
#define CHORDPRINT_H

#include "types.h"
#include <stdio.h>

extern void print_chprog( S_CHPROG* extprog);

extern void fprint_chord_prog( FILE* f, S_CHPROG* prog);
#endif