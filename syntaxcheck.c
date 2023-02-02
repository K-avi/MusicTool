#include "syntaxcheck.h"
#include "bitop.h"
#include "triadgen.h"
#include "dodecseries.h"
#include "parsing.h"
#include "scalegen.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

SYNTAX_ERROR emptycheck(char * str){
    char * tmp=str; 
    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK ;
    return SYNTAX_GENERIC_ERROR;
}


SYNTAX_ERROR printcheck(char *str){//syntax check for the print commands

     char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++; 


    //empty substring after remove 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;

    //number? 
    if(!strncmp(tmp, "env", 3)){
        tmp+=3; 
        return emptycheck(tmp);
    }
    else if(!isdigit(*tmp)) return SYNTAX_INVALID_ARG;
    else {
    
        while(isdigit(*tmp)) tmp++;

        
        while(*tmp==' ' || *tmp=='\t'  || *tmp=='\n') tmp++;
        //nothing appart from a integer in the string
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

        //other char error
        else return SYNTAX_INVALID_CHAR;
    }
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

    if(END_OF_LINE_CHAR(*str)) return SYNTAX_OK;
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

        if(!(*tmp=='\n' || *tmp=='\0' )) return SYNTAX_INVALID_CHAR; //invalid character 
        return SYNTAX_OK;
    }

    return SYNTAX_NO_ARG;
}

SYNTAX_ERROR parsetriadprogcheck(char *str){//syntax check for saving triads

    char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;
    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

    if(*tmp=='['){
        //return invalid prog
        S_TRIAD_PROG* check= str_to_triad_prog(tmp); 
        if(!check ) { free_triad_prog(check); return SYNTAX_INVALID_PROG;}//trying to generate is costly ; maybe shouldn't do this way 
        free_triad_prog(check);
       
        while(*tmp!=']') tmp++; 
        tmp++;

        while(NEUTRAL_CHAR(*tmp)) tmp++; 
      
        if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; 
 
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

SYNTAX_ERROR zero_one_two_arg_check(char * str){//checks the rand command when called with 0 or 1 or 2 integers argument (used triads)

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
    }else if (!strncmp(tmp, "nearby", 6)){
       tmp+=6;
       while(NEUTRAL_CHAR(*tmp)) tmp++; 
       if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
       else if(*tmp!='{') return saved_one_arg_check(tmp);
       else return parsescalecheck(tmp);
    }

    return SYNTAX_INVALID_ARG;
}//not tested

SYNTAX_ERROR filename_check(char * str){ //checks that the str passed as argument is a filename. 
//a filename is considered to be a string w/o spaces

    printf("%s\n", str);
    char * tmp=str; 

    while(NEUTRAL_CHAR(*tmp)) tmp++; 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;

    while( !(NEUTRAL_CHAR(*tmp) )) tmp++; //string w/o spaces or tab or \n

    while(NEUTRAL_CHAR( *tmp)) tmp++; //whatever next 

    printf("%s\n", tmp);
    if(END_OF_LINE_CHAR(*tmp) ) return SYNTAX_OK; 

    return SYNTAX_INVALID_ARG; //too much args error
}

SYNTAX_ERROR filename_check_var(char * str){ //checks that the str passed as argument is a filename. 
//a filename is considered to be a string w/o spaces

    printf("%s\n", str);
    char * tmp=str; 

    while( *tmp==' ' || *tmp=='\t') tmp++; 
    if(END_OF_LINE_CHAR(*tmp) || *tmp=='\n') return SYNTAX_TOO_FEW_ARGS;
   
    while( !( *tmp==' ' || *tmp=='\t' || *tmp=='\0' )) tmp++; //string w/o spaces or tab or \n
    while(*tmp==' ' || *tmp=='\t') tmp++; //whatever next 

    if(END_OF_LINE_CHAR(*tmp) || *tmp=='\n') return SYNTAX_OK; 

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
    else return parsetriadprogcheck(tmp);

}
SYNTAX_ERROR triadcheck(char * str){ //checks that a string containing a triad command's syntax is correct


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
        return parsetriadprogcheck(tmp+4);
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
        
    }else if (!strncmp(tmp, "triad",5)){
        
        tmp+=5;
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
        
    }else if (!strncmp(tmp, "dodec",5)){
        
        tmp+=5;
        while(NEUTRAL_CHAR(*tmp))tmp++; 
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
        
    }
    return SYNTAX_INVALID_ARG;
}
SYNTAX_ERROR readcommandcheck( char * str){

    char * tmp= str ;

    while(NEUTRAL_CHAR(*tmp))tmp++; 

    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS; 

    return filename_check(tmp);
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

SYNTAX_ERROR serieparsecheck(char *str, u_char mode ){
    //char is a flag; if it's true then func returns ok when tmp is parsed w/o args 
    //if false then a scale MUST be passed
    //checks that if { is passed its a full scale then call scale saved check 
    if(mode && END_OF_LINE_CHAR(*str)) return SYNTAX_OK;
    
    char* tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;
   // if(mode && END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    if(*tmp=='{'){
        S_SCALE check = parse_scale(str);
        if(check==0x7FF){//checks that the scale is full :)
            return parsescalecheck(tmp);
        }
    }else if(END_OF_LINE_CHAR(*tmp)){
        if(mode) return SYNTAX_OK;
        return SYNTAX_TOO_FEW_ARGS;
    }
    return SYNTAX_INVALID_ARG;
}

