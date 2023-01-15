#include "syntaxcheck.h"
#include "bitop.h"
#include "chordgen.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>



//  SYNTAX CHECKING DOESNT ACCOUNT FOR LINES THAT CONTAIN A COMMAND N THEN A # WILL HAVE TO FIX





//gonna return 1 or 0 for testing; will change to different error flags afterwards for error messages

//syntax check for common functions : print and remove 



SYNTAX_ERROR printcheck(char *str){//syntax check for the print commands

     char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++; 


    //empty substring after remove 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;

    //number? 
    if(!isdigit(*tmp)) return SYNTAX_INVALID_ARG;
    while(isdigit(*tmp)) tmp++;

    
    while(*tmp==' ' || *tmp=='\t'  || *tmp=='\n') tmp++;
    //nothing appart from a integer in the string
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

    //other char error
    else return SYNTAX_INVALID_CHAR;
    return SYNTAX_TOO_FEW_ARGS;
}



SYNTAX_ERROR removecheck(char *str){//syntax check for the remove commands

    char *tmp=str;
    while(*tmp==' ' || *tmp=='\n' || *tmp=='\t') tmp++; 


    //empty substring after remove 
    if(*tmp=='\0' ) return SYNTAX_TOO_FEW_ARGS;

    //number? 
    while(isdigit(*tmp)) tmp++;

    
    while(*tmp==' ' || *tmp=='\t' || *tmp=='\n') tmp++;
    //nothing appart from a integer in the string
    if(*tmp=='\0' ) return SYNTAX_OK;

    //other char error
    else return SYNTAX_INVALID_CHAR;

}//not tested

SYNTAX_ERROR parsescalecheck(char *str){//syntax check for parsing scales and modes

    char *tmp=str;
    while( *tmp==' '  || *tmp=='\n' || *tmp== '\t') tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;


    if(*tmp=='{'){
        
        S_SCALE check= parse_scale(tmp); 
        //return syntax invalid scale
        if(check & ERROR_FLAG) return SYNTAX_INVALID_SCALE;
       

        while(*tmp!='}') tmp++; 
        tmp++;

        while(*tmp==' ' || *tmp=='\t' || *tmp=='\n') tmp++; 
      //return invalid char
        if(!(*tmp=='\n' || *tmp=='\0' )) return SYNTAX_INVALID_CHAR; //invalid character 
        return SYNTAX_OK;
    }



    return SYNTAX_NO_ARG;
}

SYNTAX_ERROR parseprogcheck(char *str){//syntax check for saving chprogs

    char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;


    if(*tmp=='['){
        //return invalid prog
        S_CHORD_PROG* check= str_to_chord_prog(tmp); 
        if(!check ) { free_chord_prog(check); return SYNTAX_INVALID_PROG;}//trying to generate is costly ; maybe shouldn't do this way 
        free_chord_prog(check);
       

        while(*tmp!=']') tmp++; 
        tmp++;

        while(NEUTRAL_CHAR(*tmp)) tmp++; 
      
        if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; 
        
        //return invalid character 
        return SYNTAX_INVALID_CHAR;
    }



    return SYNTAX_NO_ARG;
}

SYNTAX_ERROR zero_one_arg_check(char * str){//checks the rand command when called with 0 or 1 argument (in scale and harmo)

    char *tmp=str;

    while( *tmp=='\n' || *tmp=='\t' || *tmp ==' ' )tmp++;

        if(  *tmp =='\0') return SYNTAX_OK; //called w/o argument
        while(isdigit(*tmp)) tmp++;//1 number ?
        
            
        while(*tmp==' ' || *tmp=='\n' || *tmp=='\t')tmp++; 
        if(*tmp=='\0' ) return SYNTAX_OK; //end of string?
        return SYNTAX_TOO_MUCH_ARGS; //any other char
        //return too much args
        
}

SYNTAX_ERROR zero_one_two_arg_check(char * str){//checks the rand command when called with 0 or 1 or 2 integers argument (used chprog)

    char *tmp=str;

    while( NEUTRAL_CHAR(*tmp) )tmp++;

    if(  END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK; //called w/o argument
    
    while(isdigit(*tmp)) tmp++;// number ?
    while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; //called with one argument

    while(isdigit(*tmp)) tmp++;// number ?
    while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; //called with two argument


    return SYNTAX_TOO_MUCH_ARGS; //too much args 
}

SYNTAX_ERROR two_num_args_check(char * str){//checks that a string contains two integers n nothing else 

    char *tmp= str;

    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!isdigit(*tmp)) return SYNTAX_TOO_FEW_ARGS; 

    //too few args


    while(isdigit(*tmp)) tmp++;
 //first integer in string is ok ; checks second: 

    while( NEUTRAL_CHAR(*tmp )) tmp++;
    if(!isdigit(*tmp)) return SYNTAX_TOO_FEW_ARGS;  //too few args
    while(isdigit(*tmp)) tmp++;
    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!END_OF_LINE_CHAR(*tmp)) return SYNTAX_INVALID_CHAR; //invalid chr error 

    return SYNTAX_OK;

}

