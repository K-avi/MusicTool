#ifndef SCALEGEN_H_INCLUDED
#define SCALEGEN_H_INCLUDED

#include "types.h"

extern void add_note(S_SCALE* scale, NOTE note);
extern void sort_scale(S_SCALE * scale);
extern void add_rand_note(S_SCALE* scale);

extern S_SCALE generate_ran_scale(LENGTH length);

extern LENGTH get_length( S_SCALE scale);
extern LENGTH get_length_kerni(S_SCALE scale);
extern void print_scale( const S_SCALE scale);

extern void set_scale( S_SCALE* scale, NOTE *arr, LENGTH length);


extern void print_array( NOTE *scale, LENGTH length);

extern S_SCALE * make_scale( NOTE *scale, LENGTH length);


#endif
