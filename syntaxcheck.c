#include "syntaxcheck.h"
#include "bitop.h"
#include "parsing.h"
#include "types.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>



//gonna return 1 or 0 for testing; will change to different error flags afterwards for error messages

//syntax check for common functions : print and remove 



bool printcheck(char *str){

     char *tmp=str;
    while(*tmp==' ') tmp++; 


    //empty substring after remove 
    if(*tmp=='\0') return 0;

    //number? 
    while(isdigit(*tmp)) tmp++;

    
    while(*tmp==' ' || *tmp=='\t'  || *tmp=='\n') tmp++;
    //nothing appart from a integer in the string
    if(*tmp=='\0') return 1;

    //other char error
    else return 0;
    return 0;
}//not tested

bool removecheck(char *str){

    char *tmp=str;
    while(*tmp==' ' || *tmp=='\n' || *tmp=='\t') tmp++; 


    //empty substring after remove 
    if(*tmp=='\0' ) return 0;

    //number? 
    while(isdigit(*tmp)) tmp++;

    
    while(*tmp==' ' || *tmp=='\t' || *tmp=='\n') tmp++;
    //nothing appart from a integer in the string
    if(*tmp=='\0' ) return 1;

    //other char error
    else return 0;

}//not tested

bool savescalecheck(char *str){

    char *tmp=str;
    while( *tmp==' '  || *tmp=='\n' || *tmp== '\t') tmp++;

    if( *tmp =='\0') return 0;


    if(*tmp=='{'){
        
        S_SCALE check= parse_scale(tmp); 
        if(check & ERROR_FLAG) return 0;
       

        while(*tmp!='}') tmp++; 
        tmp++;

        while(*tmp==' ' || *tmp=='\t' || *tmp=='\n') tmp++; 
      
        if(!(*tmp=='\n' || *tmp=='\0' )) return 0; //invalid character 
        return 1;
    }



    return 0;
}//not tested

//scale syntax check ////////////

bool scalecheck(char* str){

    char * tmp=str; 
    while(  *tmp=='\n' || *tmp==' ' || *tmp=='\t') tmp++;

    if( *tmp =='\0') return 0;

    else if( !strncmp(tmp, "rand", 4)){

        tmp+=4;
       
        while( *tmp=='\n' || *tmp=='\t' || *tmp ==' ' )tmp++;

        if(  *tmp =='\0') return 1;
        else if ( isdigit(*tmp)){
            tmp++;
            if(isdigit(*tmp )) (tmp++);
            while(*tmp==' ' || *tmp=='\n' || *tmp=='\t')tmp++; 
            if(*tmp=='\0' ) return 1; //end of string?
            return 0; //any other char
        }
        return 0;
    }else if(!strncmp(tmp, "remove", 6)){
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"save",4)){
        return savescalecheck(tmp+4);
    }

    return false;
}//not tested


//HARMO SYNTAX CHECK

bool harmocheck(char * str){
    return false;
}
bool chprogcheck(char * str){
    return false; 
}
bool helpcheck(char * str){
    return false;
}
bool readcheck( char * str){
    return false;
}

bool writecheck ( char *str){
    return false; 
}

bool envcheck( char * str){
    return false;
}

bool syntaxcheck(char *str){
    //returns 1 if the syntax of a line is correct; 0 otherwise
    char * tmp=str;
    while(*tmp=='\n' || *tmp==' ' || *tmp=='\t') tmp++; 
    if( *tmp=='\0' || *tmp=='#') return 1; 


    bool ret;

    if(!strncmp(tmp, "scale", 5 )){
        ret= scalecheck(tmp+5);
    }else if (!strncmp(tmp, "harmo",5)){
        ret =harmocheck(tmp+5);
    }else if (!strncmp(tmp, "chprog", 6)){
        ret =chprogcheck(tmp+6);
    }else if (!strncmp(tmp, "help",4)){
        ret =helpcheck(tmp+4);
    }else if (!strncmp(tmp, "read",4)){
        ret =readcheck(tmp+4);
    }else if (!strncmp(tmp, "write",5)){
        ret =writecheck(tmp+5);
    }else if (!strncmp(tmp, "env",3)){
        ret =envcheck(tmp+3);
    }else ret=0;
    return ret;
}