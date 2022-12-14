#include <stdio.h>
#include <stdlib.h>
#include "chordgen.h"
#include "harmo.h"
#include "globals.h"
#include "scalegen.h"
#include "types.h"
#include "misc.h"
#include "chordprog.h"
#include "harmo.h"


void set_chord_prog( S_CHORD_PROG * chord_prog, LENGTH length, TRIADS_IN_SCALE * triads, DEGREES* degrees){
    //sets the length in a chord prog to length passed as argument, and sets pointer in chord_prog->triads n chord_prog->degrees 
    //to pointers passed as argument ; !!!! does not copy them; potentially dangerous. Don't use unchecked
    if( !chord_prog) chord_prog=malloc(sizeof(S_CHORD_PROG));
    chord_prog->length=length;
    chord_prog->degrees=degrees;
    chord_prog->triads=triads;
}//should be moved to another file
//obsolete


unsigned char at_least_one_chord(TRIADS_IN_SCALE* scl_triads, LENGTH length){//returns 1 if at least one triad in a scale; 0 otherwise
  if( (!scl_triads) || length<=0) return 0;
  if(*scl_triads) return 1;
  else return at_least_one_chord(scl_triads++, length-1);
}
CPT nb_chords( TRIADS_IN_SCALE * scl_triads, LENGTH length){ //returns the number of chords u can generate in a scale
  if ((!scl_triads) || length <=0) return 0;
  else if( *scl_triads) return (count_bits(*scl_triads) + nb_chords(scl_triads+1, length-1));
  else return nb_chords(scl_triads++, length-1);
}


DEGREES * degrees_with_chords(TRIADS_IN_SCALE * triads, LENGTH length,CPT deg){//returns an array containing the degrees at which 
//there is at least 1 triad in a scale; used then to index a triads array like an associative array

  if(!triads|| deg <=0 || length<=0) return NULL;
  
  DEGREES * ret= malloc(deg*sizeof(DEGREES));
  CPT i=0;
  for(CPT cpt=0; cpt<length; cpt++){
    if(triads[cpt]!=0) { ret[i++]= cpt;}
  }
  return ret;
}



void free_chord_prog( S_CHORD_PROG * chord_prog){ //need to put it in chordgen or smtg
    if(!chord_prog) return;
    if(chord_prog->degrees) free(chord_prog->degrees);
    if(chord_prog->triads) free(chord_prog->triads);
    free(chord_prog);
}


