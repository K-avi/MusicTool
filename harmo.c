#include <stdlib.h>
#include "bitop.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "init.h"
#include "scalegen.h"

void print_bits(S_SCALE x){  //might turn into a macro 
    int i;
    for(i=8*sizeof(x)-1; i>=0; i--) {
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

S_SCALE rot( S_SCALE scale, CPT n){//rotates the first 11 bits of a scale by n 

    if(n==0) return scale;
    S_SCALE head = scale & 63488;
    S_SCALE body = scale & 2047; 

    S_SCALE tail = scale & (( 1 << (n-1)) -1);
    S_SCALE zer= 1<< 11; 

    return head | tail << (12-n) | (zer | body) >> n;
}

S_MODES generate_modes( S_SCALE scale){ //generates and return all of the modes of a scale given this scale
    LENGTH length= get_length_kerni(scale);
    S_MODES rep=malloc(length*sizeof(S_SCALE));
    rep[0]=scale;
    CPT index=1;

    for (CPT i=0; i<12; i ++){
        if( scale & (1<<i)){
        rep[index++]=rot(scale, i+1);
        }
    }
    return rep;
}

void print_modes(S_MODES modes){
    if(!modes) return;
    CPT i;
    for(i=0; i<get_length_kerni(modes[0]); i++){
        print_scale(modes[i]);
    }
}

void fprint_modes( FILE *f, S_MODES modes){//same as print_modes but u choose the buffer
    if(!modes) return;
    CPT i;
    for(i=0; i<get_length_kerni(modes[0]); i++){
        fprint_scale(f,modes[i]);
    }
}

bool equals_harmo( S_MODES modes1, S_MODES modes2){//returns 1 if two modes are equals 0 otherwise 
//modes are considered equal if they contain the modes of the same scale even if said modes are in a different order 
//for example a S_MODES containing the modes of locrian scale n one containing those of the major scale are 
// considered EQUALS bc they contain the same scales, just in a different order.
    if ( !(modes1 && modes2)) return 0;

    S_SCALE scl1= get_normal_scale_modes(modes1, get_length_kerni(modes1[0]) ); 
    S_SCALE scl2= get_normal_scale_modes(modes2, get_length_kerni(modes2[0]));

    return EQUALS_SCALE(scl1, scl2);
}