#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "dodecseries.h"
#include "chordgen.h"
#include "globals.h"
#include "harmo.h"
#include "parseloop.h"
#include "parsing.h"
#include "progbook.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"
#include "init.h"
#include "user_info.h"
#include "triadgen.h"
#include "rand.h"
#include "misc.h"
#include "triadprint.h"
#include "parseloop.h"
#include "writeenv.h"
#include "syntaxcheck.h"
#include "dodecseries.h"

#include "chordprint.h"
#include "rand.h"
#include "progbook.h"

#include "coherand.h"

#include <string.h>

int main(){

  time_t t;
  srand((unsigned) time(&t));

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);




 /* char *str= "[II, V,I]";

  

  S_CHORD_PROG * chprog= str_to_chord_prog(str);

  print_chord_prog(chprog);

  S_CHORD_PROG * dup= duplicate_chprog(chprog);

  save_chprog(dup, user_saved);

  free_chord_prog(chprog);
  free_chord_prog(dup);*/

 // chordloop();


  //file_command_parseloop( "   examples/command_exp1.txt\n\n");
//heheg
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

 // S_CHORD_PROG* chprog= str_to_chord_prog("[II, V, I]");
 // PITCH_CLASS_SET pcs= (chprog_to_pcs(chprog));

 //free_chord_prog(chprog);


 
  //PITCH_CLASS_SET pcsmaj= MAJOR_PCS<<7;
//print_pcs(pcs);
 //print_pcs(pcsmaj); 
  //print_pcs(2741);
 
 /* for (int i =0; i<14; i++){
    printf("%d\n", i);
    if((2741 & (1 <<i))){
    print_bits(rot_pcs(2741,i));

    print_pcs(rot_pcs(2741,i ));
    }
    
  }*/
  
 //print_scale( scl);
 

//  S_INTERVAL_STRUCTURE intv= 0b00000001001000100010000100100010;
 // printf("%lu\n", get_interval_struct(scl));
 // print_bits(get_interval_struct(scl));
 // printf("%d\n",length_intv_struct(intv));
 // printf("%d\n", length_intv_struct(intv));
 // print_intv_struct(intv); 

  //print_intv_struct(get_interval_struct(scl));
 /*S_SCALE scl= parse_scale("{ 0 2 4 5 7 9 11}");

  S_INTERVAL_VECTOR vect= generate_intv_vect(scl, 7);
  print_intv_vect(vect);*/

 //print_scale(get_complementary_scale(scl));

 /*for (int i =0; i<10; i++){
  print_scale(generate_nearby_scale(scl, get_length_kerni(scl)));
 }*/
   //S_INTERVAL_STRUCTURE intv1= get_interval_struct(scl);
 //print_intv_struct(intv1);
  //print_scale(  get_inverse_scale(scl, 7));
  //print_scale (get_complementary_scale(scl));
  //save_scale(scl, user_data);
  //scaleparse("invert saved 1", user_data);

  //printf("%lu\n", (long)1<<48);

  /*S_DODEC dodec= INIT_DODEC;
  print_serie(dodec);
  dodec= add_to_dodec(dodec, 10);
  dodec= add_to_dodec(dodec, 1);
  dodec= add_to_dodec(dodec, 4);
  dodec= add_to_dodec(dodec, 4);*/
  //printf("%b\n", dodec);
 // print_serie(dodec);
 // print_serie( dodec);

 // printf("%d\n", isvalid_serie(HARMO_SERIE));
  //printf("%d\n", note_in_dodec(HARMO_SERIE , 10));
  

  //print_serie(HARMO_SERIE);
  
 // S_DODEC randodec= generate_serie() ;
 // print_serie(randodec); 
  //print_serie ( shuffle_once(HARMO_SERIE , 0, 11));
 // print_serie( shuffle_serie( HARMO_SERIE,  100));

  //print_serie(retrograde_serie(HARMO_SERIE));
  //print_serie(inverse_serie(HARMO_SERIE));

/*  S_DODEC harmogenplz=INIT_DODEC;
  for (int i=0; i<12; i++){
    harmogenplz= add_to_dodec(harmogenplz, i);
    
  }*/
 // print_serie(harmogenplz);
 // print_serie(generate_serie());
 // free_userinfo(user_data);
  //S_DODEC serie= shuffle_serie(HARMO_SERIE, 200);
 // print_serie(serie);
    
 // print_serie(serie); 
  //print_serie(inverse_serie(serie));
