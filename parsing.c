#include "parsing.h"
#include "types.h"
#include "string.h"
#include "init.h"
#include "scalegen.h"
#include "user_info.h"
#include <stdio.h>
#include <stdlib.h>

extern LENGTH parse_scale_length(const char* string){

    char ret;
    while (string){
        if( *string>=48 && *string<=57 ){
            ret= atoi(string);
            break;
        }
        string ++;
    }
    if( ret >=0 && ret<=12) return ret; 
    return rand()%12;
}

char * set_to_beginning( char* str){
  //sets a str to the first iteration of '0'; returns a null string otherwhise.
  int i=0;
  while(str[i]!='0' && str[i]!='\0') i++;

  return &str[i];
}


S_SCALE parse_scale(char *string){
    S_SCALE ret= 0;
    NOTE note=0;
    int i=0;
    char *tmp= set_to_beginning(string);

    while(tmp){

        note= (*tmp% 32 + 9)%25;
        add_note(rep, note);
        tmp++;
    }

    free(tmp);
    return ret;
}

/*

S_SCALE * parse_scale( char *str){

  S_SCALE * rep=malloc(sizeof (S_SCALE));
  partial_init_scale(rep);

  if(strlen(str)>100){
      printf("\nstring parsed is too long, please try a shorter string\n");
      init_scale(rep);
      return rep;
  }
  NOTE note=0;
  int i=0;
  char *tmp= set_to_beginning(str);

  while(tmp[i]!='\0' && tmp[i]!='\n'){

    note= (tmp[i]% 32 + 9)%25;
    /*switch ((NOTE) tmp[i]){ //very messy; should change it tbh
        case 48: note= 0; break;
        case 49: note= 1; break;
        case 50: note= 2; break;
        case 51: note= 3; break;
        case 52: note= 4; break;
        case 53: note= 5; break;
        case 54: note= 6; break;
        case 55: note= 7; break;
        case 56: note= 8; break;
        case 57: note= 9; break;

        case 65: note= 10; break;
        case 66: note= 11; break;

        case 97: note= 10; break;
        case 98: note= 11; break;

        default: i++; continue;

    add_note(rep, note);
    i++;
  }
  sort_scale(rep);
  return rep;
}
*/