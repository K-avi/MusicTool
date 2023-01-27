#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bitop.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "misc.h"
#include "extchord.h"


//temporary file where everything related to extended chords is stored; will be dispatched when extended 
//chord implementation is done

CHORD_BITS extrelevant_at_fund (S_SCALE scale){//returns the relevant notes to generate triads on the first degree of a scale 

  S_SCALE triads= scale& TRIAD_MASK;
  //print_bits(triads);
  CHORD_BITS ret=0;
  ret= (triads  & (1<<2)) ? 1 : 0;
  ret|= (triads  & (1<<3)) ? (1<<1) : 0;
  ret|= (triads  & (1<<5)) ? (1<<2) : 0;
  ret|= (triads  & (1<<6)) ? (1<<3) : 0;
  ret|= (triads  & (1<<7)) ? (1<<4) : 0;
  ret|= (triads & (1<<1)) ? (1<<5) : 0;//sus2 n sus4 arent tested
  ret|= (triads & (1<<4)) ? (1<<6) : 0;
  return ret;
}//not tested 

TRIADS_IN_SCALE exttriads_at_fund( S_SCALE scale){ //returns the triads that can be generated from a scale stored as an uchar
  //the base value is zero
  TRIADS_IN_SCALE ret=0; 
  CHORD_BITS relevant_notes= extrelevant_at_fund(scale);
  ret= ( (relevant_notes & MIN_MASK)==MIN_MASK) ? 1 : 0;
  ret|= ( (relevant_notes & MAJ_MASK)==MAJ_MASK) ? (1<<1) : 0;
  ret|= ( (relevant_notes & DIM_MASK)== DIM_MASK) ? (1<<2) : 0;
  ret|= ( (relevant_notes & AUG_MASK)==AUG_MASK) ? (1<<3) : 0;
  ret|= (( relevant_notes & SUS2_MASK)== SUS2_MASK) ? (1<<4): 0;
  ret|= (( relevant_notes & SUS4_MASK)== SUS4_MASK) ? (1<<4): 0;
  return ret;
} //not tested 

