#ifndef CHORDGEN_H 
#define CHORDGEN_H 

#include "types.h"


extern CHORD generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions);
extern S_CHPROG *chprog_dup(  S_CHPROG* source);//not tested
extern S_SCALE extprog_to_scl(const S_CHPROG* chprog);

extern bool equals_extprog( S_CHPROG* chpr1, S_CHPROG* chpr2);

extern CHORD triadbits_to_chord( TRIADS_BITS triads);
extern CHORD triad_to_chord_ext( TRIAD triad);

extern TRIAD extchord_to_triad( CHORD chord);

extern CHORD pop_triad( S_EXTENSIONS extensions, TRIADS_BITS triad);

extern TRIADS_BITS triad_in_scl_to_triad_bits( TRIADS_IN_SCALE triads);

extern void free_chord_prog(S_CHPROG* source);

#ifdef DEBUG 
extern PITCH_CLASS_SET extprog_to_pcs(const S_CHPROG* chprog); 
extern void print_pcs( const PITCH_CLASS_SET pcs);

extern PITCH_CLASS_SET extchord_to_pcs(CHORD chord);
extern TRIAD extchord_to_chord( CHORD chord);

extern void print_extensions(S_EXTENSIONS extensions);
#endif

#endif