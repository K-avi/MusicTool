#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "harmo.h"
#include "parseloop.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"
#include "init.h"
#include "user_info.h"
#include "chordgen.h"
#include "rand.h"
#include "misc.h"
#include "chordprint.h"
#include "parseloop.h"
#include "writeenv.h"
#include "syntaxcheck.h"



#include <wchar.h>



int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  user_data=malloc(sizeof(S_USERINFO));
  init_userinfo(user_data);
  

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


  //file_command_parseloop( "   examples/command_exp1.txt\n\n");

 // readparse("env examples/environment_ex1.txt", user_saved);

 // file_environment_parseloop("examples/environment_ex1.txt", user_saved);

  //print_saved_scale(user_saved, 4);
  /*print_saved_scale(user_saved, 2);
  print_saved_scale(user_saved, 3);

  printf("modes: \n");

  print_saved_modes(user_saved, 1);

  printf("chprog: \n");

  print_saved_prog(user_saved, 1); 
  print_saved_prog(user_saved, 2);
 //cmdline_parseloop();*/

  //print_env(user_saved);

  //fprint_env( stdout, user_saved);
 // write_env("test.txt", user_saved);

  //S_MODES m1= generate_modes(1370); 
 // S_MODES m2= generate_modes(1370);

 // printf("%d\n", equals_harmo(m1, m2));
  //S_CHORD_PROG *ch1= str_to_chord_prog("[I, IV,V]");
 // S_CHORD_PROG *ch2= str_to_chord_prog("[I, V,V]");

  //printf("%d\n", equals_chprog(ch1, ch2));

 // save_modes(m1, user_saved);
   //save_modes(m1, user_saved);
  //print_saved_modes(user_saved, 1);
  //print_modes(user_saved->saved_modes->next->modes);
  //modes_in_saved(m1, user_saved->saved_modes);
  //printf("%d\n",scale_comp_lexi(1370 , i[6]));

 // printf("%d\n", atoi("a12fpoezpojrojzj"));

  //printf("%b\n", parse_scale(" 4 3 2 1 0}"));
  //print_scale( parse_scale("{  0 44 4 3 2 1 } "));

  //printf("%d %d %d %d %d\n", printcheck(" 1 "), removecheck("10"), savescalecheck(" {0 2 4 5 7 9 11 }"), scalecheck("rnd"), scalecheck("rand 07 1"));
 // print_chord_prog(str_to_chord_prog("[I , IV, V]"));


  //printf("scheck1 : %d\n", syntaxcheck("scale save { 0 2 4 5 7 9 11 }\n"));
// printf("scheck2: %d\n", syntaxcheck("chprog rand\n"));

 // printf("scheck3: %d\n", syntaxcheck("read command zfekfekz "));


  //printf("%d", harmocheck(" save { 0 2 3 4 1 9 }"));

 // printf(" rez is : %d\n" ,two_num_args_check(" 1 5 "));
  
 //printf("test\n");
 //free_userinfo(user_data);

 //FILE *f = fopen("test.txt", "r"); 
    //int check= parenthesis_check(f);
//printf("%d\n", check);
 //fclose(f);

 //printf("%d\n", parse_scale(" { a 2 { 0 1 3 5 7 } \n { 0 2 3} \n"));

  //char * file= file_to_string("examples/environment_ex1.txt");

 // printf("%s\n", file);
 // SYNTAX_ERROR ttest= env_check(file);
  //printf("%d\n", ttest );
  //free(file);

  //file_environment_parseloop("examples/environment_ex1.txt   ", user_data );
  //file_command_parseloop("examples/command_ex1.txt", user_data);
  //int *i = malloc(100);
  //i[101]= 10;

  
  free_userinfo(user_data);
  return 0;

}