SYNTAX_ERROR one_num_arg_check( char * str){//checks that a string contains 1 integer and nothing else

    char *tmp= str;

    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if(!isdigit(*tmp)) return SYNTAX_TOO_FEW_ARGS;  //too few args 


    while(isdigit(*tmp)) tmp++;
 //integer in string is ok; checks that nothing else is in 

    while( NEUTRAL_CHAR(*tmp )) tmp++;
    if(!END_OF_LINE_CHAR(*tmp)) return SYNTAX_INVALID_CHAR; //invalid chr in string

    return SYNTAX_OK;
}
//scale syntax check ////////////


SYNTAX_ERROR saved_one_arg_check (char * str){//checks that a string is of the form .... saved n

 //   printf("entered saved one arg check\n");
    char * tmp = str; 

    while( NEUTRAL_CHAR(*tmp )) tmp++;
    //printf("%s\n", tmp);
    if(!strncmp (tmp, "saved", 5)){
        //printf("reached this check\n");
        return one_num_arg_check(tmp+5);
    }else {
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;
        else return SYNTAX_INVALID_ARG;
    }

}

SYNTAX_ERROR intvcheck(char * str){//checks that an intv command is of the form 
//" intv struct " or "intv vector" with a scale or 1 arg or saved n
    char * tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;
    if(!strncmp(tmp, "struct", 6)){
        tmp+=6; 
        while(NEUTRAL_CHAR( *tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        else if(*tmp=='{') return parsescalecheck(tmp);
        else return saved_one_arg_check(tmp);
    }else if (!strncmp(tmp, "vector", 6)){
        tmp+=6;
        while(NEUTRAL_CHAR( *tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        else if(*tmp=='{') return parsescalecheck(tmp);
        else return saved_one_arg_check(tmp);
    }else{
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; 
        else return SYNTAX_INVALID_ARG;
    }

}

SYNTAX_ERROR scalecheck(char* str){//return SYNTAX_OK || 

    char * tmp=str; 
    while(  NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; //too few args

    else if( !strncmp(tmp, "rand", 4)){

        
        return zero_one_arg_check(tmp+4);
        
    }else if(!strncmp(tmp, "remove", 6)){
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"save",4)){
        return parsescalecheck(tmp+4);
    }else if(!strncmp (tmp, "invert",6)){
        
       tmp+=6;
       while(NEUTRAL_CHAR(*tmp)) tmp++; 
       if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
       else if(*tmp!='{') return saved_one_arg_check(tmp);
       else return parsescalecheck(tmp);
    }else if(!strncmp( tmp, "comp", 4)){
       
        tmp+=4;
       while(NEUTRAL_CHAR(*tmp)) tmp++; 
       if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
       else if(*tmp!='{') return saved_one_arg_check(tmp);
       else return parsescalecheck(tmp);
    }else if(!strncmp( tmp, "prime", 5)){
     
       tmp+=5;
       while(NEUTRAL_CHAR(*tmp)) tmp++; 
       if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
       else if(*tmp!='{') return saved_one_arg_check(tmp);
       else return parsescalecheck(tmp);
    }else if (!strncmp( tmp, "intv", 4)){
        return intvcheck(tmp+4);
    }

    return SYNTAX_INVALID_ARG;
}//not tested

SYNTAX_ERROR filename_check(char * str){ //checks that the str passed as argument is a filename. 

//a filename is considered to be a string w/o spaces

    char * tmp=str; 

    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;

    while( !(NEUTRAL_CHAR(*tmp) )) tmp++; //string w/o spaces or tab or \n

    while(NEUTRAL_CHAR( *tmp)) tmp++; //whatever next 

    if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; 

    return SYNTAX_INVALID_ARG; //too much args error
}




//HARMO SYNTAX CHECK

SYNTAX_ERROR harmocheck(char * str){
    char * tmp=str; 
    while( NEUTRAL_CHAR(*tmp )) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; //too few args error

    if(!strncmp(tmp, "remove", 6)){ // harmo remove N
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){ // harmo print N
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"saved",5)){ //harmo saved scale N
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp)) tmp++;

        if(!strncmp(tmp, "scale", 5)){
             
            return one_num_arg_check(tmp+5);
        }
        else return SYNTAX_INVALID_ARG;
    }else if(!strncmp (tmp ,"save",4)){ //harmo save N || harmo save as scale I J
        tmp+=4;
       
        while(NEUTRAL_CHAR(*tmp)) tmp++;
        if(*tmp=='{'){  //case:harmo save N
    
            return parsescalecheck(tmp);
        }else if(!strncmp(tmp, "as", 2)){ //case : harmo save as scale I J
            tmp+=2; 

            //("%s\n", tmp);
            
            while(NEUTRAL_CHAR(*tmp))tmp++; 
            if(!strncmp(tmp,  "scale", 5)) {
               // printf("%s\n", tmp);
                return two_num_args_check(tmp+5);
            }
            else return SYNTAX_INVALID_ARG;
        
        }else if( END_OF_LINE_CHAR(*tmp) ){return SYNTAX_OK;}
    }else if( !strncmp(tmp, "rand", 4)){ // harmo rand || harmo rand N
        return zero_one_arg_check(tmp+4);
    }else if( ! strncmp(tmp , "scale", 5)){
        return parsescalecheck(tmp+5);
    }

    return SYNTAX_INVALID_ARG;

}

SYNTAX_ERROR toscalecheck(char* str){
    
    char* tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;
    
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    else if(*tmp!='[') return saved_one_arg_check(tmp);
    else return parseprogcheck(tmp);

}
SYNTAX_ERROR chprogcheck(char * str){ //checks that a string containing a chprog command's syntax is correct


    char * tmp=str; 

    while(  NEUTRAL_CHAR(*tmp)) tmp++;

    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;

    else if( !strncmp(tmp, "rand", 4)){

        
        return zero_one_two_arg_check(tmp+4);
        
    }else if(!strncmp(tmp, "remove", 6)){
        return removecheck(tmp+6);
    }else if(!strncmp(tmp, "print", 5)){
        return printcheck(tmp+5);
    }else if(!strncmp (tmp ,"save",4)){
        return parseprogcheck(tmp+4);
    }else if(!strncmp (tmp, "toscale", 7)){
        return toscalecheck(tmp+7);
    }
    return SYNTAX_INVALID_ARG; 
}


SYNTAX_ERROR helpcheck(char * str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK; 

    else if (!strncmp(tmp, "scale", 5)){

        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }else if (!strncmp(tmp, "harmo",5)){
        
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }else if (!strncmp(tmp, "chprog",6)){
        
        tmp+=6;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }else if (!strncmp(tmp, "write",5)){
        
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }else if (!strncmp(tmp, "read",4)){
        
        tmp+=4;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }
    return SYNTAX_INVALID_ARG;
}

SYNTAX_ERROR readcheck( char * str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; 

    else if (!strncmp(tmp, "command", 7)){
        //printf("checking");
        return filename_check(tmp+7);
    }else if (!strncmp(tmp, "env", 3)){
        return filename_check(tmp+3);
    }
    return SYNTAX_INVALID_ARG;
}

SYNTAX_ERROR writecheck ( char *str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; 
    
    else if (!strncmp(tmp, "env", 3)){
        return filename_check(tmp+3);
    }
    return SYNTAX_INVALID_ARG;

}




SYNTAX_ERROR commentcheck( char * str){//checks if a line contains a comment

    char * tmp = str; 
    
    while (NEUTRAL_CHAR(*tmp)) tmp++;

    if(*tmp=='#') return SYNTAX_OK; 
    return SYNTAX_GENERIC_ERROR;
}

SYNTAX_ERROR emptycheck(char * str){
    char * tmp=str; 
    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK ;
    return SYNTAX_GENERIC_ERROR;
}

SYNTAX_ERROR syntaxcheck(char *str){
    //returns SYNTAX_OK if the syntax of a line is correct; an error flag otherwise
    char * tmp=str;
    while(*tmp=='\n' || *tmp==' ' || *tmp=='\t') tmp++; 
    if( *tmp=='\0' || *tmp=='#') return SYNTAX_OK; 


    SYNTAX_ERROR ret;

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
 
    }else if (!strncmp(tmp, "quit",4)){
        ret=emptycheck(tmp+4);
        if(ret) ret= SYNTAX_INVALID_CHAR;
    }else {
        ret= SYNTAX_INVALID_ARG;
    }
    return ret;
}






