#ifndef HARMO_H_INCLUDED
#define HARMO_H_INCLUDED

#include "types.h"
#include <stdio.h>

extern void print_bits(S_SCALE x);

extern void print_modes(S_MODES  modes);
extern void fprint_modes( FILE* f, S_MODES modes);

extern S_MODES  generate_modes( S_SCALE scale);


extern S_SCALE rot(S_SCALE scale, CPT n);



#endif // HARMO_H_INCLUDED
