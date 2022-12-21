#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bitop.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "misc.h"
#include "chordgen.h"

#include "stdio.h"

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
  TRIADS_IN_SCALE* ret= malloc(length*sizeof(TRIADS_IN_SCALE));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=triads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

TRIADS_IN_SCALE * get_triads_length( S_SCALE scale, LENGTH length){// same as get triads but without calculating the length

  if( (!scale) || (! length)) return NULL;

  TRIADS_IN_SCALE* ret= malloc(length*sizeof(TRIADS_IN_SCALE));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=triads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

CHORD_DEGREES get_degrees( S_SCALE scale){//returns the degrees from which u can generate a triad in a scale
//stored as a ushort   
    if(!scale) return 0;

    LENGTH length = get_length(scale);

    CHORD_DEGREES ret= scale << 1;
    
    ret|= 1;

    CHORD_DEGREES mask= ret;
    //print_bits(ret);
    INDEX pos;

    S_MODES modes= generate_modes(scale);
  

    for(CPT i=0; i<length ; i++){

    
      if( !triads_at_fund(modes[i])){
        
         //printf("%d\n", i);
         pos=nth_bit_pos(mask,i+1);
         
        
         ret^=(1<<pos);
         //print_bits(ret);
      }// else print_scale(modes[i]);//si il n'y a pas de triades au mode i ; enleve le degre de la valeur de retour.
    }
    free(modes);
    return ret;

}//tested

CPT nb_deg( TRIADS_IN_SCALE* scl_triads, LENGTH length){//returns the number of degrees in a scale 
//that contain at least one chord.
  CPT ret=0;
   for(CPT i=0; i<length; i++){
    if (scl_triads[i]!=0) {ret++;}
   }
   return ret;
}

S_CHORD_PROG *chprogdup(  S_CHORD_PROG* source){//copies a cp from dest 

   if(!source ) return NULL;
   if(!source->length) return NULL;
   if(!source->chord_prog) return NULL;
  
   S_CHORD_PROG* ret=malloc(sizeof(S_CHORD_PROG));
   ret->length=source->length;
   ret->chord_prog=malloc(source->length* sizeof(CHORD));
   memcpy( ret->chord_prog, source->chord_prog, source->length);

   return ret;
}


//from formerly chordprog.c 

bool at_least_one_chord(TRIADS_IN_SCALE* scl_triads, LENGTH length){//returns 1 if at least one triad in a scale; 0 otherwise
  if( (!scl_triads) || length<=0) return 0;
  if(*scl_triads) return 1;
  else return at_least_one_chord(scl_triads++, length-1);
}

CPT nb_chords( TRIADS_IN_SCALE * scl_triads, LENGTH length){ //returns the number of chords u can generate in a scale
  if ((!scl_triads) || length <=0) return 0;
  else if( *scl_triads) return (count_bits(*scl_triads) + nb_chords(scl_triads+1, length-1));
  else return nb_chords(scl_triads++, length-1);
}

void free_chord_prog(S_CHORD_PROG* source){
  free(source->chord_prog);
  free(source);
}

//from rand.c cuz makes more sense here

 DEGREES get_deg_from_chdeg( CHORD_DEGREES deg){//converts a degree stored in chord_degrees format to degrees format; 
//in order to use it to generate the first 4 bits of a CHORD.

    DEGREES ret= nth_bit_pos(deg, 1);
    return ret;
}//tested

CHORD generate_chord(TRIADS_IN_SCALE triads, CHORD_DEGREES deg){//generates a chord from a triad and a degree 
  
  if(!triads || !deg) return 0;

  CHORD ret=0;

  switch(triads){
    case MIN_CHORD : ret=(MIN<<4); break;
    case MAJ_CHORD : ret=(MAJ<<4); break;
    case AUG_CHORD : ret=(AUG<<4); break;
    case DIM_CHORD : ret=(DIM<<4); break;
    default: ret=0; break;
  } 
  
  ret=ret |get_deg_from_chdeg(deg);

  return ret;
}