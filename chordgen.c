#include <stdlib.h>
#include <stdio.h>
#include "chordgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"




CHORD_BITS relevant_at_fund (S_SCALE scale){//returns the relevant notes to generate triads on the first degree of a scale 

  S_SCALE triads= scale& TRIAD_MASK;
  //print_bits(triads);
  CHORD_BITS ret=0;
  ret= (triads  & (1<<2)) ? 1 : 0;
  ret|= (triads  & (1<<3)) ? (1<<1) : 0;
  ret|= (triads  & (1<<5)) ? (1<<2) : 0;
  ret|= (triads  & (1<<6)) ? (1<<3) : 0;
  ret|= (triads  & (1<<7)) ? (1<<4) : 0;
  return ret;
}

TRIADS_IN_SCALE triads_at_fund( S_SCALE scale){ //returns the triads that can be generated from a scale stored as an uchar
  //the base value is zero
  TRIADS_IN_SCALE ret=0; 
  CHORD_BITS relevant_notes= relevant_at_fund(scale);
  ret= ( (relevant_notes & MIN_MASK)==MIN_MASK) ? 1 : 0;
  ret|= ( (relevant_notes & MAJ_MASK)==MAJ_MASK) ? (1<<1) : 0;
  ret|= ( (relevant_notes & DIM_MASK)== DIM_MASK) ? (1<<2) : 0;
  ret|= ( (relevant_notes & AUG_MASK)==AUG_MASK) ? (1<<3) : 0;

  return ret;
} 

TRIADS_IN_SCALE * get_triads( S_SCALE scale){// returns the triads you can generate from a scale at each degree

  LENGTH length= get_length(scale);
  CHORD_BITS* ret= malloc(length*sizeof(CHORD_BITS));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=triads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

TRIADS_IN_SCALE * get_triads_length( S_SCALE scale, LENGTH length){// same as get triads but without calculating the length

  CHORD_BITS* ret= malloc(length*sizeof(CHORD_BITS));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=triads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}



////////////////////


DEGREES * get_degrees( S_SCALE scale){ //returns the degrees from which u can generate a triad in a scale.
  DEGREES* ret= malloc(get_length(scale)*sizeof(DEGREES));
  ret[0]=0;
  CPT j=1;
  for(CPT i=0; i<12; i++){
    if( (1<<i) & scale) ret[j++]=i+1;
  }
  return ret;
}

DEGREES * get_degrees_length( S_SCALE scale ,LENGTH length){//same as get degrees but without calculating the length of the scale
  DEGREES* ret= malloc(length*sizeof(DEGREES)); 
  ret[0]=0;
  CPT j=1;
  for(CPT i=0; i<12; i++){
    if( (1<<i) & scale) ret[j++]=i+1;
  }
  return ret;
}


CPT nb_deg( TRIADS_IN_SCALE* scl_triads, LENGTH length){//returns the number of degrees in a scale 
//that contain at least one chord.
  CPT ret=0;
   for(CPT i=0; i<length; i++){
    if (scl_triads[i]!=0) {ret++;}
   }
   return ret;
}

S_CHORD_PROG* chprogdup(  S_CHORD_PROG* source){//copies a cp from dest 

    if(!source ) return NULL;
    if( (!source->degrees) ||  (!source->triads) || (!source->length)) return NULL;
    S_CHORD_PROG * ret= malloc(sizeof(S_CHORD_PROG));

    ret->length=source->length;
    ret->degrees= malloc(source->length*sizeof(DEGREES));
    ret->triads= malloc(source->length*sizeof(TRIADS_IN_SCALE));

    for( CPT i = 0; i<source->length; i++){
      ret->degrees[i]= source->degrees[i];
      ret->triads[i]= source->degrees[i];
    }

    return ret;
}