TRIADS_IN_SCALE * extget_triads( S_SCALE scale){// returns the triads you can generate from a scale at each degree

  LENGTH length= get_length(scale);
  TRIADS_IN_SCALE* ret= malloc(length*sizeof(TRIADS_IN_SCALE));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=exttriads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

TRIADS_IN_SCALE * extget_triads_length( S_SCALE scale, LENGTH length){// same as get triads but without calculating the length

  if( (!scale) || (! length)) return NULL;

  TRIADS_IN_SCALE* ret= malloc(length*sizeof(TRIADS_IN_SCALE));

  S_MODES modes= generate_modes(scale);
  for (CPT i=0; i<length; i++) {
    ret[i]=exttriads_at_fund(modes[i]);
  }
  free(modes);
  return ret;
}

PITCH_CLASS_SET extget_degrees( S_SCALE scale){//returns the degrees from which u can generate a triad in a scale
//stored as a ushort   
    if(!scale) return 0;

    LENGTH length = get_length(scale);

    PITCH_CLASS_SET ret= scale << 1;
    
    ret|= 1;

    PITCH_CLASS_SET mask= ret;
    //print_bits(ret);
    INDEX pos;

    S_MODES modes= generate_modes(scale);
  

    for(CPT i=0; i<length ; i++){

    
      if( !exttriads_at_fund(modes[i])){
        
         //printf("%d\n", i);
         pos=nth_bit_pos(mask,i+1);  
        
         ret^=(1<<pos);
      }
    }
    free(modes);
    return ret;

}//tested

CPT extnb_deg( TRIADS_IN_SCALE* scl_triads, LENGTH length){//returns the number of degrees in a scale 
//that contain at least one chord.
  CPT ret=0;
   for(CPT i=0; i<length; i++){
    if (scl_triads[i]!=0) {ret++;}
   }
   return ret;
}//tested 

S_EXTCHPROG *extchprogdup(  S_EXTCHPROG* source){//copies a cp from dest 

   if(!source ) return NULL;
   if(!source->length) return NULL;
   if(!source->chprog) return NULL;
  
   S_EXTCHPROG* ret=malloc(sizeof(S_CHORD_PROG));
   ret->length=source->length;
   ret->chprog=malloc(source->length* sizeof(CHORD));
   memcpy( ret->chprog, source->chprog, source->length);

   return ret;
}//not tested

CPT extnb_chords( TRIADS_IN_SCALE * scl_triads, LENGTH length){ //returns the number of triads u can generate in a scale
  if ((!scl_triads) || length <=0) return 0;
  else if( *scl_triads) return (count_bits(*scl_triads) + extnb_chords(scl_triads+1, length-1));
  else return extnb_chords(scl_triads++, length-1);
}//tested

void free_extprog(S_EXTCHPROG* source){

  if(!source) return ;
  
  if(source->chprog){
    free(source->chprog);
  }
  free(source);
}//not tested 

 DEGREES extget_deg_from_chdeg( PITCH_CLASS_SET deg){//converts a degree stored in chord_degrees format to degrees format; 
//in order to use it to generate the first 4 bits of a CHORD.

    DEGREES ret= nth_bit_pos(deg, 1);
    return ret;
}//tested

CHORD_EXT generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions){//generates a chord from a triad and a degree 
  
  if(!triads || !deg) return 0;
  CHORD_EXT ret=0;

  switch(triads){
    case MIN_CHORD : ret=(MIN_EXT<<4); break;
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
}//not tested 

bool equals_extprog( S_EXTCHPROG* chpr1, S_EXTCHPROG* chpr2){//returns 1 if two chprog contain the same chords 
//0 otherwise.
  if(! (chpr1 && chpr2)) return 0;
  if(! (chpr1->chprog&& chpr2->chprog)) return 0;

  if(chpr1->length != chpr2->length) return 0;

  for (CPT i=0; i< chpr1->length; i++){
    if(chpr1->chprog[i]!=chpr2->chprog[i]) return 0;
  }

  return 1;

}//not tested



PITCH_CLASS_SET extchord_to_pcs(CHORD_EXT chord){
  //turns a chord into it's triad in chord degrees notation.

  if(!chord ) return 0;
  
  BITS ret= chord >>4;
  BITS degree = chord & 15;

  if(!ret )return 0;

  return rot_pcs(ret, degree);
}//not tested 

PITCH_CLASS_SET extprog_to_pcs(const S_EXTCHPROG* chprog){
  PITCH_CLASS_SET ret= 0;
  for (INDEX cpt =0; cpt < chprog->length ; cpt ++){
    
    ret|= extchord_to_pcs(chprog->chprog[cpt]);
  }
  return ret;
} //not tested 

S_SCALE extrog_to_scl(const S_EXTCHPROG* chprog){
  return extprog_to_pcs(chprog)>>1;
}//not tested 


TRIADS_IN_SCALE select_triad( CHORD_EXT chord){
  //selects a triad in a ext chord. 
  //The first triad tested is maj, then min, aug, dim, sus4, sus2

  S_SCALE scl= chord >>4;  //retrieves the "scale" in chord

  if( scl & MAJ_EXT){
    chord= MAJ_CHORD;
  }else if( scl & MIN_EXT){
    chord= MIN_CHORD;
  }else if( scl & AUG_EXT){
    chord=AUG_CHORD;
  }else if (scl & DIM_EXT){
    chord=DIM_CHORD;
  }else if (scl & SUS4_EXT){
    chord= SUS4_CHORD;
  }else if (scl & SUS2_EXT){
    chord= SUS2_CHORD;
  }else {
    chord=0;
  }
  printf("%d\n",chord);
  return chord;
}//yes

CHORD extchord_to_triad( CHORD_EXT chord){

  CHORD ret= chord& 0xF; //retrieves first 4 bits; 
  ret|= select_triad(chord)<<4;
  printf("%b\n", ret);
  return ret;
  
}//not tested 

char*  extbits_triad_to_str( TRIADS_BITS triad){//pretty self expleanatory
    switch (triad) {
    case MIN: return "m"; 
    case MAJ: return ""; 
    case DIM: return "-"; 
    case AUG: return "+"; 
    case SUS2: return "sus2"; 
    case SUS4: return "sus4";
    default: return NULL;
    }
}

CHORD_EXT pop_triad( S_EXTENSIONS extensions, TRIADS_IN_SCALE triad){
  //pops the degree of a triad; 
  CHORD_EXT ret=0;
  switch(triad){
    case (MAJ): ret= extensions^MAJ_EXT; break;
    case (MIN): ret= extensions^MIN_EXT; break;
    case(AUG): ret= extensions^AUG_EXT; break;
    case (DIM): ret= extensions^DIM_EXT; break;
    case(SUS2): ret= extensions^SUS2_EXT; break;
    case(SUS4): ret= extensions^SUS4_EXT; break;
    default : ret=0; break;
  }
  return ret;
}


char *extbits_deg_to_str(DEGREES_BITS deg){

    switch (deg) { //i dont like switch cases statements but these seem necessary
    case 0: return "I";
    case 1: return "bII";
    case 2: return "II";
    case 3: return "bIII";
    case 4: return "III";
    case 5: return "IV";
    case 6: return "bV";
    case 7: return "V";
    case 8: return "bVI";
    case 9: return "VI";
    case 10: return "bVII";
    case 11: return "VII";
    default: { return NULL;}
    }

}
char *bit_shift_to_degree(unsigned char num){

    switch(num){
      case(1):  return "b2";
      case(2):  return "2";
      case(3):  return "b3";
      case(4):  return "3";
      case(5):  return "4";
      case(6):  return "b5";
      case(7):  return "5";
      case(8):  return "b6"; 
      case(9):  return "6"; 
      case(10): return "b7"; 
      case(11): return "7";
      default:  return NULL;
    }
}
void print_extensions(S_EXTENSIONS extensions){//alors toi la putain de ta race jv te tuer

  if(!extensions) return ;
  LENGTH extnum= count_bits(extensions);
  LENGTH len= 0;
  if(extnum==0) return;
  else if(extnum==1) len= 5; 
  else len= 5+2*extnum-1;

  printf("add ");

  CPT cpt=0, bitindex=1, bitval; 
  CPT tmp=0;
  //printf("%d %d\n", len, cpt);
  //trying to make the formated string of chord+ extensions ; kinda hard tbf
  while (cpt < len-6){
   // printf("%d\n", tmp++ );
    bitval= nth_bit_pos(extensions, bitindex++)+1;
    //printf("bitval is: %d %c ; nthbitpos is: %d \n",bitval+'0', bitval+'0',bitval);
  
    printf("%s,",bit_shift_to_degree(bitval));
    cpt+=2; 
  }
  bitval= nth_bit_pos(extensions, bitindex++)+1;
  printf("%s", bit_shift_to_degree(bitval));
}



// bVIIsus4addb9,9,b3,3,b5,5,b6,6,b7,7
//longest of these mofo is 31 characters long wtfs

void print_ext_chord( CHORD_EXT chord){

  /*should do it like -> degree (same as chord)
                      -> triad (redo it in chord)
                      -> extensions (if null then null) else add I,J,...    
  */
  
  if(!chord)return ;
  
  DEGREES_BITS degree= chord & 0xF; 
  CHORD triad= extchord_to_triad(chord);
  printf("%d\n", triad);

  S_EXTENSIONS extensions= pop_triad(chord>>4, degree); //I need to pop the bits of the triad 

  char* strdeg= extbits_deg_to_str(degree);
  char* strtriad= extbits_triad_to_str(triad);

  printf("%s%s", strdeg, strtriad);
  //print_extensions(extensions);
  return;
}//not tested 


void print_extchprog(S_EXTCHPROG* extprog){

}
