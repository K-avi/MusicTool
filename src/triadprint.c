#include "triadprint.h"
#include <stdlib.h>
#include <string.h>
#include "triadgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"
#include "triadprint.h"


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


char*  bits_triad_to_str( TRIADS_BITS triad){//pretty self expleanatory
    switch (triad) {
    case MIN: return "m";
    case MAJ: return "";
    case DIM: return "-";
    case AUG: return "+";
    case SUS2: return "sus2"; 
    case SUS4: return "sus4";
    default: { return NULL;}
    }
}


char *bits_deg_to_str(DEGREES_BITS deg){

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

char * chord_to_str(TRIAD chord){//turns a triad  into a string.

    if(!chord) return NULL;

    //uses a mask to separate first 4 and last 4 bits
    TRIAD first= chord & FIRST4; 
    TRIAD last= chord & LAST4;
    last= last>>4; //

  
    char* degree= bits_deg_to_str(first);
    char* triad= bits_triad_to_str(last);
    if( (!triad) || (!degree) ) return NULL;

  
    LENGTH len_deg=strlen(degree);
    LENGTH len_tri= strlen(triad);

    LENGTH len=  (len_deg+len_tri);
    char * ret= malloc( (len+1)*sizeof(char));
    

    for(int i=0; i<len_deg;i++){
        ret[i]=degree[i];
    }

    for(int j= len_deg; j<len_deg+len_tri; j++){
        ret[j]=triad[j-len_deg];
    }

    ret[len]='\0';
    return ret;
}

void print_triad_prog( S_TRIAD_PROG * chord_prog){
    if(!chord_prog) return;
    //if( !(chord_prog->degrees && chord_prog->triads && chord_prog->length==0)) return;
    char * curchord= NULL;
    printf("[ ");
    for(CPT i=0; i<chord_prog->length; i++){
        curchord =chord_to_str(chord_prog->chord_prog[i]);

        if(i!=chord_prog->length-1) printf("%s, ", curchord) ;
        else printf("%s", curchord) ;

        free(curchord);
    }
    printf(" ]\n");
}

void fprint_triad_prog(FILE* f , S_TRIAD_PROG * chord_prog){//same as print chprog but u can choose the buffer

    if(!chord_prog) return;
    if(f==NULL) return;

    char * curchord= NULL;
    fprintf(f,"[ ");
    for(CPT i=0; i<chord_prog->length; i++){
        curchord =chord_to_str(chord_prog->chord_prog[i]);

        if(i!=chord_prog->length-1) fprintf(f,"%s, ", curchord) ;
        else fprintf(f,"%s", curchord) ;

        free(curchord);
    }
    fprintf(f," ]\n");
}

