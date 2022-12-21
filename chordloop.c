#include "chordloop.h"
#include "chordprint.h"
#include "user_info.h"
#include "parsing.h"
#include "chordgen.h"
#include "rand.h"
#include "scalegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void chordloop(){

    
    printf("\n Welcome to Chord Mode, type 'help' for more informations\n");
    printf("  >>>");

    //overkill but usefull 
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[256];

    S_CHORD_PROG * tmp_chprog=NULL;
    SIGNED_LENGTH index=-1 , l1=-1, l2=-1;

    while (true){

      fflush(stdin);
      memset(&line[0], 0, 256*sizeof(char));

      fflush(stdout);
      if (!fgets(line, 256, stdin))	continue;

      if(strstr(line, "fullrand")){

        l1=parse_index(line);
        l2=parse_next(line);
        if(tmp_chprog) {
            free(tmp_chprog->chord_prog);
            free(tmp_chprog);
        }

        printf("%d, %d\n", l1, l2);
        if(l1==-1){
        
            tmp_chprog=generate_chord_prog(generate_ran_scale((rand()%4+7)), rand()%10+1);//generates rand chprog from scale between 7 and 12 length
        }else if(l2==-1){
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , rand()%10+1   );
        }else{
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , l2   );
        }
        
        if(!tmp_chprog) printf("couldn't generate a chord prog with given parameters; please try other ones\n");
        else print_chord_prog(tmp_chprog);
        printf("  >>>");
        continue;

      } else if (strstr(line, "help")!=NULL)	{

        printf("\ntype 'quit' to exit Chord Mode \n");
        printf("\ntype 'exit' to exit MusicTool \n");
        printf("\ntype 'coherand x y' to generate a chord prog of length x using a scale of length y using a book of prebuilt chordprogs\n");
        printf("\ntype 'coherand x' to generate a chord prog of length x using a scale of rand length using a book of prebuilt chordprogs\n");
        printf("\ntype 'fullrand x y' to generate a chord prog of length x using a scale of length y\n");
        printf("\ntype 'fullrand x' to generate a chord prog of length x using a scale of a random length\n");
        printf("\ntype 'fullrand' to generate a chord prog of a random length from a scale of random length \n");
        printf("\ntype 'save [ I, IIm, .... ]' to save the chprog you passed after it if  save scale is called without argument, the last generated scale will be saved\n");
        printf("\ntype 'print saved chprog n' to print the nth chprog you saved\n");
        printf("\ntype 'remove chprog n' to remove the chprog saved at index n\n");
        printf("\ntype 'extract scale n' to extract the scale from the chprog saved at index n\n");
        printf("\ntype 'extract scale [I......]' to extract the scale from the chprog passed as argument\n");

        printf("  >>>");
        continue;
      } else if(strstr(line, "quit")!=NULL)	{

          free(tmp_chprog->chord_prog);
          free(tmp_chprog);

          printf("\nYou have exited Chord Mode\n");
          printf("  >>>");
        break;
      }else if(strstr(line, "exit")!=NULL)	{
          
          free(tmp_chprog->chord_prog);
          free(tmp_chprog);

          printf("\nYou have exited MusicTool\n");
          exit(0);

      } else {
        printf("syntax error\n");
        printf("  >>>");
      }
    }
}
