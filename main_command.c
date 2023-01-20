#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "scalegen.h"
#include "types.h"
#include "init.h"
#include "parseloop.h"
#include "harmo.h"
#include "parsing.h"
#include "user_info.h"
#include "globals.h"
#include "chordgen.h"




int main( int argc, char *argv[])
{
  
  if(argc!=3){
     printf("to use smtool pass two args\n");
  }
  else{
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    //initialises the user saved info structure
    user_data=malloc(sizeof(S_USERINFO));
    init_userinfo(user_data);

    SYNTAX_ERROR err =parse_command( argv, user_data);

    if(err!=0){
      char * err_msg= syntax_error_flag_to_str(err);
      printf("%s\n", err_msg);
    }
    free_userinfo(user_data);
  }
  return 0;
}