char* skip_line(char * str){
    //sets a str to the next new line in it; or the next end of string char if \n isnt found. 

    while(! (*str=='\n' || *str=='\0')) str++;
    return str;
}

SYNTAX_ERROR env_scl_harmo_check ( char *str) {//checks the syntax of the substring containing an env scale in 
//in an env file string.

    S_SCALE scale_check=ERROR_FLAG;

    while( *str!='('){ //found open parenthesis
        while( NEUTRAL_CHAR_ENV(*str) || EOL_ENV(*str)) str++;
        if(EOF_ENV(*str)) return SYNTAX_MISSING_PAR;
        else if( COMMENT_ENV(*str)) {  //skips the comment line
            str=skip_line(str) ;
             continue;
        }else if(*str=='('){ 
            str++;
            break;
        }else{
            //printf("in seeking ( inval\n");
            return SYNTAX_INVALID_CHAR;
        }
    }
    if(*str=='(') str++;
    while( *str!=')'){
        while( NEUTRAL_CHAR_ENV(*str) || EOL_ENV(*str)) str++;

      
        if(EOF_ENV(*str)) return SYNTAX_MISSING_PAR;
        else if( COMMENT_ENV(*str)) {  //skips the comment line

           // printf("skipping line\n");
            str=skip_line(str) ;
          
           
            continue;
        }else if (*str=='{'){
          //  printf("%s\n", str);
            scale_check= parse_scale(str);
           // print_scale(scale_check);
          //  printf("%d\n", scale_check);
            if(scale_check&ERROR_FLAG){
                return SYNTAX_INVALID_SCALE;
            }else {
                str= strstr(str, "}");
            }
            str++; 
            continue;
        }else if(*str==')'){ 
            break;
        }else{
          // printf("%c in seeking ) inval\n", *str);
            return SYNTAX_INVALID_CHAR;
        }
    }
    
    return SYNTAX_OK;

}

