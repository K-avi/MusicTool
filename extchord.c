#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitop.h"
#include "chordgen.h"
#include "chordprint.h"
#include "parsing.h"
#include "randext.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "misc.h"
#include "extchord.h"
#include "rand.h"
#include <stdarg.h> //ohboy

//temporary file where everything related to extended chords is stored; will be dispatched when extended 
//chord implementation is done

CHORD_BITS extrelevant_at_fund (S_SCALE scale){//returns the relevant notes to generate triads on the first degree of a scale 

  S_SCALE triads= scale& EXTTRIAD_MASK;

  CHORD_BITS ret=0;
  ret= (triads  & (1<<2)) ? 1 : 0; //if minor third
  ret|= (triads  & (1<<3)) ? (1<<1) : 0; //if major third
  ret|= (triads  & (1<<5)) ? (1<<2) : 0; //if tritone
  ret|= (triads  & (1<<6)) ? (1<<3) : 0; //if fifth
  ret|= (triads  & (1<<7)) ? (1<<4) : 0;// if augmented fifth
  ret|= (triads & (1<<1)) ? (1<<5) : 0;//sus2 n sus4 arent tested
  ret|= (triads & (1<<4)) ? (1<<6) : 0;//if fourth
  
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
  ret|= (( relevant_notes & SUS4_MASK)== SUS4_MASK) ? (1<<5): 0;
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
    INDEX pos;
    S_MODES modes= generate_modes(scale);

    for(CPT i=0; i<length ; i++){
 
      if( !exttriads_at_fund(modes[i])){

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
  
   S_EXTCHPROG* ret=malloc(sizeof(S_EXTCHPROG));
   ret->length=source->length;
   ret->chprog=malloc(source->length* sizeof(CHORD_EXT));
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
}//tested 

 DEGREES extget_deg_from_chdeg( PITCH_CLASS_SET deg){//converts a degree stored in chord_degrees format to degrees format; 
//in order to use it to generate the first 4 bits of a CHORD.

    DEGREES ret= nth_bit_pos(deg, 1);
    return ret;
}//tested

CHORD_EXT generate_chord_ext(TRIADS_IN_SCALE triads, PITCH_CLASS_SET deg, S_SCALE extensions){//generates a chord from a triad and a degree 
  
  if(!triads || !deg) return 0;
  CHORD_EXT ret=0;

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
}// tested 


TRIADS_IN_SCALE select_triad( CHORD_EXT chord){
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
TRIADS_BITS triad_to_triad_bits( TRIADS_IN_SCALE triads){
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

TRIAD extchord_to_triad( CHORD_EXT chord){

  TRIAD ret= (chord& 0xF); //retrieves first 4 bits which store the degree 
  ret|= triad_to_triad_bits(select_triad(chord))<<4; //wtf
  return ret;
  
}//kinda tested 

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
}//tested

CHORD_EXT pop_triad( S_EXTENSIONS extensions, TRIADS_BITS triad){
  //pops the triad passed as arg in the extensions of a chord
 
  CHORD_EXT ret=0;
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


char *extbits_deg_to_str(DEGREES_BITS deg){
//same as in chprog; redundant
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
}//tested
char *bit_shift_to_degree(unsigned char num){//turns a 
//bit shift into a degree str

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
}//tested

void print_extensions(S_EXTENSIONS extensions){//prints the extensions of an extended chprog in the 
//command line

  if(!extensions) return ;
  LENGTH extnum= count_bits(extensions);
  LENGTH len= 0;
  if(extnum==0) return;
  else if(extnum==1) len= 5; 
  else len= 5+2*extnum-1;

  printf(" add ");

  CPT cpt=0, bitindex=1, bitval; 
  CPT tmp=0;

  while (cpt < len-6){

    bitval= nth_bit_pos(extensions, bitindex++)+1; 
    printf("%s,",bit_shift_to_degree(bitval));
    cpt+=2; 
  }
  bitval= nth_bit_pos(extensions, bitindex++)+1;
  printf("%s", bit_shift_to_degree(bitval));
}//tested



void print_ext_chord( CHORD_EXT chord){//prints an extended chord to command line
 
  if(!chord)return ;
  
  DEGREES_BITS degree= chord & 0xF; 
  TRIAD triad= extchord_to_triad(chord);
  S_EXTENSIONS extensions= pop_triad( (chord>>4), triad >>4); //I need to pop the bits of the triad 
  
  char* strdeg= extbits_deg_to_str(degree); 
  char* strtriad= extbits_triad_to_str((triad>>4));

  printf("%s%s", strdeg, strtriad);
  print_extensions(extensions);
}//works 




void ext_print_chprog( S_EXTCHPROG* extprog){

    if(!( extprog && extprog->chprog)) return;
    LENGTH l=extprog->length; 

    printf("[ ");
    for(CPT i=0; i<l-1; i++){
      print_ext_chord(extprog->chprog[i]);
      printf(" ; ");
    }
    print_ext_chord(extprog->chprog[l-1]); 
    printf(" ]\n");
}


CHORD_EXT triad_to_chord( TRIADS_IN_SCALE triads){
  switch (triads){
    case MIN_CHORD: return MIN_EXT; 
    case MAJ_CHORD: return MAJ_EXT; 
    case AUG_CHORD: return AUG_EXT; 
    case DIM_CHORD: return DIM_EXT; 
    case SUS2_CHORD: return SUS2_EXT; 
    case SUS4_CHORD: return SUS4_EXT; 
    default:  return 1<<15;
  }
}



CHORD_EXT ext_gen_chord  (CHORD_EXT chord, CPT extension_num, CPT extension_total, TRIADS_IN_SCALE triad){
    //erases randoms extensions from chord in order to keep extension_num extensions. 
    //returns chord if extension_total < extension_num 
    //triad is used to pop out n in the triad from chord 

    //various validity checks
    if(!chord ) return 0; 
    if(extension_total>9 ) return 0;
    if(extension_num > extension_total) return 0;

    //extension_total is also the lentgth of the scale in chord (how many bits set n so on)
    if(extension_total==0) return chord;
    S_EXTENSIONS chord_extension= chord>>4; 

    chord_extension= pop_triad(chord_extension, triad_to_triad_bits(triad));
    unsigned char rand_index= nth_bit_pos( chord_extension, rand()%extension_total+1);

    for(CPT i=0; i<extension_total-extension_num; i++){
        chord_extension= POP_BIT( chord_extension, rand_index);
        rand_index= nth_bit_pos( chord_extension, rand()%(extension_total-i)+1);

    }
    CHORD_EXT ret=  chord & 0xF;
    chord_extension=pop_triad(chord_extension, triad_to_triad_bits( triad));
    ret|= chord_extension<<4;
    return ret; 

}//problem cuz it can kill the triad which is real bad
//this function is: awful 



S_EXTCHPROG* generate_ext_chprog( unsigned int argnum, ...){
   /*
   should be able to take arguments 
  -length=n | rand
  -scllen=n | rand 
  -scale={...} | rand 
  -extnum=1...n | rand ; should be made more complete after that (like min ext max ext etcs)
   */
  if(argnum==0){/*generation without arguments is gonna be goofy; I don't 
  want it to rely on a specific scale. It's gonna change scale at each chord because I said so*/

      LENGTH proglength= rand()%10+1; //proglength between 1 and 10 

      S_SCALE scl= 0;//scl of min length 6 to make sure a chord can be generated
      CPT extension_num=0; 
      
      CHORD_EXT curchord= 0; //chord to pop extensions from 

      PITCH_CLASS_SET relevant_deg= 0; //gets deg of scl 
      PITCH_CLASS_SET selected_deg= 0;
      DEGREES selected_deg_converted= 0;

      S_SCALE curmode = 0;
      TRIADS_IN_SCALE curtriads= 0;
      TRIADS_IN_SCALE seltriads= 0;
  
      S_EXTCHPROG *ret=  malloc( sizeof(S_EXTCHPROG));
      ret->chprog= malloc(proglength* sizeof( CHORD_EXT));
      ret->length=proglength;

      for(CPT i=0; i<proglength; i++){
          
        scl=generate_ran_scale( 8);
        extension_num=count_bits(scl)-2;

        relevant_deg=get_degrees(scl); 
        selected_deg= select_rand_degree(relevant_deg);
        selected_deg_converted= get_deg_from_chdeg(selected_deg);
        
        curmode= rot( scl, nth_bit_pos(selected_deg, 1));

        curtriads=triads_at_fund(curmode); 
        seltriads=select_rand_triads(curtriads);

        curchord=selected_deg_converted | (curmode <<4);
      
        if(extension_num){
          curchord= ext_gen_chord(curchord, rand()%extension_num, extension_num, seltriads);
        }else { 
          curchord= ext_gen_chord(curchord, 0, 0, seltriads);
        }

        ret->chprog[i] = curchord;
      }
      return ret;
      
  }else{ 
      va_list ap;
      va_start(ap, argnum);

      CPT i=0 ;
      char* arg;
      LENGTH proglength=0, scllen=0;
      char extension_max=-1;
      S_SCALE scl=0;

      for(i=0; i<argnum; i++){//retrieves the arguments for generation. 
        arg=va_arg(ap, char*); 
        if(!strncmp(arg, "-length=",8)){
            if(isdigit(*(arg+8))){
              proglength=atoi(arg+8); 
            }
        }else if(!strncmp(arg, "-scllen=", 8)){
            if(isdigit(*(arg+8))){
              scllen=atoi(arg+8); 
            }
        }else if(!strncmp(arg, "-extmax=", 8)){  
            if(isdigit(*(arg+8))){
              extension_max= atoi(arg+8);
            }
          
        }else if(!strncmp(arg, "-scl=", 5)){      
            scl=parse_scale(arg+5);
        }//default behavior for invalid args is to ignore them; might be bad dunno
      }
      va_end(ap);

      if(scl && scllen) scllen=0; /*scl and scllen are mutually exclusive; scl is more important I think.
      this behavior might change idk yet*/

      if(scllen){ //sets scl if scllen is set 
        scl=generate_ran_scale(scllen);
      }else if(!scl){ //sets scale if not the case
        scl=generate_ran_scale(rand()%4+8);
      }

      if(!proglength){
        proglength=rand()%10+1;
      }

      if(extension_max==-1){
        extension_max=9;
      }

      CPT extension_num= count_bits(scl)-2;
      extension_num= extension_num<0 ? 0 : extension_num; //prevents it from being negative
      CHORD_EXT curchord= 0; //chord to pop extensions from 

      PITCH_CLASS_SET relevant_deg= extget_degrees(scl); //gets deg of scl 
      if(!relevant_deg) return NULL; //case if scale doesnt contain any chords

      PITCH_CLASS_SET selected_deg= 0;
      DEGREES selected_deg_converted= 0;

      S_SCALE curmode = 0;
      TRIADS_IN_SCALE curtriads= 0;
      TRIADS_IN_SCALE seltriads= 0;
  
      S_EXTCHPROG *ret=  malloc( sizeof(S_EXTCHPROG));
      ret->chprog= malloc(proglength* sizeof( CHORD_EXT));
      ret->length=proglength;
      
      for(CPT i=0; i<proglength; i++){

        selected_deg= select_rand_degree(relevant_deg);
        selected_deg_converted= extget_deg_from_chdeg(selected_deg);
        
        curmode= rot( scl, nth_bit_pos(selected_deg, 1));
        curtriads=exttriads_at_fund(curmode); 
  
        seltriads=select_rand_triads(curtriads);
        curchord=selected_deg_converted | (curmode <<4);

        if(extension_num ){
          if(!extension_max){
            curchord= ext_gen_chord(curchord,0 , extension_num, seltriads);
          }else{
            extension_max= extension_max>extension_num ? extension_num: extension_max;
            curchord= ext_gen_chord(curchord, extension_max, extension_num, seltriads);
          }
        }else{
          curchord= ext_gen_chord(curchord, 0, 0, seltriads);
        }
        ret->chprog[i] = curchord;
      }
      return ret;
  }
  return NULL;
}