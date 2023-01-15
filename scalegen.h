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
extern S_SCALE generate_nearby_scale (S_SCALE scale, LENGTH length);
extern S_INTERVAL_VECTOR generate_intv_vect(S_SCALE scale, LENGTH length);

#ifdef DEBUG
extern SIGNED_BOOL scale_comp_lexi( S_SCALE scl1, S_SCALE scl2);
extern unsigned short inverse_bit (S_SCALE scale );

extern S_INTERVAL_STRUCTURE get_interval_struct(S_SCALE scale);
extern int length_intv_struct(S_INTERVAL_STRUCTURE intervals);

extern void  print_intv_struct(S_INTERVAL_STRUCTURE intervals);
extern PITCH_CLASS_SET rot_pcs( PITCH_CLASS_SET scale, CPT n);

extern S_SCALE move_note(S_SCALE scale, LENGTH length);

#endif

#endif
