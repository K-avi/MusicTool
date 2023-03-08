#ifndef TRIADPRINT_H
#define TRIADPRINT_H

#include <stdio.h>
#include "types.h"
extern void print_triad_prog( S_TRIAD_PROG * chord_prog);
extern void fprint_triad_prog(FILE* f , S_TRIAD_PROG * chord_prog);

extern char * chord_to_str(TRIAD chord);
char*  bits_triad_to_str( TRIADS_BITS triad);
char *bits_deg_to_str(DEGREES_BITS deg);

#endif