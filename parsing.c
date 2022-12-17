#include "parsing.h"
#include "types.h"
#include "string.h"
#include "init.h"
#include "scalegen.h"
#include "user_info.h"
#include <stdio.h>
#include <stdlib.h>

LENGTH parse_scale_length(const char* string){//returns the length of a scale if a char between 0 and 9 is 
//in a string and 13 otherwise

    LENGTH ret=13;
    while (*string!='\n' && string && *string!='\0'){
        
        if( *string>='1' && *string<='9' ){
            ret= atoi(string);
            break;
        }
        string ++;
    }
    return ret; 
}

SIGNED_LENGTH parse_index(const char* string){//parses the index to print a scale/mode

    SIGNED_LENGTH ret=-1;
    while (*string!='\n' && string && *string!='\0'){
        
        if( *string>='1' && *string<='9' ){
            ret= atoi(string);
            break;
        }
        string ++;
    }
    return ret;

}
SIGNED_LENGTH parse_next(const char* string){//returns atoi of the second number in a string; -1 otherwise
    SIGNED_LENGTH ret=-1;
    CPT cpt=0;
    while (*string!='\n' && string && *string!='\0'){
        if( *string>='1' && *string<='9' && cpt){
            ret= atoi(string);
            break;
        }
        else if( *string>='1' && *string<='9' ){
            cpt=1;
        }
        string ++;
    }
    return ret;
}

char * set_to_beginning( char* str){//sets a str to the first iteration of '0'; returns a null string otherwhise.
  int i=0;
  while(str[i]!='0' && str[i]!='\0' && str[i]!='\n') i++;

  if(str[i]=='0') return &str[i];
  return NULL;
}

S_SCALE parse_scale(char *string){ //parses a scale; returns null scale if no scale is found
    if(string==NULL) return 0;
    S_SCALE ret=0;
    NOTE note=0;
    char *tmp= set_to_beginning(string);

    while(*tmp!='}' && tmp!=NULL){
        
        if(*tmp>='1' && *tmp<='9'){ 
            note=atoi(tmp)%12;
            add_note(&ret, note);
            if(note >9) tmp++; //avoids problem with 10 or eleven
        }
        tmp++;
    }  
    return ret;
}


/*
char* set_to_beginning_chprog(char* str){//sets to the first iteration of a '[' in a string
  if(!str) return NULL;
  
  char* tmp= strstr(str,"[");
   
  return tmp;
  
}

S_CHORD_PROG* parse_chprog(char* string){
    if(!string) return NULL;

    char*tmp= set_to_beginning_chprog(string);
    CPT i=0, nb_accords=0;

    while(tmp[i]!='\0' && tmp[i]!= ']'){
        if(tmp[i++]==',') nb_accords++;
    }

    S_CHORD_PROG *ret=malloc(sizeof(S_CHORD_PROG));
    
    ret->length= nb_accords;
    ret->degrees= malloc(nb_accords*sizeof(DEGREES));
    ret->triads= malloc(nb_accords*sizeof(TRIADS_IN_SCALE));
    

    //needs to do the loop where I generate each chord by looking at the string between "[... ,"; ", ... ,"
    //or ", ... ]"

    while(1){
        break;
    }

    return ret ;

}*/