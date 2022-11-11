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


int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
   
  //TRIADS_IN_SCALE tri=triads_at_fund(236);
  //TRIADS_IN_SCALE tri= triads_at_fund(2047);

  TRIADS_IN_SCALE *triads_maj= get_triads( 1370);

 /* for( CPT i=0; i<7; i++){
    print_bits(triads_maj[i]);
    printf("\n");
  }*/

 // print_bits(tri);

 // printf("%d",tri);

 printf("%d %d %d %d", select_rand_chord(0xF),select_rand_chord(0xF),select_rand_chord(0xF),select_rand_chord(0xF));

 free(triads_maj);
  
  return 0;
}