//  S_DODEC * mat= serie_to_12tmat(serie);
 // print_12t_mat(mat);
 // free(mat);
 //printf("a");f
  //printf("b");
  //fprintf(stderr, "vc");

  /*for(int i=0 ; i<10; i++){
    print_scale(gen_ran_scale_var());
  }*/

 /* SYNTAX_ERROR savet1= dodeccheck("save { 0 1 2 3 4 5 6 7 8 9 10 11}");
 // printf("%d\n" , savet1);
  SYNTAX_ERROR savet2= dodeccheck("save");
  //printf("%d\n" , savet2);

  SYNTAX_ERROR randt1= dodeccheck("rand");

  SYNTAX_ERROR funct1= dodeccheck("invert ");
  SYNTAX_ERROR funct2= dodeccheck(" retro saved 3");
  SYNTAX_ERROR funct3= dodeccheck(" comp 5 saved 4");
  SYNTAX_ERROR funct4= dodeccheck(" retroinv 8");

  printf("savet1: %d savet2: %d randt: %d\nfunc1: %d func2: %d func3: %d func4: %d\n", savet1, savet2, randt1, funct1, funct2, funct3,funct4);
*/

 // print_scale (1370);
  //char * str= extensions_to_str(1370);
 // printf("%s\n", str);
   // print_extensions(1370);
   // print_ext_chord((1370<<4| 3 ));
   // printf("\n");
   //print_extensions(1370);
  
  //free(str);

 // S_CHPROG* prog= generate_chprog(1, "-scl={0 3 4 7}");
 // printf(" %p ", prog);

  //ext_print_chprog(prog);
 // if(prog){
  //  if(prog->chprog){
  //    free(prog->chprog);
  //  }
  //  free(prog); 
  //}
  //int b=1;
  /*char *str ="  -length=3 -scllen=7 -extnum=1" ;
 
  S_CHPROG *aaa= generate_chprog(str);
  fprint_chord_prog(stdout,aaa);
  
 // ext_print_chprog(aaa);
 // prog->length=1; 
 // prog->chord_prog=&aaaa;
 // print_triad_prog(prog);
  if(aaa) {
    if(aaa->chprog)free(aaa->chprog); 
    free(aaa);
  }*/


 /*S_TRIAD_PROG* t_prog= generate_triad_prog("-scllen=2 -length=4 ");
  SYNTAX_ERROR check = prog_triad_randcheck( "-scllen=2 -length=4", 't');
  printf("%d is check\n", check);
  print_triad_prog(t_prog);

  free_triad_prog(t_prog);*/

 /* printf("error is : %d\n", error_catch);
  pbook->nbentries=40;

  for (CPT i=0; i<40; i++){
    pbook->book[i]=i;
   
  }

  int a= realloc_book(pbook);
  printf("a is %d\n", a);

  
  for (CPT i=0; i<20; i++){
    pbook->book[40+i]=40+i; 
    pbook->nbentries++;
  }
  printf("max entry is: %d\n", pbook->maxentries);
   for(CPT i=0; i<pbook->nbentries; i++){
    printf("%llu\n", pbook->book[i]);
  }*/


  PROGBOOK *pbook= malloc(sizeof(PROGBOOK));
 
  init_book(pbook, _book_init_small);
  

  S_CHPROG* prog= str_to_chprog(" [ I; IV; V; bII; II; bVII; VII ; I ; bIII ; III; II; IV; I]");
  S_CHPROG* prog1 = str_to_chprog( "[ I; IV; V ]");
  S_CHPROG* prog2 = str_to_chprog( "[ I ]");

  S_CHPROG* prog3 = str_to_chprog( "[ IV ]");
  S_CHPROG* prog4 = str_to_chprog( "[ V ]");
   S_CHPROG* prog5 = str_to_chprog( "[ I ;V ]");
    S_CHPROG* prog6 = str_to_chprog( "[ I ; IV ]");
     S_CHPROG* prog7 = str_to_chprog( "[ I; II; V ]");

  BOOKENTRY entry= chprog_to_bookentry(prog);
  BOOKENTRY entry1= chprog_to_bookentry(prog1);
  BOOKENTRY entry2= chprog_to_bookentry(prog2);

   BOOKENTRY entry3= chprog_to_bookentry(prog3);
  BOOKENTRY entry4= chprog_to_bookentry(prog4);

   BOOKENTRY entry5= chprog_to_bookentry(prog5);
    BOOKENTRY entry6= chprog_to_bookentry(prog6);
     BOOKENTRY entry7= chprog_to_bookentry(prog7);

  
  add_entry(pbook, entry);
 
  add_entry(pbook, entry1);
  add_entry(pbook, entry2);
 add_entry(pbook, entry2);
 add_entry(pbook, entry3);
  add_entry(pbook, entry4);
  add_entry(pbook, entry5);
  add_entry(pbook, entry6);
  add_entry(pbook, entry7);
   
  

//  print_progbook(pbook);
 


  BOOK_LENGTH_TABLE *table= progbook_constrained_to_book_length(pbook, 2741 );

  S_DEGREE_PROG* deg_pr= build_deg_prog_from_deg_array(table, 5);

  S_TRIAD_PROG* t_prog= degree_prog_to_triad_prog(deg_pr, 1370 );
  //printf("%d\n", parse_scale("{0 4  7 }"));
  S_CHPROG* ch_prog = degree_prog_to_chprog( deg_pr,  1370);

 // print_chprog(ch_prog);
 // ch_prog->chprog[0]=pop_extensions(ch_prog->chprog[0], 2);

  
  pop_prog_extensions(ch_prog, 2);
  //pop_prog_extensions_rand(ch_prog);
  //print_triad_prog(t_prog);
  free_triad_prog(t_prog);

  print_chprog(ch_prog);
  free_chord_prog(ch_prog);
 /* for(int i=0;i<12;i++){
    printf("%p\n", table->book_arrays[i]);
  }*/
  //printf(" %d\n",  pbook->nbentries);
  //print_book_entry( pbook->book[0]);
  //print_book_entry( pbook->book[1]);
  //print_progbook(pbook);
 // print_book_lengthtable(table);

 // print_degree_prog(deg_pr);

  free(deg_pr->degree_prog); 
  free(deg_pr);

  free_book(pbook);
  free_chord_prog(prog);
  free_chord_prog(prog1);
  free_chord_prog(prog2);
  free_chord_prog(prog3);
  free_chord_prog(prog4);
  free_chord_prog(prog5);
  free_chord_prog(prog6);
  free_chord_prog(prog7);
  free_book_table(table);
  return 0;

}