SYNTAX_ERROR zer_one_saved_one_check(char * str){//worst function name I ever came up with ffs
    /*returns SYNTAX_OK if :
    noarg
    or
    1 integer arg
    or 
    number + saved + number  
    or 
    1 sdodec arg
    or 
    number + sdodec args
    */
    char *tmp=str;
    while (NEUTRAL_CHAR(*tmp)) tmp++;
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

    else if(isdigit(*tmp)){
        while (isdigit(*tmp)) tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

        else if(!strncmp(tmp, "saved", 5)){
            return saved_one_arg_check(tmp);
        }else if(*tmp == '{'){
            return serieparsecheck(tmp, false);
        }
    }else if(*tmp =='{'){
        return serieparsecheck(tmp, false);
    }else if(!strncmp(tmp, "saved", 5)){
        return saved_one_arg_check(tmp);
    }
    return SYNTAX_GENERIC_ERROR;
}

SYNTAX_ERROR zero_serie_saved_check( char * str) {//returns syntax ok if str is empty or a valid serie 
//or saved n ; returns an erorr otherwise 
    char *tmp=str;
    while (NEUTRAL_CHAR(*tmp)) tmp++;
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    
    else if(*tmp =='{'){
        return serieparsecheck(tmp, false);
    }else if(!strncmp(tmp, "saved", 5)){
        return saved_one_arg_check(tmp);
    }
    return SYNTAX_GENERIC_ERROR;
}

SYNTAX_ERROR dodeccheck(char*str){
    char * tmp=str; 
    while(NEUTRAL_CHAR(*tmp) ) tmp++;
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_TOO_FEW_ARGS;
    
    else if(!strncmp(tmp, "save", 4)){
       return serieparsecheck(tmp+4, true);

    }else if (!strncmp(tmp, "remove",6)){
       return removecheck(tmp+6);

    }else if (!strncmp(tmp, "print",5)){
       return printcheck(tmp+5);

    }else if (!strncmp(tmp, "invert",6)){
        return zer_one_saved_one_check(tmp+6);

    }else if (!strncmp(tmp, "retroinv",8)){
        return zer_one_saved_one_check(tmp+8);

    }else if (!strncmp(tmp, "retro",5)){
        return zer_one_saved_one_check(tmp+5);

    }else if (!strncmp(tmp, "prime",5)){
       return zer_one_saved_one_check(tmp+5);

    }else if (!strncmp(tmp, "matrix",6)){
       return zero_serie_saved_check(tmp+6);

    }else if(!strncmp (tmp, "rand", 4)){
        return emptycheck(tmp+4);
    }
    return SYNTAX_INVALID_CHAR;
}



SYNTAX_ERROR prog_degree_check( char * str , u_char * size){
    //doesnt work bc i'm stoopid; have to put the longest strings first lmao 
    char * tmp=str ; 
    while(NEUTRAL_CHAR(*tmp)) tmp++;

    if(*tmp=='I'){
        (*size)=1; 
        return SYNTAX_OK;
    }else if (!strncmp( tmp , "bII",3)){
        (*size)=3;
        return SYNTAX_OK;
    }else if (!strncmp(tmp, "II", 2)){
        (*size)=2; 
        return SYNTAX_OK;
    }else if (!strncmp( tmp , "bIII",4)){
        (*size)=4;
        return SYNTAX_OK;
    }else if (!strncmp(tmp, "III", 3)){
        (*size)=3; 
        return SYNTAX_OK;
    }else if (!strncmp( tmp , "IV",2)){
        (*size)=2;
        return SYNTAX_OK;
    }else if (!strncmp(tmp, "bV", 2)){
        (*size)=2; 
        return SYNTAX_OK;
    }else if (*tmp == 'V'){
        (*size)=1;
        return SYNTAX_OK;
    }else if (!strncmp(tmp, "bVI", 3)){
        (*size)=3; 
        return SYNTAX_OK;
    }else if (!strncmp( tmp , "VI",2)){
        (*size)=2;
        return SYNTAX_OK;
    }else if (!strncmp(tmp, "bVII", 4)){
        (*size)=4; 
        return SYNTAX_OK;
    }else if (!strncmp( tmp , "VII",3)){
        (*size)=3;
        return SYNTAX_OK;
    }else if(END_OF_LINE_CHAR(*tmp)){
        (*size)=0; 
        return SYNTAX_TOO_FEW_ARGS;
    }else {
        (*size)=0;
        return SYNTAX_INVALID_PROG;
    }

    return SYNTAX_INVALID_PROG;
}

