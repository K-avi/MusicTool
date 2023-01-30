#ifndef CHORDGEN_H 
#define CHORDGEN_H 

#include "types.h"

extern PITCH_CLASS_SET get_degrees( S_SCALE scale);
extern void free_triad_prog(S_TRIAD_PROG* source);

extern TRIADS_IN_SCALE triads_at_fund( S_SCALE scale);

extern DEGREES get_deg_from_chdeg( PITCH_CLASS_SET deg); 

extern TRIAD generate_chord(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg);

extern bool equals_chprog( S_TRIAD_PROG* chpr1, S_TRIAD_PROG* chpr2);

extern S_SCALE chprog_to_scl(const S_TRIAD_PROG* chprog);
#ifdef DEBUG 
extern PITCH_CLASS_SET chprog_to_pcs(const S_TRIAD_PROG* chprog); 
extern void print_pcs( const PITCH_CLASS_SET pcs);

extern PITCH_CLASS_SET chord_to_pcs(TRIAD chord);
#endif

#endif