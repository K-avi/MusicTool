#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "harmo.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"
#include "scaleloop.h"
#include "init.h"
#include "user_info.h"
#include "chordgen.h"
#include "chordprint.h"
#include "rand.h"
#include "chordprog.h"
#include "chordpattern.h"


int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
   
  //TRIADS_IN_SCALE tri=triads_at_fund(236);
  //TRIADS_IN_SCALE tri= triads_at_fund(2047);

 // TRIADS_IN_SCALE *triads_maj= get_triads( 1370);

 /* for( CPT i=0; i<7; i++){
    print_bits(triads_maj[i]);
    printf("\n");
  }*/

 // print_bits(tri);

 // printf("%d",tri);

 //printf("%d %d %d %d", select_rand_chord(0xF),select_rand_chord(0xF),select_rand_chord(0xF),select_rand_chord(0xF));

 //free(triads_maj);


 //CPT IIVV=contains_pattern(1370, 0x7FF);
  //printf("is the I IV V in maj scale? %d\n" ,IIVV);
// S_MODES modes=generate_modes(1371);

// TRIADS_IN_SCALE * triads= get_triads(1378);



 /*for(int i=0; i<7; i++){
  printf("%d ", degrees[i]);
 }*/

//printf("\n%d\n", chord_prog->length);
 /*for(int i=0 ; i<5; i++){
  printf("%d %d\n", chord_prog->degrees[i], chord_prog->triads[i]);
 }*/

 S_CHORD_PROG* chord_prog= generate_chord_prog(1371, 5);
 //init_chord_book( chord_book, &nb_entries);



 //printf("%d ", chord_book[0].length);
 //printf("%d ", chord_book[0].relev_deg);

 print_chord_prog(chord_prog);


 free_chord_prog(chord_prog);

 
 free(chord_book);
  
 return 0;
}