SYNTAX_ERROR prog_triad_check(char * str, u_char* size){

    if(!str){ return SYNTAX_OK; size=0;}
    char * tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++ ; 
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

    if(*str=='\0') {return SYNTAX_OK; *size=1;}
    else if( *str=='m') {return SYNTAX_OK; *size=1;}
    else if( *str=='+') {return SYNTAX_OK; *size=1;}
    else if( *str=='-') {return SYNTAX_OK; *size=1;}
    else if(!strncmp( str, "sus2", 4)){return SYNTAX_OK; *size=4;}
    else if(!strncmp( str, "sus4", 4)){return SYNTAX_OK; *size=4;}

    return SYNTAX_INVALID_PROG;
}

SYNTAX_ERROR one_extension_check(char * str){
    
    if(!str) return SYNTAX_TOO_FEW_ARGS;

    char* tmp=str;
    if(!strncmp(tmp,"b2",2)){
        
        tmp+=2; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='2'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(!strncmp(tmp,"b3",2)){
        
        tmp+=2; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='3'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='4'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(!strncmp(tmp,"b5",2)){
        
        tmp+=2; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='5'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(!strncmp(tmp,"b6",2)){
        
        tmp+=2; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='6'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(!strncmp(tmp,"b7",2)){
        
        tmp+=2; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }else if(*tmp=='7'){
        tmp++; 
        while (NEUTRAL_CHAR(*tmp)) tmp++;
        if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    }

    return SYNTAX_INVALID_PROG;
}//not finished

SYNTAX_ERROR all_extensions_check( char *str, u_char* size){//checks if the extensions of a chord r correct ; returns 
//syntax ok / syntax invalid prog/ syntax too few args 

    char * tmp= str; 
    CPT cpt=0;
    while(!END_OF_LINE_CHAR(*tmp)) {
        if(*tmp==',') cpt++; 
        tmp++;
    }
    
    SYNTAX_ERROR check= SYNTAX_TOO_FEW_ARGS;

    char ** strtab= chprog_str_to_tab_chord_str(str,  cpt,  ',');
   
    for(CPT i=0; i<cpt; i++){
        check= one_extension_check(strtab[i]);
        if(check) return check;
    }

    free_str_tab(strtab, cpt);   
    return check;
}//not finished

SYNTAX_ERROR chordparsecheck(char *str){

    char *tmp=str;
    while(NEUTRAL_CHAR(*tmp)) tmp++;
    if( END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;

    u_char *size= malloc(sizeof(u_char));
    *size= 0;

    SYNTAX_ERROR check= SYNTAX_GENERIC_ERROR;
    
    //degree check
    check= prog_degree_check(tmp, size);
    printf("reached 1 \n");
    if(check) { 
        free(size) ;
        return check;
    }//if degree invalid

    tmp+= (*size);
    while(NEUTRAL_CHAR(*tmp)) tmp++;

    //triad check
    check= prog_triad_check(tmp, size);

     printf("reached 2 \n");
    if(check) {
        printf("exit in check after reached2 %s, %d\n", tmp, *tmp);
        free(size);
        return check;
    }
    tmp+=(*size);

    while(NEUTRAL_CHAR(*tmp)) tmp++;
    //extension check;
    if(!strncmp(tmp, "add", 3)){ //extensions
        tmp+=3;
        while(NEUTRAL_CHAR(*tmp)) tmp++;
        check= all_extensions_check(tmp,size);

    }else { //just a triad 
        printf("tmp at exit is: %s\n", tmp);
        if( END_OF_LINE_CHAR(*tmp)){
            free(size); 
            return SYNTAX_OK;
        }
    }

    free(size);
    return SYNTAX_NO_ARG;
}//not finished

SYNTAX_ERROR progparsecheck(char * str){

    char* tmp=str,*tmp1=str; 
    LENGTH length=1;

    CPT open_bracket_check=0, closed_bracket_check=0;


    while(!END_OF_LINE_CHAR(*tmp)) {
        if(*tmp==';') length++;
     
        if(*tmp=='[') open_bracket_check++;
        if( open_bracket_check &&  *tmp==']' ) closed_bracket_check++;
        tmp++;
    }

    if(! (open_bracket_check==1 && closed_bracket_check==1)) return SYNTAX_INVALID_ARG; //checks that only 1 chprog between 
    //brackets is passed 

    while (NEUTRAL_CHAR(*tmp1))tmp1++;
 
    if(*tmp1=='[') tmp1++;
    else { printf("invalid pr1");return (SYNTAX_INVALID_ARG);}
  
    char **strtab = chprog_str_to_tab_chord_str(tmp1,  length, ';');

    SYNTAX_ERROR check= SYNTAX_TOO_FEW_ARGS;
   
    for(CPT i=0; i<length;i++){
     
        printf("%s\n", strtab[i]);
        check= chordparsecheck(strtab[i]);
        printf("check is :%d\n", check);
       
    }
    free_str_tab(strtab,  length);
    return check;
}

SYNTAX_ERROR progsavecheck(char * str){
    char * tmp=str;
    while (NEUTRAL_CHAR (*tmp)) {
        tmp++;
    }
    if(END_OF_LINE_CHAR(*tmp)) return SYNTAX_OK;
    return progparsecheck(tmp);
}

SYNTAX_ERROR progcheck(char *str ){

    char * tmp=str;
    
    while(NEUTRAL_CHAR(*tmp)) tmp++;
    if(END_OF_LINE_CHAR( *tmp)) return SYNTAX_TOO_FEW_ARGS;
    
    else if(!strncmp(tmp, "save", 4)){
       return progsavecheck(tmp+4);

    }else if (!strncmp(tmp, "remove",6)){
       return removecheck(tmp+6);

    }else if (!strncmp(tmp, "print",5)){
       return printcheck(tmp+5);

    }else if(!strncmp (tmp, "rand", 4)){
        return emptycheck(tmp+4);// needs to be changed to custom runtime check for args
    }
    return SYNTAX_INVALID_CHAR;
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
    }else if (!strncmp(tmp, "triad", 5)){
        ret =triadcheck(tmp+5);
    }else if (!strncmp(tmp, "help",4)){
        ret =helpcheck(tmp+4);
    }else if (!strncmp(tmp, "read",4)){
        ret =readcheck(tmp+4);
    }else if (!strncmp(tmp, "write",5)){
        ret =writecheck(tmp+5);
    }else if (!strncmp(tmp, "serie",5)){
        ret =dodeccheck(tmp+5);
    }else if (!strncmp(tmp, "dodec",5)){
        ret =dodeccheck(tmp+5);
    }else if (!strncmp(tmp, "prog",4)){
        ret =progcheck(tmp+4);
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

            str=skip_line(str) ;        
            continue;
        }else if (*str=='{'){
            scale_check= parse_scale(str);
      
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

SYNTAX_ERROR env_triad_check ( char *str) {//checks the syntax of the substring containing an env scale in 
//in an env file string.

    S_TRIAD_PROG * prog_test=NULL;

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
            
            prog_test= str_to_triad_prog(str);
          
          //  printf("%d\n", scale_check);
            if(!prog_test){
                return SYNTAX_INVALID_PROG;
            }else {
                str= strstr(str, "]");
            }
            free_triad_prog(prog_test);
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

SYNTAX_ERROR env_dodec_check(char *str){
    S_DODEC dodec_check=DODEC_ERRFLAG;

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
            return SYNTAX_INVALID_CHAR;
        }
    }
    if(*str=='(') str++;
    while( *str!=')'){
        while( NEUTRAL_CHAR_ENV(*str) || EOL_ENV(*str)) str++;

      
        if(EOF_ENV(*str)) return SYNTAX_MISSING_PAR;
        else if( COMMENT_ENV(*str)) {  //skips the comment line

            str=skip_line(str) ;        
            continue;
        }else if (*str=='{'){
            dodec_check= parse_serie(str);
           //print_serie(dodec_check);
            if(dodec_check==DODEC_ERRFLAG){
                return SYNTAX_INVALID_DODEC;
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

               continue;
            }else if(!strncmp(tmp, "triad", 5)){
                tmp+=5;
              
                scheck=env_triad_check(tmp);
                if(scheck) return scheck;
                tmp=strstr(tmp, ")");
                tmp++;
               
               continue;
            }else if(!strncmp(tmp, "dodec", 5)){
          
                tmp+=5;
               
                scheck=env_dodec_check(tmp);
                if(scheck) return scheck;
                tmp=strstr(tmp, ")");
                tmp++;
              // printf("%s\n", tmp); 
               continue;
            }else {
                return SYNTAX_INVALID_CHAR;
            }
        }

        tmp++;
    }

    return SYNTAX_OK;
}