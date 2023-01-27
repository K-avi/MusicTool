#ifndef EXTCHORD_H 
#define EXTCHORD_H 

#include "types.h"


extern CHORD_EXT generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions);

extern bool equals_chprog( S_CHORD_PROG* chpr1, S_CHORD_PROG* chpr2);

extern S_SCALE extprog_to_scl(const S_EXTCHPROG* chprog);

extern void print_ext_chord( CHORD_EXT chord);
#ifdef DEBUG 
extern PITCH_CLASS_SET extprog_to_pcs(const S_EXTCHPROG* chprog); 
extern void print_pcs( const PITCH_CLASS_SET pcs);

extern PITCH_CLASS_SET extchord_to_pcs(CHORD_EXT chord);
extern CHORD extchord_to_chord( CHORD_EXT chord);

extern void print_extensions(S_EXTENSIONS extensions);
#endif

#endif