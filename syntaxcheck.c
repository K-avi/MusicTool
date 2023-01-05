#include "syntaxcheck.h"
#include "bitop.h"
#include "chordgen.h"
#include "parsing.h"
#include "types.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>



//  SYNTAX CHECKING DOESNT ACCOUNT FOR LINES THAT CONTAIN A COMMAND N THEN A # WILL HAVE TO FIX

#define NEUTRAL_CHAR( chr) ( (chr)==' ' || (chr)=='\t' || (chr)=='\n')

#define END_OF_LINE_CHAR( chr) (chr == '\0' || chr=='#')



//gonna return 1 or 0 for testing; will change to different error flags afterwards for error messages

//syntax check for common functions : print and remove 



bool printcheck(char *str){//syntax check for the print commands

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

bool removecheck(char *str){//syntax check for the remove commands

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

bool savescalecheck(char *str){//syntax check for saving scale and modes

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
}

bool saveprogcheck(char *str){//syntax check for saving chprogs

    char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return 0;


    if(*tmp=='['){
        
        S_CHORD_PROG* check= str_to_chord_prog(tmp); 
        if(!check ) { free_chord_prog(check); return 0;}//trying to generate is costly ; maybe shouldn't do this way 
        free_chord_prog(check);
       

        while(*tmp!=']') tmp++; 
        tmp++;

        while(NEUTRAL_CHAR(*tmp)) tmp++; 
      
        if(END_OF_LINE_CHAR(*tmp) ) return 1; //invalid character 
        return 0;
    }



    return 0;
}

bool zero_one_arg_check(char * str){//checks the rand command when called with 0 or 1 argument (in scale and harmo)

    char *tmp=str;

    while( *tmp=='\n' || *tmp=='\t' || *tmp ==' ' )tmp++;

        if(  *tmp =='\0') return 1; //called w/o argument
        while(isdigit(*tmp)) tmp++;//1 number ?
        
            
        while(*tmp==' ' || *tmp=='\n' || *tmp=='\t')tmp++; 
        if(*tmp=='\0' ) return 1; //end of string?
        return 0; //any other char
        
}

bool zero_one_two_arg_check(char * str){//checks the rand command when called with 0 or 1 or 2 integers argument (used chprog)

    char *tmp=str;

    while( NEUTRAL_CHAR(*tmp) )tmp++;

    if(  END_OF_LINE_CHAR(*tmp)) return 1; //called w/o argument
    
    while(isdigit(*tmp)) tmp++;// number ?
    while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp) ) return 1; //called with one argument

    while(isdigit(*tmp)) tmp++;// number ?
    while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp) ) return 1; //called with two argument


    return 0; //any other char    
}

bool two_num_args_check(char * str){//checks that a string contains two integers n nothing else 

    char *tmp= str;

    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!isdigit(*tmp)) return 0; 


    while(isdigit(*tmp)) tmp++;
 //first integer in string is ok ; checks second: 

    while( NEUTRAL_CHAR(*tmp )) tmp++;
    if(!isdigit(*tmp)) return 0;
    while(isdigit(*tmp)) tmp++;
    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!END_OF_LINE_CHAR(*tmp)) return 0; //invalid chr in string

    return 1;

}

bool one_num_arg_check( char * str){//checks that a string contains 1 integer and nothing else

    char *tmp= str;

    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!isdigit(*tmp)) return 0; 


    while(isdigit(*tmp)) tmp++;
 //integer in string is ok; checks that nothing else is in 

    while( NEUTRAL_CHAR(*tmp )) tmp++;
    if(!END_OF_LINE_CHAR(*tmp)) return 0; //invalid chr in string

    return 1;
}
//scale syntax check ////////////

bool scalecheck(char* str){

    char * tmp=str; 
    while(  NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return 0;

    else if( !strncmp(tmp, "rand", 4)){

        
        return zero_one_arg_check(tmp+4);
        
    }else if(!strncmp(tmp, "remove", 6)){
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"save",4)){
        return savescalecheck(tmp+4);
    }

    return false;
}//not tested

bool filename_check(char * str){ //checks that the str passed as argument is a filename. 

//a filename is considered to be a string w/o spaces

    char * tmp=str; 

    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return 0;

    while( !(NEUTRAL_CHAR(*tmp) )) tmp++; //string w/o spaces or tab or \n

    while(NEUTRAL_CHAR( *tmp)) tmp++; //whatever next 

    if(END_OF_LINE_CHAR(*tmp)) return 1; 

    return 0;
}




//HARMO SYNTAX CHECK

bool harmocheck(char * str){
    char * tmp=str; 
    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return 0;

    else if(!strncmp(tmp, "remove", 6)){ // harmo remove N
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){ // harmo print N
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"saved",5)){ //harmo saved scale N
        while(NEUTRAL_CHAR(*tmp)) tmp++;

        if(!strncmp(tmp, "scale", 5)){
            return one_num_arg_check(tmp+5);
        }
        else return 0;
    }else if(!strncmp (tmp ,"save",4)){ //harmo save N || harmo save as scale I J

        while(NEUTRAL_CHAR(*tmp)) tmp++;
        if(*tmp=='{'){  //case:harmo save N
            return savescalecheck(tmp+4);
        }else if(!strncmp(tmp, "as", 2)){ //case : harmo save as scale I J
            tmp+=2; 
            
            while(NEUTRAL_CHAR(*tmp))tmp++; 
            if(!strncmp(tmp,  "scale", 4)) return two_num_args_check(tmp+4);
            else return 0;
        
        } 
    }else if( !strncmp(tmp, "rand", 4)){ // harmo rand || harmo rand N
        return zero_one_arg_check(tmp+4);
    }

    return false;

}
bool chprogcheck(char * str){ //checks that a string containing a chprog command's syntax is correct


    char * tmp=str; 

    while(  NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return 0;

    else if( !strncmp(tmp, "rand", 4)){

        
        return zero_one_two_arg_check(tmp+4);
        
    }else if(!strncmp(tmp, "remove", 6)){
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"save",4)){
        return savescalecheck(tmp+4);
    }
    return false; 
}


bool helpcheck(char * str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return 1; 

    else if (!strncmp(tmp, "scale", 5)){

        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return 1;
        
    }else if (!strncmp(tmp, "harmo",5)){
        
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return 1;
        
    }else if (!strncmp(tmp, "chprog",6)){
        
        tmp+=6;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return 1;
        
    }else if (!strncmp(tmp, "write",5)){
        
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return 1;
        
    }else if (!strncmp(tmp, "read",4)){
        
        tmp+=4;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return 1;
        
    }
    return 0;
}

bool readcheck( char * str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return 0; 

    else if (!strncmp(tmp, "command", 7)){
        return filename_check(tmp+7);
    }else if (!strncmp(tmp, "env", 3)){
        return filename_check(tmp+3);
    }
    return 0;
}

bool writecheck ( char *str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return 0; 
    
    else if (!strncmp(tmp, "env", 3)){
        return filename_check(tmp+3);
    }
    return 0;

}

bool envcheck( char * str){ //not yet 
    return false;
}

bool commentcheck( char * str){//checks if a line contains a comment

    char * tmp = str; 
    
    while (NEUTRAL_CHAR(*tmp)) tmp++;

    if(*tmp=='#') return 1; 
    return 0;
}

bool emptycheck(char * str){
    char * tmp=str; 
    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return 1 ;
    return 0;
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
    }else ret=commentcheck(tmp) | emptycheck(tmp);
    return ret;
}