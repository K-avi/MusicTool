
#include "scalegen.h"
#include "bitop.h"
#include "chordgen.h"
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

S_SCALE add_note_nopointer(S_SCALE scale, NOTE note){ //adds a note to a scale


    if(!IsValidNote(note)) return scale;

    if(!IsInScale(scale, note)){
        scale= SET_NTH(scale, (note-1)) ;
    }
    return scale;

}

S_SCALE add_rand_note_nopointer(S_SCALE scale){ //adds a random note to a scale

    if(scale >= FULLSCALE) return scale;
    else{
        NOTE note= rand()%12;
        while(IsInScale(scale,  note)){
            note=rand()%12;
        }
        return add_note_nopointer(scale, note);
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
    return rand()%0x7FF;
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



S_SCALE get_normal_scale(S_SCALE scale){
    LENGTH length=get_length_kerni(scale);
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

unsigned short inverse_bit (S_SCALE scale ){
    //returns the inverse of the first bit set in a scale; check out the definition of the inverse of 
    //an interval for more info
    if(!scale ) return scale; 
    CPT i=0;
    
    while(!(scale & ( 1<<i))){
        i++;
    }
    return (1<< (10-i));
}//tested 

S_SCALE get_inverse_scale(S_SCALE scale){//returns the inverse (I0) of a scale passed as argument.

    S_SCALE ret=0;  
    for(int i=0; i<12; i++){
        ret|= inverse_bit( (scale &(1<<i)));
    }
    return ret;
}//tested 


S_SCALE get_prime_scale(S_SCALE scale){//returns the prime of the scale passed as argument

    LENGTH length= get_length_kerni(scale);
    S_SCALE scl_norm= get_normal_scale(scale) ,scl_inv= get_inverse_scale(scl_norm);

    S_SCALE ret= (scale_comp_lexi(scl_norm, scl_inv)==1) ? scl_norm : scl_inv; 

    return ret;
}//works 

S_SCALE get_complementary_scale(S_SCALE scale){ //returns the complementary of a scale passed as argument AS A SCALE N NOT A PITCH CLASS!!!
    
    if(!scale ) return FULLSCALE;
    PITCH_CLASS_SET chdeg= (scale<<1) | 1; 
    chdeg^=4095; //bc 4095 is 12 bits set to one if I xor chdeg I get the bits of the compl scale

    return chdeg>>(nth_bit_pos(chdeg, 1)+1); 
}//works 

S_INTERVAL_STRUCTURE get_interval_struct(S_SCALE scale){
    //converts a scale to an interval struct 
    if(ERROR_FLAG & scale) return (long)INTERVAL_STRUCT_ERRFLAG;
    if(!scale) return 0;

    PITCH_CLASS_SET scale_deg = ( scale <<1 )| 1;
    LENGTH l= get_length_kerni(scale_deg);

    S_INTERVAL_STRUCTURE ret=0;

    unsigned char curbits, prevbits=nth_bit_pos(scale_deg, 1);
    
    INDEX shift=0; 

    for(CPT i=0; i<l; i++ ){
        curbits= nth_bit_pos(scale_deg, i+1); 
        ret|=(curbits-prevbits)<<(4*(shift));
        shift++;
        prevbits=curbits;
    }
    
    //printf("%d , %d \n,",nth_bit_pos(scale_deg, l) ,(4*l));
    ret= ret>>4;
    u_long lon= ((long)(12-nth_bit_pos(scale_deg, l))<<(4*(l-2)));
    ret|= lon; //no idea why this works but eh it does 
    return  ret;
} //tested and works

int length_intv_struct(S_INTERVAL_STRUCTURE intervals){
    //returns the length of an interval structure
    if(!intervals) return 1 ;
    if(intervals & INTERVAL_STRUCT_ERRFLAG) return 0;

    LENGTH l=0; 
    while( (intervals>>(4*l) & 15)){//15 is 1111
        l++;
    }
    return l;
}//works 



void  print_intv_struct(S_INTERVAL_STRUCTURE intervals){//prints an interval struct
    if(intervals & INTERVAL_STRUCT_ERRFLAG) return; 
    if(!intervals) {printf("[12\n]"); return;}
    printf("[ ");
    for (CPT i=0; i<length_intv_struct(intervals); i++){
        #ifndef WIN32
        printf("%lu " , (intervals>>(4*i)&15));
        #endif
        #ifdef WIN32
        printf("%llu " , (intervals>>(4*i)&15));
        #endif

    }
    printf("]\n");
    return ;
}//will be change to something cleaner at some point

PITCH_CLASS_SET rot_pcs( PITCH_CLASS_SET pcs, CPT n){//rotates the first 12 bits of a scale by n 

    if(n==0) return pcs;
    S_SCALE head = pcs & (61440);
    S_SCALE body = pcs & (4095); 

    S_SCALE tail = pcs & (( 1 >> (n-1)) -1);
   // S_SCALE zer= 1<< 12; 
   
    return (head | tail >> (12-n) | ( body) << n ) & (~ ERROR_FLAG_PCS);
}

S_SCALE move_note(S_SCALE scale, LENGTH length){//doesnt check for case where 
//popped-1 n popped+1 r already set; which might cause a problem down the line idk
   
    S_SCALE ret=scale;
    INDEX ran= rand()%length;
    INDEX popped =nth_bit_pos(ret,ran );
    ret=POP_BIT(ret,popped);

    //print_scale(ret);
    if(popped==11){ //really weird behavior tbh
        ret=SET_NTH(ret, 10);
               
    }else if (popped==0){ 
        ret=SET_NTH(ret, 1); 
               
    }else {
        //printf("in");
        ran= rand()%2; //choose wether to set 1 above or beneath
        if(ran==0){
            ret=SET_NTH(ret,  (popped+1));
        }else {
            ret=SET_NTH(ret, (popped-1));
                        
        }
    }
    return ret;
}

S_SCALE delete_nearby(S_SCALE scale, LENGTH length){
    if( (!scale) || (!length)){
        return ERROR_FLAG;
    }
    S_SCALE ret=scale;
    INDEX ran= rand()%length;
    INDEX popped =nth_bit_pos(ret,ran );
    ret=POP_BIT(ret,popped);
    return ret;
}

S_SCALE generate_nearby_scale (S_SCALE scale){//generates a nearby scale from the scale passed as arg ; 
//a nearby scale is a scale that has 1 more/less note than another scale or that has one of its notes moved up or down a semitone.
    LENGTH length=get_length_kerni(scale);
    if(!scale) return ERROR_FLAG;
    
    S_SCALE ret=scale;
    unsigned char ran=0;

    if(! (length==12 || length==1)){
        ran= rand()%3; 
        if(ran==0){//add note case
            return add_rand_note_nopointer(ret);

        }else if(ran==1){//delete note case
            ret=delete_nearby(ret,  length);

        }else{//move note case
            ret= move_note(ret,  length);

        }
    }else if(length==12){

        ran=rand()%2;

        if(ran==0){//delete note case
            ret=delete_nearby(scale,  length);
        }else if(ran==1){//move note case 
            ret= move_note(ret,  length);
        }

    }else if(length==1){
        ran =rand()%2; 

        if(ran==0){//add note case
            ret=add_rand_note_nopointer(ret);
        }else if(ran==1){//move note case
            ret=move_note(ret, length);
        }
    }

    return ret;
}//works

void print_intv_vect( S_INTERVAL_VECTOR vect){
    //printf("%b\n", vect);
    if(vect & INTV_VECT_ERRFLAG){ return ;}
    CPT  mask=0xF; 
    printf("< ");
    for(CPT i=0; i<6; i++){
        printf("%d ",  (vect >>(4*i)) &mask );
    }
    printf(" >\n");
}

S_INTERVAL_VECTOR add_partial_intv_vect(S_SCALE scale , S_INTERVAL_VECTOR vect){

    if(scale & ERROR_FLAG) return INTV_VECT_ERRFLAG;

    S_INTERVAL_VECTOR ret= vect;
 
    BITS mask= 0xF;
    BITS retrieved=0;
    for(CPT i=0; i<6; i++){
    
        if( scale & (1<<i)){
           
            retrieved = (ret & (mask << (4*i))) >> (4*i);
            retrieved +=1;

            ret= ret & ( ~(mask <<(4*i)));
            ret= ret | (retrieved << (4*i));
        }
    }
    return ret ;
}

S_INTERVAL_VECTOR generate_intv_vect(S_SCALE scale, LENGTH length){

    if(!(scale & length)) return 0;

    S_INTERVAL_VECTOR ret= 0; 
    S_MODES modes= generate_modes(scale); 

    for (CPT i=0; i<length; i++){
       
        ret=add_partial_intv_vect(modes[i],  ret);
    }
    free(modes);

    unsigned mask= 0xF00000;
    BITS retrieved= (ret & mask) >> 20;
    
    retrieved/=2;

    ret &= ~mask;
    ret|= retrieved <<20;
    return ret;
}

