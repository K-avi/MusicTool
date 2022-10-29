#include <stdlib.h>
#include <stdio.h>
#include "bitop.h"
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "init.h"
#include "misc.h"
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

    for (CPT i=1; i<12; i ++){
        if( scale & (1<<i)){
        rep[index++]=rot(scale, i+1);
        }
    }
   
    return rep;
}
//need to do the parsing function for modes
void print_modes(S_MODES modes){
    CPT i;
    for(i=0; i<get_length_kerni(modes[0]); i++){
        print_scale(modes[i]);
    }
}
/*CPT get_index_of_nth( S_SCALE scale, CPT n){
    //returns the "index" of the nth bit set in a scale 
    LENGTH length= get_length_kerni(scale);
    
    CPT bits_found=0;
    short last_bit_index=-1;
    CPT decalage=0;

    while(bits_found<n){
        if( GET_NTH(scale, decalage)) { bits_found++; last_bit_index=decalage;}
        decalage++;
    }
    return last_bit_index;
}

S_SCALE generate_nth_mode(S_SCALE scale, CPT n){//returns the nth mode of a scale. 
    if(n==0 || n==1) return scale;
    else if( n> get_length_kerni(scale)) {fprintf(stdout, "n is superior to the length of the scale");return scale;} 
    return rot(scale, get_index_of_nth(scale, n)-1);
}



S_SCALE rotate_right_scale(S_SCALE scale, CPT n) //harmonises a scale on the nth mode if n is 1;
//does so by right rotating the first 11 bits of the scale by n;
{
    //if(n>get_length_kerni(scale)){ printf("\n n too long\n"); return scale;}
   // if( !(1 <<n & scale)) {printf("\n triedc to harmo on a mode that doesnt start as a note\n");return scale;} 
    
    S_SCALE mask = 0x7FF; // Mask for lower 11 bits;
    S_SCALE flags= scale & (~mask); //preserve the flags 
    
    S_SCALE ret= ROTATE_RIGHT(scale, n, 16);

    ret|= (ret & (~mask) )>>6; //likely the issue
    ret&= mask;
    
    return ret|flags ;
}
S_SCALE rotate_right_scale_yohan( S_SCALE scale, CPT n){
      return (scale>>n)  | ((scale & ((1<<n))-1)) << (10-n)  | (scale & 0xF800);
}

S_SCALE rot1(S_SCALE scale, CPT n){
    S_SCALE head = scale & 63488;
    S_SCALE body = scale & 2047; 

    S_SCALE tail = scale & (( 1 << n) -1);
    S_SCALE zer= 2048; 

    printf("scale shift is %d\n tail is\n",n);
    print_bits(tail);
    printf("body is\n");
    print_bits(body);
    printf("\n:");

    return head | ((tail << 10 | zer |body )>>n);
}
*/