SYNTAX_ERROR env_chprog_check ( char *str) {//checks the syntax of the substring containing an env scale in 
//in an env file string.

    S_CHORD_PROG * prog_test=NULL;

    while( *str!='('){ //found open parenthesis
        while( NEUTRAL_CHAR_ENV(*str) || EOL_ENV(*str)) str++;
        if(EOF_ENV(*str)) return SYNTAX_MISSING_PAR;
        else if( COMMENT_ENV(*str)) {  //skips the comment line
            str=skip_line(str) ;
             continue;
        }else if(*str=='('){ 
            str++;
            break;
        }else{
           // printf("in seeking ( inval\n");
            return SYNTAX_INVALID_CHAR;
        }
    }
     if(*str=='(') str++;
    while( *str!=')'){
        while( NEUTRAL_CHAR_ENV(*str) || EOL_ENV(*str)) str++;

      
        if(EOF_ENV(*str)) return SYNTAX_MISSING_PAR;
        else if( COMMENT_ENV(*str)) {  //skips the comment line

           // printf("skipping line\n");
            str=skip_line(str) ;
          
           
            continue;
        }else if (*str=='['){
            
            prog_test= str_to_chord_prog(str);
          
          //  printf("%d\n", scale_check);
            if(!prog_test){
                return SYNTAX_INVALID_PROG;
            }else {
                str= strstr(str, "]");
            }
            free_chord_prog(prog_test);
            str++; 
            continue;
        }else if(*str==')'){ 
            break;
        }else{
            //printf("%c in seeking ) inval\n", *str);
            return SYNTAX_INVALID_CHAR;
        }
    }
    str++;
    return SYNTAX_OK;

}
SYNTAX_ERROR env_check(char * str){//checks the syntax of an env file passed as one beeeg string.

    if(!str) return SYNTAX_INVALID_ARG;
    char * tmp= str;
    SYNTAX_ERROR scheck=0;

    if(strncmp( str, "MusicTool:environment",18)){
        return SYNTAX_INVALID_SOF;
    }

    tmp+=18;

    while(!EOF_ENV(*tmp)){

        while(NEUTRAL_CHAR(*tmp)) tmp++;
        if(EOF_ENV(*tmp)) break; //reached EOF
        if(EOL_ENV(*tmp)) {tmp++; continue;}//empty line

        else if(COMMENT_ENV(*tmp)){ 
            while(!(EOL_ENV(*tmp) || EOF_ENV(*tmp) )){ tmp++;}
            continue;
        }//read comment line until EOF/EOL
    
        else if(!strncmp(tmp, "env", 3)){
            tmp+=3;
        

            while(NEUTRAL_CHAR_ENV(*tmp)) tmp++;
            if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_NO_ARG;

            else if(!strncmp(tmp, "scale", 5)){
                
                tmp+=5;
                scheck=env_scl_harmo_check(tmp);
                if(scheck) return scheck;
                tmp=strstr(tmp, ")");
                tmp++;
             // printf("%s\n", tmp); 
               continue;
            }else if(!strncmp(tmp, "harmo", 5)){
               
                tmp+=5;
                // printf("%s\n", tmp);
                scheck=env_scl_harmo_check(tmp);
                if(scheck) return scheck;
                tmp=strstr(tmp, ")");
                tmp++;
               //printf("%s\n", tmp); 
               continue;
            }else if(!strncmp(tmp, "chprog", 6)){
                //printf("chprog reached\n");
                tmp+=6;
               // printf("%s\n", tmp);
                scheck=env_chprog_check(tmp);
                if(scheck) return scheck;
                tmp=strstr(tmp, "]");
                tmp++;
              // printf("%s\n", tmp); 
               continue;
            }
        }

        tmp++;
    }

    return SYNTAX_OK;
}