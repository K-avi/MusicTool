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
  print_bits(triads);
  CHORD_BITS ret=0;
  ret= (triads  & (1<<2)) ? 1 : 0;
  ret|= (triads  & (1<<3)) ? (1<<1) : 0;
  ret|= (triads  & (1<<5)) ? (1<<2) : 0;
  ret|= (triads  & (1<<6)) ? (1<<3) : 0;
  ret|= (triads  & (1<<7)) ? (1<<4) : 0;
  return ret;
}

TRIADS_IN_SCALE triads_at_fund( S_SCALE scale){ //returns the triads that can be generated from a scale stored as an uchar
  
  TRIADS_IN_SCALE ret=0; 
  CHORD_BITS relevant_notes= relevant_at_fund(scale);
  ret= ( (relevant_notes & MIN_MASK)==MIN_MASK) ? 1 : 0;
  ret|= ( (relevant_notes & MAJ_MASK)==MAJ_MASK) ? (1<<1) : 0;
  ret|= ( (relevant_notes & DIM_MASK)== DIM_MASK) ? (1<<2) : 0;
  ret|= ( (relevant_notes & AUG_MASK)==AUG_MASK) ? (1<<3) : 0;

  return ret;
} //doesnt work bc thats not how & works 

TRIADS_IN_SCALE * get_triads( S_SCALE scale){// returns the triads you can generate from a scale at each degree

//not done yet
  LENGTH length= get_length(scale);
  CHORD_BITS* ret= malloc(length*sizeof(CHORD_BITS));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=triads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

void print_triad( TRIADS_IN_SCALE triads){//prints which triads a scale contains
  if( !triads){ printf(" this scale doesn't contain any triads :/\n"); return;}
  if( MIN_CHORD & triads){
    printf( "this scale contains the minor chord\n");
  }
  if(MAJ_CHORD & triads){
    printf( "this scale contains the major chord\n");
  }
  if( DIM_CHORD & triads){
    printf( "this scale contains the diminished chord\n");
  }
  if( AUG_CHORD & triads){
    printf( "this scale contains the augmented chord\n");
  }
}




TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads){
  
  if(!triads) return 0;
  LENGTH length=get_length(triads);
  unsigned select=rand()%length;
  
  CPT cpt=0, incr=0;
  while(incr < select){
    if(1 <<incr & triads) cpt=incr;
    incr++;
  }
  return (1<<cpt);
}

LENGTH *select_random_degrees(S_SCALE scale, LENGTH scale_length, CPT num){
  
  if(num>scale_length) return NULL;
  
  LENGTH* ret= malloc(num*sizeof(LENGTH));
  CPT j=0;
  int ran=-1; 
  while( j <num){
    ran=rand()%13;
    if(ran==0) ret[j++]=1; 
    else if( (1<<ran) & scale) ret[j++]=ran;
  }
  return ret;
}

