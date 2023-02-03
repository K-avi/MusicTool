#include <stdlib.h>

#include "misc.h"
#include "chordgen.h"
#include "triadprint.h"
#include "chordprint.h"
#include "types.h"

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

void fprint_extensions(FILE *f, S_EXTENSIONS extensions){//prints the extensions of an extended chprog in the 
//command line

  if(!extensions) return ;
  LENGTH extnum= count_bits(extensions);
  LENGTH len= 0;
  if(extnum==0) return;
  else if(extnum==1) len= 5; 
  else len= 5+2*extnum-1;

  fprintf(f," add ");

  CPT cpt=0, bitindex=1, bitval; 
  CPT tmp=0;

  while (cpt < len-6){

    bitval= nth_bit_pos(extensions, bitindex++)+1; 
    fprintf(f,"%s,",bit_shift_to_degree(bitval));
    cpt+=2; 
  }
  bitval= nth_bit_pos(extensions, bitindex++)+1;
  fprintf(f,"%s", bit_shift_to_degree(bitval));
}//tested



void print_ext_chord( CHORD chord){//prints an extended chord to command line
 
  if(!chord)return ;
  
  DEGREES_BITS degree= chord & 0xF; 
  TRIAD triad= extchord_to_triad(chord);
  S_EXTENSIONS extensions= pop_triad( (chord>>4), triad >>4); //I need to pop the bits of the triad 
  
  char* strdeg= bits_deg_to_str(degree); 
  char* strtriad= bits_triad_to_str((triad>>4));

  printf("%s%s", strdeg, strtriad);
  print_extensions(extensions);
}//works 


void fprint_ext_chord(FILE * f, CHORD chord){//prints an extended chord to command line
 
  if(!chord)return ;
  
  DEGREES_BITS degree= chord & 0xF; 
  TRIAD triad= extchord_to_triad(chord);
  S_EXTENSIONS extensions= pop_triad( (chord>>4), triad >>4); //I need to pop the bits of the triad 
  
  char* strdeg= bits_deg_to_str(degree); 
  char* strtriad= bits_triad_to_str((triad>>4));

  fprintf(f, "%s%s", strdeg, strtriad);
  fprint_extensions(f,extensions);
}//works 


void print_chprog( S_CHPROG* prog){

    if(!( prog && prog->chprog)) return;
    LENGTH l=prog->length; 

    printf("[ ");
    for(CPT i=0; i<l-1; i++){
      print_ext_chord(prog->chprog[i]);
      printf(" ; ");
    }
    print_ext_chord(prog->chprog[l-1]); 
    printf(" ]\n");
}


void fprint_chord_prog( FILE* f, S_CHPROG* prog){

     if(!( prog && prog->chprog)) return;
    LENGTH l=prog->length; 

    fprintf(f,"[ ");
    for(CPT i=0; i<l-1; i++){
      fprint_ext_chord(f,prog->chprog[i]);
      fprintf(f," ; ");
    }
    print_ext_chord(prog->chprog[l-1]); 
    fprintf(f," ]\n");
}