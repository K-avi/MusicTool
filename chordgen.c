#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitop.h"
#include "triadgen.h"
#include "triadprint.h"
#include "parsing.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "misc.h"
#include "chordgen.h"
#include "rand.h"
#include <stdarg.h> //ohboy

//temporary file where everything related to extended chords is stored; will be dispatched when extended 
//chord implementation is done

S_CHPROG *chprog_dup(  S_CHPROG* source){//copies a cp from source

   if(!source ) return NULL;
   if(!source->length) return NULL;
   if(!source->chprog) return NULL;
  
   S_CHPROG* ret=malloc(sizeof(S_CHPROG));
   ret->length=source->length;
   ret->chprog=malloc(source->length* sizeof(CHORD));
   memcpy( ret->chprog, source->chprog, source->length*sizeof(CHORD));
  
   return ret;
}//tested


void free_chord_prog(S_CHPROG* source){

  if(!source) return ;
  if(source->chprog){
    free(source->chprog);
  }
  free(source);
}//tested 

 DEGREES extget_deg_from_chdeg( PITCH_CLASS_SET deg){//converts a degree stored in chord_degrees format to degrees format; 
//in order to use it to generate the first 4 bits of a CHORD.

    DEGREES ret= nth_bit_pos(deg, 1);
    return ret;
}//tested

CHORD generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions){//generates a chord from a triad and a degree 
  
  if(!triads || !deg) return 0;
  CHORD ret=0;

  switch(triads){
    case MIN_CHORD : ret=(MIN<<4); break;
    case MAJ_CHORD : ret=(MAJ<<4); break;
    case AUG_CHORD : ret=(AUG<<4); break;
    case DIM_CHORD : ret=(DIM<<4); break;
    case SUS2_CHORD : ret=(SUS2<<4); break;
    case SUS4_CHORD: ret=(SUS4<<4); break;
    default: ret=0; break;
  } 
  ret|= extensions<<4;
  ret=ret |extget_deg_from_chdeg(deg);
  return ret;
}

bool equals_extprog( S_CHPROG* chpr1, S_CHPROG* chpr2){//returns 1 if two chprog contain the same chords 
//0 otherwise.
  if(! (chpr1 && chpr2)) return 0;
  if(! (chpr1->chprog&& chpr2->chprog)) return 0;

  if(chpr1->length != chpr2->length) return 0;

  for (CPT i=0; i< chpr1->length; i++){
    if(chpr1->chprog[i]!=chpr2->chprog[i]) return 0;
  }
  return 1;
}//not tested



PITCH_CLASS_SET extchord_to_pcs(CHORD chord){
  //turns a chord into it's triad in chord degrees notation.

  if(!chord ) return 0;
  
  BITS ret= chord >>3;
  BITS degree = chord & 15;

  if(!ret )return 0;

  return rot_pcs(ret, degree);
}//not tested 

S_SCALE chord_to_scl( CHORD chord){
   if(!chord ) return 0;
  
  BITS ret= chord >>4;
  BITS degree = chord & 15;

  if(!ret )return 0;

  return rot(ret, degree);
}

PITCH_CLASS_SET extprog_to_pcs(const S_CHPROG* chprog){
  PITCH_CLASS_SET ret= 0;
  for (INDEX cpt =0; cpt < chprog->length ; cpt ++){
    
    ret|= extchord_to_pcs(chprog->chprog[cpt]);
  }
  return ret;
} //not tested 

S_SCALE extprog_to_scl(const S_CHPROG* chprog){
  PITCH_CLASS_SET ret= 0;
  for (INDEX cpt =0; cpt < chprog->length ; cpt ++){
    
    ret|= chord_to_scl(chprog->chprog[cpt]);
  }
  return ret;
}// tested 


TRIADS_IN_SCALE select_triad( CHORD chord){
  //selects a triad in a ext chord. 
  //The first triad tested is maj, then min, aug, dim, sus4, sus2
  S_SCALE scl= (chord >>4) ;  //retrieves the "scale" in chord

  TRIADS_IN_SCALE ret=0;
  if(  (scl & MAJ_EXT)==MAJ_EXT){ 
    ret= MAJ_CHORD;
  }else if( (scl & MIN_EXT)==MIN_EXT){  
    ret= MIN_CHORD;
  }else if( (scl & AUG_EXT) ==AUG_EXT){
    ret=AUG_CHORD;
  }else if ( (scl & DIM_EXT)==DIM_EXT){
    ret=DIM_CHORD;
  }else if ( (scl & SUS4_EXT) ==SUS4_EXT){
    ret= SUS4_CHORD;

  }else if ( (scl & SUS2_EXT)==SUS2_EXT){
    ret= SUS2_CHORD;

  }else {
    print_scale(scl);
    ret=0;
  }
  return ret;
}//yes

TRIADS_BITS triad_in_scl_to_triad_bits( TRIADS_IN_SCALE triads){
  switch (triads){
    case MIN_CHORD: return MIN; 
    case MAJ_CHORD: return MAJ; 
    case AUG_CHORD: return AUG; 
    case DIM_CHORD: return DIM; 
    case SUS2_CHORD: return SUS2; 
    case SUS4_CHORD: return SUS4; 
    default:  return 0;
  }
}

CHORD triad_to_chord_ext( TRIAD triad){
  return (triad & 0xF) | (triadbits_to_chord(triad>>4))<<4;
}

TRIAD extchord_to_triad( CHORD chord){

  TRIAD ret= (chord& 0xF); //retrieves first 4 bits which store the degree 
  ret|= triad_in_scl_to_triad_bits(select_triad(chord))<<4; 
  return ret;
  
}//kinda tested 

CHORD pop_triad( S_EXTENSIONS extensions, TRIADS_BITS triad){
  //pops the triad passed as arg in the extensions of a chord
 
  CHORD ret=0;
  switch(triad){
    case (MAJ): ret= extensions^MAJ_EXT; break;
    case (MIN): ret= extensions^MIN_EXT; break;
    case(AUG): ret= extensions^AUG_EXT; break;
    case (DIM): ret= extensions^DIM_EXT; break;
    case(SUS2): ret= extensions^SUS2_EXT; break;
    case(SUS4): ret= extensions^SUS4_EXT; break;
    default : ret=extensions; break;
  }
  return ret;
}//tested


CHORD triad_in_scl_to_chord( TRIADS_IN_SCALE triads){
  printf("in tr to chord tr is : %d\n", triads);
  switch (triads){
    case MIN_CHORD: printf(" oui");return MIN_EXT; 
    case MAJ_CHORD: return MAJ_EXT; 
    case AUG_CHORD: return AUG_EXT; 
    case DIM_CHORD: return DIM_EXT; 
    case SUS2_CHORD: return SUS2_EXT; 
    case SUS4_CHORD: return SUS4_EXT; 
    default:  printf("HOW!???") ;return 1<<15;
  }
}

CHORD triadbits_to_chord( TRIADS_BITS triads){
  switch (triads){
    case MIN: return MIN_EXT; 
    case MAJ: return MAJ_EXT; 
    case AUG: return AUG_EXT; 
    case DIM: return DIM_EXT; 
    case SUS2: return SUS2_EXT; 
    case SUS4: return SUS4_EXT; 
    default:  return 1<<15;
  }
}