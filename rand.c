#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "triadgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"
#include "randext.h"
#include "misc.h"

#include <stdarg.h>





TRIADS_IN_SCALE select_rand_triads(TRIADS_IN_SCALE triads){//selects a random triads in a TRIADS_IN_SCALE struct
  
  if(!triads) return 0;
  if( triads==1 || triads== 2 || triads== 4 || triads==8 || triads==16 || triads== 32) {return  triads;} // case if only one triad

  LENGTH length=count_bits(triads);

  int select=rand()%length+1;
  
  CPT cpt=0, incr=0, ret=0;
  while(cpt < select && incr<8){
    if( 1 & (triads>>incr)) {  ret=incr; cpt++;}
    incr++;
  }
  return (1<<ret);
}//not tested 

PITCH_CLASS_SET select_rand_degree( PITCH_CLASS_SET deg){//selects ONE random degree in a PITCH_CLASS_SET short

  if(!deg) return 0;
  LENGTH length= count_bits(deg);
  if(length==1) return deg; 

  unsigned rand_deg= (rand()%(length))+1;
  
  return (1<<nth_bit_pos(deg, rand_deg));
}//tested




S_TRIAD_PROG* generate_chord_prog(S_SCALE scale, LENGTH length){ //generates a random chord prog of length length 


    print_scale(scale);
    if (!scale || !length) return NULL;
    PITCH_CLASS_SET deg_w_chord= get_degrees(scale);
    //_bits(deg_w_chord);
    

    if(!deg_w_chord ) return NULL;

    S_TRIAD_PROG* ret= malloc(sizeof(S_TRIAD_PROG));
    ret->length= length;
    ret->chord_prog= malloc(length* sizeof(TRIAD));

    if(count_bits(deg_w_chord)==1){ //case if u can only generate 1 chord from a scale 
      
      
      INDEX index= nth_bit_pos(deg_w_chord ,1); //retrieves the index of the relevent degree
      S_SCALE relev_mode= rot(scale, index);//retrieves the mode of said degree
    
      TRIADS_IN_SCALE triads= triads_at_fund(relev_mode);
      if(count_bits(triads)==1){
        for(CPT i=0; i<length; i++){

          TRIADS_IN_SCALE triad_selected= select_rand_triads(triads);//selects a random triad on the degree 
        
          ret->chord_prog[i]= generate_chord(triad_selected, deg_w_chord);
        }
      }else{

        TRIADS_IN_SCALE curtriads= select_rand_triads(triads);
        TRIADS_IN_SCALE prevtriads= curtriads;

        for(CPT i=0; i<length; i++){

          curtriads= select_rand_triads(triads);//selects a random triad on the degree 

          while(curtriads==prevtriads){
              
              curtriads=select_rand_triads(triads);
            }
            prevtriads=curtriads;

          ret->chord_prog[i]= generate_chord(curtriads, deg_w_chord);
        }
      }
      
    }else{//u can generate two or more chords

        PITCH_CLASS_SET curdeg= select_rand_degree(deg_w_chord);
        S_SCALE curmode = rot(scale , nth_bit_pos(curdeg, 1));//bad bc I calculate index multiple times
        //i should change the design so that i get an index that I use to get the triads n stuff
        TRIADS_IN_SCALE curtriads= triads_at_fund(curmode);
        TRIADS_IN_SCALE seltriads= select_rand_triads(curtriads);

        PITCH_CLASS_SET prevdeg=curdeg;

        for(CPT i=0; i<length; i++){

            
           //print_bits(deg_w_chord);
            curdeg=select_rand_degree(deg_w_chord);
            

            while(curdeg==prevdeg){
              
              curdeg=select_rand_degree(deg_w_chord);
            }
            prevdeg=curdeg;

            //printf("%b", curdeg);
            curmode=rot(scale , nth_bit_pos(curdeg, 1));

           // print_scale(curmode);
            curtriads=triads_at_fund(curmode);
            seltriads= select_rand_triads(curtriads);
           // print_bits(curtriads);
            
            ret->chord_prog[i]= generate_chord(seltriads, curdeg);
          
        }

    }

    return ret;
}//not done 
