#ifndef CHORDPRINT_H
#define CHORDPRINT_H

#include <stdio.h>
#include "types.h"
extern void print_triad_prog( S_TRIAD_PROG * chord_prog);
extern void fprint_triad_prog(FILE* f , S_TRIAD_PROG * chord_prog);

extern char * chord_to_str(TRIAD chord);
#endif