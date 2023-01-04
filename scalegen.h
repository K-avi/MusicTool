#ifndef SCALEGEN_H_INCLUDED
#define SCALEGEN_H_INCLUDED

#include "types.h"
#include <stdio.h>


#define EQUALS_SCALE(scl1, scl2) ( (scl1)==(scl2))

extern void add_note(S_SCALE* scale, NOTE note);
extern void sort_scale(S_SCALE * scale);
extern void add_rand_note(S_SCALE* scale);

extern S_SCALE generate_ran_scale(LENGTH length);

extern LENGTH get_length( S_SCALE scale);
extern LENGTH get_length_kerni(S_SCALE scale);
extern void print_scale( const S_SCALE scale);
extern void fprint_scale(FILE*f, const S_SCALE scale );

extern void set_scale( S_SCALE* scale, NOTE *arr, LENGTH length);


extern void print_array( NOTE *scale, LENGTH length);

extern S_SCALE * make_scale( NOTE *scale, LENGTH length);

extern S_SCALE inverse_scale(S_SCALE scale, LENGTH length);
extern S_SCALE complementary_scale(S_SCALE scale);


extern S_SCALE get_normal_scale(S_SCALE scale, LENGTH length);
extern S_SCALE get_normal_scale_modes(S_MODES modes, LENGTH length);

extern S_SCALE get_prime_scale(S_SCALE scale, LENGTH length);
extern S_SCALE get_inverse_scale(S_SCALE scale, LENGTH length);
extern S_SCALE get_complementary_scale(S_SCALE scale);


//testing only 

extern SIGNED_BOOL scale_comp_lexi( S_SCALE scl1, S_SCALE scl2);


#endif
