
#include "scalegen.h"
#include "bitop.h"
#include "harmo.h"
#include "types.h"
#include "misc.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>


bool IsValidNote( NOTE note){ //checks wether a note is valid or not (valid meaning that it's value is between 0 and 11
    return (note >=1 && note <=11);
}

bool IsInScale( S_SCALE scale, NOTE note){ //asserts wether a note is already in a scale or not

    if (note==0) return true; 
    else return ( GET_NTH(scale, (note-1) ));

}

void add_note(S_SCALE* scale, NOTE note){ //adds a note to a scale


    if(!IsValidNote(note)) return;

    if(!IsInScale(*scale, note)){
        *scale= SET_NTH(*scale, (note-1)) ;
    }

}

void add_rand_note(S_SCALE* scale){ //adds a random note to a scale

    if(*scale >= FULLSCALE) return;
    else{
        NOTE note= rand()%12;
        while(IsInScale(*scale,  note)){
            note=rand()%12;
        }
        add_note(scale, note);
    }

}



LENGTH get_length( S_SCALE scale){//takes  flags into account
    
    if(scale==0 || scale <<5==0) return 1;
    else{
        LENGTH n=0;

        for(CPT i=0; i<11; i++){
            if( GET_NTH(scale, i)) n++;
        }
        return n+1;
    }
}

LENGTH get_length_kerni( S_SCALE scale){ //doesnt 
    if(scale==0 || scale <<5==0) return 1;
    else{
        LENGTH cnt=0; 
        while(scale!=0){
            cnt++;
            scale=scale & scale-1;
        }
        return cnt+1;
    }      
}


S_SCALE generate_ran_scale(LENGTH length){ //generates a random scale of 'length' notes

    S_SCALE  ret=0;
    int i;
    length=length%13;
    for(i=0; i<length-1; i++){
        add_rand_note(&ret);
    }
   return ret;
}

S_SCALE gen_ran_scale_var(){ //generates a random scale of a random length between 1 and 12
    return random()%MAXLENGTH;
}


void set_scale(S_SCALE* scale, NOTE* array, LENGTH length ){//sets a scale to the values of an array; 
    //maybe useless
    for(CPT i=0; i<length; i++){
        add_note(scale, array[i]);
    }
}

S_SCALE * make_scale( NOTE *array, LENGTH length){ //generates a scale from an array + a length passed as argument

    S_SCALE* ret = malloc(sizeof(S_SCALE));
    set_scale(ret, array, length);
    return ret;
}

void print_scale( const S_SCALE scale){ //prints the notes of a scale and it's length in a nice way :)
    int i;
    if(ERROR_FLAG & scale ) return;
    printf("\n{ 0 ");
    for(CPT i=0; i<11; i++){
        if(GET_NTH(scale, i)) printf("%d ", i+1);
    }

    printf("}\n");
}

void fprint_scale( FILE* f,const S_SCALE scale ){//same as print scale but u can choose the buffer where scale is printed 

    int i;
    fprintf(f,"\n{ 0 ");
    for(CPT i=0; i<11; i++){
        if(GET_NTH(scale, i)) fprintf(f,"%d ", i+1);
    }

    fprintf(f,"}\n");
}

SIGNED_BOOL scale_comp_lexi( S_SCALE scl1, S_SCALE scl2){//returns 0 if two scales are equal ; 1 if scl2>scl1 in lexicographic order, -1 if scl1>scl2

    if(scl1==scl2) return 0;
    if(!scl1) return 1;
    if(!scl2) return -1;

    LENGTH lscl1= count_bits(scl1), lscl2= count_bits(scl2);
    
    CPT it_max= (scl1>=scl2) ?scl2 : scl1;
    
    for(CPT i=0; i<it_max; i++){

      
        if( (scl1 & (1<<i)) && !(scl2&(1<<i))  ){
            return 1;
        }else if( !(scl1 & (1<<i)) && (scl2&(1<<i)) ){
            return -1;
        }
    }
    SIGNED_BOOL ret = (it_max==lscl1) ? 1 : -1;

    return ret;

}



S_SCALE get_normal_scale(S_SCALE scale, LENGTH length){
    S_MODES modes= generate_modes(scale);
    S_SCALE ret= scale;
    for(INDEX i=0; i<length; i++){
        if(scale_comp_lexi(ret, modes[i])==1) ret=modes[i];
    }
    free(modes);
    return ret;
}

S_SCALE get_normal_scale_modes(S_MODES modes, LENGTH length){//same as get normal scale w/o calculating the modes.
    if(!modes ) return ERROR_FLAG;
    S_SCALE ret= modes[0];
    for(INDEX i=0; i<length; i++){
        if(scale_comp_lexi(ret, modes[i])==1) ret=modes[i];
    }
    return ret;
}

S_SCALE get_inverse_scale(S_SCALE scale, LENGTH length){//returns the inverse (I0) of a scale passed as argument.
    INDEX i = nth_bit_pos(scale,length-1); 
    return rot(scale, i+1);
}


S_SCALE get_prime_scale(S_SCALE scale, LENGTH length){//returns the prime of the scale passed as argument

    S_SCALE scl_norm= get_normal_scale(scale,  length) ,scl_inv= get_inverse_scale(scl_norm,  length);

    S_SCALE ret= (scale_comp_lexi(scl_norm, scl_inv)==1) ? scl_norm : scl_inv; 

    return ret;
}

S_SCALE get_complementary_scale(S_SCALE scale){ //returns the complementary of a scale passed as argument AS A SCALE N NOT A PITCH CLASS!!!
    
    if(!scale ) return FULLSCALE;
    CHORD_DEGREES chdeg= (scale<<1) | 1; 
    chdeg^=4095; //bc 4095 is 12 bits set to one if I xor chdeg I get the bits of the compl scale

    return chdeg>>(nth_bit_pos(chdeg, 1)+1); 
}