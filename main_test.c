#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chordloop.h"
#include "globals.h"
#include "harmo.h"
#include "parseloop.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"
#include "scaleloop.h"
#include "init.h"
#include "user_info.h"
#include "chordgen.h"
#include "rand.h"
#include "misc.h"
#include "chordprint.h"
#include "parseloop.h"



#include <wchar.h>

int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  user_saved=malloc(sizeof(S_USERINFO));
  init_userinfo(user_saved);

  //CHORD_DEGREES chord= get_degrees(1370);
  //print_bits(chord);

  /*S_CHORD_PROG * ch= malloc(sizeof(S_CHORD_PROG));

  ch->chord_prog= malloc(3);
  ch->length= 3;

  ch->chord_prog[0]=0b00100000  ;
  ch->chord_prog[1]=0b00100111  ;
  ch->chord_prog[2]=0b00100101  ;*/


 //S_CHORD_PROG * ch1= generate_chord_prog(1370, 5);

 //CHORD ch= generate_chord(MIN_CHORD, 1);
  //print_bits(ch);

  //printf("%s\n", chord_to_str(ch));
  /*CHORD_DEGREES maj= get_degrees(1370);
  (maj);
  

  CHORD_DEGREES randeg= select_rand_degree(maj);


  DEGREES seldeg= get_deg_from_chdeg(randeg);
  print_bits(randeg);
  printf("%d\n", seldeg);
  print_bits(seldeg);
  */

  //printf("%d\n", ch1->length);
  //printf("%p\n", &(ch1->chord_prog[0]));

  //print_bits(ch1->chord_prog[0]);

  //printf("%p\n",chord_to_str(ch1->chord_prog[0]));

 //print_chord_prog(ch1);
  

  
  // print_chord_prog(ch);
  
 
  //free_chord_prog(ch1);

 /* for (int i=0; i<10; i++){
    S_SCALE scale = parse_scale("{ 0 3 6 7 }");
    //print_bits()
   // printf("%b\n", get_degrees(scale));
   // printf("%d",i );
   // print_scale(rot(scale , i));
    S_CHORD_PROG * chprog= generate_chord_prog(scale ,10);
   // print_scale(scale);
    print_chord_prog(chprog);
   // printf("\n");
  }*/
  // chordloop();
  // wchar_t str= L'\240';
  /*
  char * chord= "      IVm    ";
  

  CHORD ch= str_to_chord(chord);

  //printf("%b\n", ch);
  char * chord_str= chord_to_str(ch);

  if(chord_str){
  printf("%s\n", chord_str);
  }else printf("%p\n" ,chord_str);
   
   
  free(chord_str);*/

 /* char *str= "[II, V,I]";

  

  S_CHORD_PROG * chprog= str_to_chord_prog(str);

  print_chord_prog(chprog);

  S_CHORD_PROG * dup= duplicate_chprog(chprog);

  save_chprog(dup, user_saved);

  free_chord_prog(chprog);
  free_chord_prog(dup);*/

 // chordloop();

 parseloop();

  free_userinfo(user_saved);
 return 0;
}
