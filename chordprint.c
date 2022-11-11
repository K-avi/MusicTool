#include "chordprint.h"
#include <stdlib.h>
#include <stdio.h>
#include "chordgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"


SIGNED_LENGTH map_index_to_note(S_SCALE scale, LENGTH index){
    /*the purpose of this function is to return which note corresponds to the nth degree of a scale. For example, if I say 1 it returns 1 bc its the fundamental.
    if I want the 2nd note I return the bit where the 1st note is +1 and so on */
    if(get_length(scale)<index) return -1;
    else if( index==1) return 1;
    else{
        CPT cpt=0, bit=0;
        while (cpt<index) {
            if( (1<<cpt) & scale) bit=cpt;
            cpt++;
        }
        return bit;
    }
}

char * get_deg(S_SCALE scale, LENGTH degree){ //returns the string corresponding to the nth note in the scale 
    if(get_length(scale)<degree) return "err1";
    if(!((1<<degree) & scale) ) return "err2";
    switch (degree) {
    case 1: return "I";
    case 2: return "bII";
    case 3: return "II";
    case 4: return "bIII";
    case 5: return "III";
    case 6: return "IV";
    case 7: return "bV";
    case 8: return "V";
    case 9: return "bVI";
    case 10: return "VI";
    case 11: return "bVII";
    case 12: return "VII";
    default: return "err3";
    }

}

char * get_triad_type(TRIADS_IN_SCALE triad){
    switch (triad) {
    case MAJ_CHORD: return "";
    case MIN_CHORD: return "m";
    case AUG_CHORD: return "+";
    case DIM_CHORD: return "°";
    default: return "err1";
    }
}