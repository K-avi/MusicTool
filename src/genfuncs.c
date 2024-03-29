#include "triadprint.h"
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
#include <sys/types.h>
#include "harmo.h"
#include "triadgen.h"



bool generic_rand( char * str, char mode  ){
  /*
    generic randomisation function; handles operations of type : 
    f: str-> 'a rand -> 'a 
    f: str-> 'a rand int -> 'a 
    f: str-> 'a rand int int -> 'a 
    wanted to implement it w void* but kinda pointless atm ; might get back to it
  */
  
  if(mode == 's' || mode== 'h'){
    scl_length= parse_scale_length(str);
    if(scl_length==13) scl_length=rand()%12;
      
    tmp_saved_scale=generate_ran_scale(scl_length);

    if(mode=='h'){
      if(tmp_saved_mode) free(tmp_saved_mode);
      tmp_saved_mode=generate_modes(tmp_saved_scale);
    }

	  print_scale(tmp_saved_scale);
	  if(mode=='h')print_modes(tmp_saved_mode);
  }

  
  else if(mode =='d'){
    tmp_saved_dodec=shuffle_serie(HARMO_SERIE, 100);
    print_serie(tmp_saved_dodec);
  }
  return 1;
}

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
  function to represent a generic f: str -> scl -> scl -> stdout
  returns 1 or 2 depending on succes condition; and zero if failed
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
    }else{
      if(tmp_saved_scale){
        tmp_saved_scale=operation(tmp_saved_scale); 
        print_scale(tmp_saved_scale); 
        return 3;
      }
    }
    return 0;
}


u_char generic_dodec_dodec( S_DODEC (*operation)(S_DODEC serie), S_DODEC(*nth_operation)(S_DODEC serie, INDEX index), char*str, S_USERINFO*user_saved ){
  /*
  function representing fhe treatment all the function that behaves: 
  f : str -> S_DODEC -> S_DODEC -> stdout
  returns a positive integer when succes , 0 when fails
  */
  char * tmp=str; 
  while(NEUTRAL_CHAR(*tmp)) tmp++; 
  if(END_OF_LINE_CHAR(*tmp)){
    if(tmp_saved_dodec){
      tmp_saved_dodec=operation(tmp_saved_dodec); 
      print_serie(tmp_saved_dodec);

      return 1; 
    }else {
      printf("no serie saved in tmp; nothing will be done\n");
    }
  }else if (isdigit(*tmp)){
    indexx= atoi(tmp)%12;
    while (isdigit(*tmp)) tmp++;
    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(*tmp=='{'){
      tmp_saved_dodec=nth_operation(parse_serie(tmp),indexx);
      print_serie(tmp_saved_dodec);

      return 2; 
    }else if(!strncmp(tmp, "saved", 5)){
      tmp+=5; 
      while(NEUTRAL_CHAR(*tmp)) tmp++; 
      if(isdigit(*tmp)){
        index2=atoi(tmp);
        if(index2!=-1 && index2){
          generated_dodec=get_saved_dodec(user_saved, index2); 
          tmp_saved_dodec=nth_operation(generated_dodec, indexx);
          print_serie(tmp_saved_dodec);

          return 3;
        }
      }else {
        printf("runtime error in dodec fun i saved j\n");
      }
    }else if(END_OF_LINE_CHAR(*tmp)){
      if(tmp_saved_dodec){
        tmp_saved_dodec=nth_operation(tmp_saved_dodec, indexx); 
        print_serie(tmp_saved_dodec);

        return 4;
      }
    }else{
      printf("runtime error in dodec fun i ...\n");
    }
  }else if (!strncmp(tmp, "saved", 5)){
    tmp+=5;
    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(isdigit(*tmp)){
      indexx=atoi(tmp);
      if(indexx!=-1 && indexx){
        generated_dodec=get_saved_dodec(user_saved, indexx); 
        tmp_saved_dodec=operation(generated_dodec);
        print_serie(tmp_saved_dodec);

        return 5; 
      }
    }else {
      printf("runtime error in dodec fun saved\n");
    }
  }else if(*tmp=='{'){
    S_DODEC parsed_dodec= parse_serie(tmp);
   
    tmp_saved_dodec=operation(parsed_dodec);
    print_serie(tmp_saved_dodec);
  }else {
    printf("runtime error in dodec fun\n");
  }
  return 0;
}