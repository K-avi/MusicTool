#include <stdlib.h>
#include <stdio.h>
#include "chordgen.h"
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"
#include "rand.h"
#include "misc.h"
#include "chordprog.h"




TRIADS_IN_SCALE select_rand_chord(TRIADS_IN_SCALE triads){//selects a random triads in a scale
  
  if(!triads) return 0;
  if( triads==1 || triads== 2 || triads== 4 || triads==8) {return  triads;}

  LENGTH length=count_bits(triads);

  int select=rand()%length+1;
  
  CPT cpt=0, incr=0, ret=0;
  while(cpt < select && incr<8){
    if( 1 & (triads>>incr)) {  ret=incr; cpt++;}
    incr++;
  }
  return (1<<ret);
}

S_CHORD_PROG * generate_chord_prog(S_SCALE scale, LENGTH length){ //generates a random chord prog of length length 
//very convoluted; should get back to it and rewrite partially (maybe using associative array isnt a good solution)
    LENGTH scale_length= count_bits(scale); 
    
    TRIADS_IN_SCALE * scl_triads= get_triads_length(scale, scale_length);
 

    //checks that u can create at least one chord w the scale passed as argument
    CPT nb_relev_deg= nb_deg(scl_triads,  scale_length);

    if(nb_relev_deg==0) return NULL; //if u cant generate any triads

    DEGREES* relev_degrees= degrees_with_chords(scl_triads, scale_length, nb_relev_deg);//retrieves the degree w 
    //one chord or more on them

    if(nb_relev_deg==1){ //if u can only generate 1 chord from a scale

      DEGREES * scl_degrees= get_degrees_length(scale, scale_length);

        //initialises the differents fields of return values
      S_CHORD_PROG * ret=malloc(sizeof(S_CHORD_PROG));
      TRIADS_IN_SCALE * ret_triads= malloc(length*sizeof(TRIADS_IN_SCALE));
      DEGREES * ret_degrees= malloc(length*sizeof(DEGREES));

      for( CPT i=0; i<length; i++){ 
        
        ret_triads[i]=select_rand_chord(scl_triads[relev_degrees[0]]);
        ret_degrees[i]=scl_degrees[relev_degrees[0]];
      }

      set_chord_prog(ret, length, ret_triads, ret_degrees);
      free(scl_triads);
      free(scl_degrees);
      free(relev_degrees);
      return ret;
    } 
    
    else {
       
      DEGREES * scl_degrees= get_degrees_length(scale, scale_length);

      //initialises the differents fields of return values
      S_CHORD_PROG * ret=malloc(sizeof(S_CHORD_PROG));
      TRIADS_IN_SCALE * ret_triads= malloc(length*sizeof(TRIADS_IN_SCALE));
      DEGREES * ret_degrees= malloc(length*sizeof(DEGREES));

      CPT i=0;
      int ran=0;
      SIGNED_LENGTH last_deg_selected=-1;

      while(i<length){
          
          ran=rand()%nb_relev_deg;
          if(last_deg_selected==ran) { continue;} //checks that the same chord isnt selected twice in a row
          last_deg_selected=ran;
          ret_triads[i]=select_rand_chord(scl_triads[relev_degrees[ran]]);
          ret_degrees[i]=scl_degrees[relev_degrees[ran]];
          i++;
      }
      set_chord_prog(ret, length, ret_triads, ret_degrees);
      free(scl_triads);
      free(scl_degrees);
      free(relev_degrees);
      return ret;
  }
}
