#include "chordprint.h"
#include <stdlib.h>
#include <stdio.h>
#include "chordgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"


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
}//maybe tested


char*  triad_to_str( TRIADS_IN_SCALE triad){//pretty self expleanatory
    switch (triad) {
    case 1: return "m";
    case 2: return "";
    case 4: return "°";
    case 8: return "+";
    default: { return NULL;}
    }
}

char *deg_to_str(DEGREES deg){

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

void print_chord_prog( S_CHORD_PROG * chord_prog){
    if(!chord_prog) return;
    //if( !(chord_prog->degrees && chord_prog->triads && chord_prog->length==0)) return;

    printf("[ ");
    for(CPT i=0; i<chord_prog->length; i++){
        if(i!=chord_prog->length-1) printf("%s%s, ", deg_to_str(chord_prog->degrees[i]), triad_to_str(chord_prog->triads[i]) ) ;
        else printf("%s%s", deg_to_str(chord_prog->degrees[i]), triad_to_str(chord_prog->triads[i]) ) ;
    }
    printf(" ]\n");
}