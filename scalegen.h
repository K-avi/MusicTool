#ifndef SCALEGEN_H_INCLUDED
#define SCALEGEN_H_INCLUDED

#include "types.h"

extern void add_note(S_SCALE* scale, NOTE note);
extern void sort_scale(S_SCALE * scale);
extern void add_rand_note(S_SCALE* scale);

extern S_SCALE* generate_ran_scale(LENGTH length);
extern void set_scale( S_SCALE* scale, int *arr, int length);

extern void print_scale( const S_SCALE *scale);
extern void print_array( NOTE *scale, LENGTH length);


#endif
