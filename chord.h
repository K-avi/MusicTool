#ifndef EXTCHORD_H 
#define EXTCHORD_H 

#include "types.h"


extern CHORD_EXT generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions);

extern S_SCALE extprog_to_scl(const S_EXTCHPROG* chprog);

extern void print_ext_chord( CHORD_EXT chord);

extern void ext_print_chprog( S_EXTCHPROG* extprog);

extern bool equals_extprog( S_EXTCHPROG* chpr1, S_EXTCHPROG* chpr2);

extern CHORD_EXT triadbits_to_chord( TRIADS_BITS triads);
extern CHORD_EXT triad_to_chord_ext( TRIAD triad);

extern S_EXTCHPROG* generate_ext_chprog( unsigned int argnum, ...);

#ifdef DEBUG 
extern PITCH_CLASS_SET extprog_to_pcs(const S_EXTCHPROG* chprog); 
extern void print_pcs( const PITCH_CLASS_SET pcs);

extern PITCH_CLASS_SET extchord_to_pcs(CHORD_EXT chord);
extern TRIAD extchord_to_chord( CHORD_EXT chord);

extern void print_extensions(S_EXTENSIONS extensions);
#endif

#endif