#include "chordprint.h"
#include "dodecseries.h"
#include "parsing.h"
#include "globals.h"
#include "bitop.h"
#include "rand.h"
#include "scalegen.h"
#include "types.h"
#include "user_info.h"
#include "genfuncs.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "harmo.h"
#include "chordgen.h"



bool generic_rand( char * str, char mode  ){

  
  if(mode == 's' || mode== 'h'){
    length= parse_scale_length(str);
    if(length==13) length=rand()%12;
      
    tmp_saved_scale=generate_ran_scale(length);

    if(mode=='h'){
      if(tmp_saved_mode) free(tmp_saved_mode);
      tmp_saved_mode=generate_modes(tmp_saved_scale);
    }

	  print_scale(tmp_saved_scale);
	  if(mode=='h')print_modes(tmp_saved_mode);
  }

  else if(mode =='c'){
    l1=parse_index(str);
    l2=parse_next(str);
      
    free_chord_prog(tmp_chprog);
     
    if(l1==-1){
        
        tmp_chprog=generate_chord_prog(generate_ran_scale((rand()%4+7)), rand()%10+1);//generates rand chprog from scale between 7 and 12 length
    }else if(l2==-1){
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , rand()%10+1   );
    }else{
            tmp_chprog=generate_chord_prog(generate_ran_scale(l1) , l2   );
    }
        
    if(!tmp_chprog) printf("couldn't generate a chord prog with given parameters; please try other ones\n");
    else print_chord_prog(tmp_chprog);
  }
  else if(mode =='d'){
    tmp_saved_dodec=shuffle_serie(HARMO_SERIE, 100);
    print_serie(tmp_saved_dodec);
  }
  return 1;

}//not yet 

u_char generic_print_uinfo (void (*print_uinfo)(S_USERINFO* uinfo, LENGTH index), void (*print_env)( S_USERINFO* uinfo),char*str, S_USERINFO*usaved ){
  /*
  str -> print 'a uinfo
  */
  char * tmp=str;
  while(NEUTRAL_CHAR(*tmp)) tmp++;
  if(isdigit(*tmp)){
      indexx=parse_index(tmp);
      if(indexx==-1) printf("index not recognised; nothing will be printed, please pass an integer from 1 to the number of objects saved\n");
      else{print_uinfo(usaved, indexx);}
      return 1;

  }else if(!strncmp(tmp, "env", 3)){
            print_env(usaved);
            return 2;
  }else printf("runtime error in print\n");
  return 0;
}

u_char generic_remove (void  (* remove)(S_USERINFO* uinfo, INDEX index), char* str, S_USERINFO*uinfo){
  /*
  function to represent 
  str -> rm 'a uinfo 
  */
  
  char * tmp=str;
  while(NEUTRAL_CHAR(*tmp)) tmp++;
  if(isdigit(*tmp)){
      indexx=parse_index(tmp);
      if(indexx==-1) printf("index not recognised; nothing will be removed, please pass an integer from 1 to the number of objects saved\n");
      else{remove(uinfo, indexx);}
      return 1;
  }
  return 0;
}

u_char generic_scl_scl( S_SCALE (*operation)(S_SCALE scl),char* str, S_USERINFO*uinfo ){
  /*
  function to represent a generic f: str -> scl -> scl function 
  */
   char * tmp=str;
   S_SCALE generated_scl=0;
   while (NEUTRAL_CHAR(*tmp)) {
          tmp++;
    }
    if(*tmp=='{'){
          //printf("%s\n", &line[i]);
      generated_scl=parse_scale(tmp);    
      if( ! (generated_scl&ERROR_FLAG)){
        tmp_saved_scale=operation(generated_scl);   
        print_scale(tmp_saved_scale);
        return 1;
      }else{
        printf("please parse a valid scale\n");
      }
    }else if(!strncmp(tmp, "saved", 5)){
          tmp+=5;
          while(NEUTRAL_CHAR(*tmp)){
            tmp++;
          }
          indexx=parse_index(tmp);
          if(indexx!=-1){
            generated_scl=get_saved_scale(uinfo, indexx); 
            if( !( generated_scl & ERROR_FLAG)){
              tmp_saved_scale=operation(generated_scl);
              print_scale(tmp_saved_scale);
              return 2;
            }else{
              printf("runtime error while doing scale operation\n");
            }
          }
    }
    return 0;
}

void generic_save( void (*save)(void* element, S_USERINFO *user_info) ,   char*str){

}