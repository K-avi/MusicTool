#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
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
  if( triads==1 || triads== 2 || triads== 4 || triads==8) {return  triads;} // case if only one triad

  LENGTH length=count_bits(triads);

  int select=rand()%length+1;
  
  CPT cpt=0, incr=0, ret=0;
  while(cpt < select && incr<8){
    if( 1 & (triads>>incr)) {  ret=incr; cpt++;}
    incr++;
  }
  return (1<<ret);
}

u_char t_in_scale_to_tchprog(TRIADS_IN_SCALE triad)//converts a triad in triads_in_scale format to 

void add_triad( TRIADS_IN_SCALE triads, TRIADS_IN_CHPROG chprog){//puts a chord in the first empty slot of a chprog
//an empty slot is represented by 4 bits set to 0.
//assumes that triads contains one chord and that chprog doesnt overflow

  u_char bits= *(u_char* )(chprog) & (15);
  CPT cpt=0;
  while ( bits){
    bits =  (*(u_char*)(chprog))&((15)<< (4*cpt));
  }
  

}




S_CHPROG_NEW * generate_chprog_new( S_SCALE scale, LENGTH length){

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

      unsigned size_alloc= length/2 ? length/2 : length/2+1; //savoir combien allouer ; 
      //vu que 1 accord = 4 bites ; si nb pair la moitie de la longueur de chprog, sinn la moitié +1 
      S_CHPROG_NEW * ret=malloc(sizeof(S_CHORD_PROG));
      DEGREES_IN_CHPROG degrees= malloc(size_alloc); 
      TRIADS_IN_CHPROG triads =malloc(size_alloc); 

      for( CPT i=0; i<length; i++){ 
        
        //ret_triads[i]=select_rand_chord(scl_triads[relev_degrees[0]]);
        //ret_degrees[i]=scl_degrees[relev_degrees[0]];
      }

      //set_chord_prog(ret, length, ret_triads, ret_degrees);
      free(scl_triads);
      free(scl_degrees);
      free(relev_degrees);
      return ret;
    } 


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
