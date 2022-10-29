#ifndef HARMO_H_INCLUDED
#define HARMO_H_INCLUDED

#include "types.h"

extern void print_bits(S_SCALE x);
extern S_SCALE generate_nth_mode(S_SCALE scale, LENGTH mode);

extern S_SCALE rightRotate(S_SCALE ptr, CPT n);

extern CPT get_index_of_nth( S_SCALE scale, CPT n);
extern S_SCALE generate_nth_mode(S_SCALE scale, CPT n);
extern S_SCALE rotate_right_scale(S_SCALE scale, CPT n);
extern void print_modes(S_MODES  modes);

extern S_MODES  generate_modes( S_SCALE scale);
extern S_SCALE rotate_right_scale_yohan(S_SCALE scale, CPT n);

extern S_SCALE rot(S_SCALE scale, CPT n);



#endif // HARMO_H_INCLUDED
