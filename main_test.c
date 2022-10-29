#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "harmo.h"
#include "scalegen.h"
#include "types.h"
#include "bitop.h"



int main(){

     time_t t;
     srand((unsigned) time(&t));


    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    /*
    unsigned short a=0;

    add_note(&a, 1);
    add_rand_note(&a);
    add_rand_note(&a);
    add_rand_note(&a);

  //  S_SCALE *test= generate_ran_scale(5);

  //  S_SCALE *test1= malloc((sizeof(S_SCALE)));
 // NOTE maj_scale[7]= {0,2,4,5,7,9,11};
  // set_scale(test1, maj_scale , 7);

   // print_scale(*test1);
   // printf("%d", *test1);
    //print_bits(*test1);
    
  
   */

    S_SCALE full = FULLSCALE;

    
   
    S_SCALE test2= 1370;

    /*
    S_SCALE plz_dorian= rot(test2, 2);
    S_SCALE plz_phrygian= rot(test2, 4);
    S_SCALE plz_lydian= rot(test2, 5);

    S_SCALE plz_mixolydian= rot(test2, 7);
    S_SCALE plz_eolian= rot(test2, 9);
    S_SCALE plz_locrian= rot(test2, 11);

    printf("dorian is: \n");
    
    print_scale(plz_dorian); 
    printf("\nand it's bitwise rep is:\n");
    print_bits(plz_dorian);

    printf("phrygian is: \n");   
    print_scale(plz_phrygian); 
    printf("\nand it's bitwise rep is:\n");
    print_bits(plz_phrygian);  


    print_scale(plz_lydian); 
     printf("\nand it's bitwise rep is:\n");
    print_bits(plz_lydian);

    printf("\nmixolydian is:\n");
    print_scale(plz_mixolydian);
    printf("and its bitwise rep is;\n");
    print_bits(plz_mixolydian);

    printf("\neolian is\n");
    print_scale(plz_eolian);
    printf("\nand its bitwise rep is\n");
    print_bits(plz_eolian);

    printf("\nlocrian is\n");
    print_scale(plz_locrian);
    printf("\nand its bitwise rep is\n");
    print_bits(plz_locrian);
  */
    //printf("\n%d  is the nth index of the 1 in the scale\n", get_index_of_nth(test2, 1));

   S_MODES eccle= generate_modes(test2);
   print_modes(eccle);

   
    return 0;
}
