#ifndef CHORDPATTERN_H_INCLUDED
#define CHORDPATTERN_H_INCLUDED


#include "types.h"
extern SIGNED_BOOL contains_pattern( S_SCALE scale, CHORD_DEGREES chord_degrees);

extern void init_chord_book( S_CHORD_BOOK chord_book , CPT * nb_entries);


#endif