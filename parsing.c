#include "parsing.h"
#include "types.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"
#include "scalegen.h"
#include "user_info.h"
#include "bitop.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


#ifdef WIN32 

char * strndup( char * str, size_t chars){
    if(!str) return NULL;
    char * buffer; 
    int n; 
    buffer=(char*) malloc(chars+1); 

    if(buffer){
        for(n=0; ((n<chars) && (str[n]!=0)); n++) buffer[n]= str[n];
        
    }
    return buffer;
}
#endif

LENGTH parse_scale_length(const char* string){//returns the length of a scale if a char between 0 and 9 is 
//in a string and 13 otherwise

    LENGTH ret=13;
    while ( *string!='\0'){
        
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
    while (*string!='\0'){
        
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
    while ( *string!='\0'){
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

char * set_to_first_bracket( char* str){//sets a str to the first iteration of '0'; returns a null string otherwhise.
  int i=0;
  while(str[i]!='{' && str[i]!='\0') i++;

  if(str[i]=='{') return &str[i];
  return NULL;
}

S_SCALE parse_scale(char *string){ //parses a scale; returns ERROR_FLAG scale if no scale is found or if there are invalid chars in the scale
    if(string==NULL) return ERROR_FLAG;
    S_SCALE ret=0;
    NOTE note=0;
    char *tmp= set_to_first_bracket(string);
    
    if(!tmp) return ERROR_FLAG;
    tmp++;

    CPT zero_check =0; //checks that '0' is present in the scale

    while(*tmp!='}' && *tmp!='\0' ){
       
        if(*tmp>='0' && *tmp<='9'){ 
            if(*tmp=='0') zero_check=1;
            note=atoi(tmp)%12;
            //if(note>11) return ERROR_FLAG;
            add_note(&ret, note);
            while(isdigit(*tmp)) tmp++; //avoids problem with 10 or eleven
        }else if( !(*tmp==' ' || *tmp=='\t' || *tmp=='\n'  || *tmp=='}' || *tmp=='\0')) { return ERROR_FLAG;}
        if(*tmp!='}')tmp++;
    }  
 
    if(*tmp!='}' )return ERROR_FLAG;
    if(!zero_check) return ERROR_FLAG;
   
    return ret;
}


WORD_BITS str_to_wordbits( char * str){ //turns a string into WORD_BITS so that it can then be analyzed 
//word bits is an intermediate format for chord prog parsing between a chord written as a string and a chord 
//written as a short 
    if(!str) return 0;
    char * tmp= str; 

    while(*tmp==' ') tmp++; //goes to the first non space character in the string

    WORD_BITS word=0;

    CPT cpt=0; //the longest word of the lang is bVIIm , cpt is a filter -> any word longer than bVIIm is not valid

    
    while(*tmp!='\0' && tmp && cpt<=5){

        
        if( *tmp == ' ') break;

        else if(*tmp=='I' )
            word |= (WORD_BITS_I<<(3*cpt));
        
        else if(*tmp=='V' )
            word |= (WORD_BITS_V<<(3*cpt));

        else if(*tmp=='b' )
            word |= (WORD_BITS_b<<(3*cpt));
        else if(*tmp=='m' )
            word |= (WORD_BITS_m<<(3*cpt));
        
        else if(*tmp=='+' )
            word |= (WORD_BITS_aug<<(3*cpt));
        else if(*tmp=='-' )
            word |= (WORD_BITS_dim<<(3*cpt));
        
        else return 0; //case if the word contains a non valid character
        
        cpt++;
        tmp++;
    }

    if(cpt>5) return 0; //case if word too big 

    if(*tmp!='\0'){
        while(*tmp== ' ') tmp++; //makes sure that there isn't two substrings separated by spaces in str
        if(*tmp!= '\0') return 0; //error if two sets of characters separated by a space.
    }

    return word;
}

CHORD word_bits_to_chord (WORD_BITS word){//translates word bits into a chord. Returns zero if the word isn't valid
    
    //chrecks that there is no space between the relevent chars. For example : "        bVIm" is accepted but 
    // " b V I m " is not
    //also does syntax checking for chord with 0 being the return error

    /* 
    the words are between 1 and 5 'characters' . The way it's analyzed is  
    I check the validity of every character. 
    this function is ugly AF tbh I might make it cleaner at some point 
    */

    //the function is a monstrous amalgamation of boilerplates n I feel pretty bad about it.
    // I'll rewrite it at some point

   
    if(!word) return 0;
    
    
    CPT shift=0;

    unsigned short mask =7; // 111 

    if( (word &mask)== WORD_BITS_b ){ //b? 
        //priprintf("in b\n");
        shift+=3;

        //printf("%b\n", word & (mask<<shift));
        if( (word & (mask<<shift))== (WORD_BITS_I)<<shift){ //bI?

            shift+=3;
            if((word & (mask<<shift))== (WORD_BITS_I)<<shift){ //bII?
                shift+=3;
                if((word & (mask<<shift))== (WORD_BITS_I)<<shift){//bIII?
                   shift+=3; 
                    if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//bIIIm
                        return DEG_bIII|(MIN <<4);

                    }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//bIII+
                        return DEG_bIII|(AUG <<4);

                    }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//bIII-
                        return DEG_bIII|(DIM <<4);

                    }else if( !(word & (mask<<shift) )){//bIII 
                        return DEG_bIII|(MAJ <<4);

                    }else 
                        return 0; //error if char other than correct ones

                }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//bIIm
                    return DEG_bII|(MIN <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//bII+
                    return DEG_bII|(AUG <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//bII-
                    return DEG_bII|(DIM <<4);
                }else if( !(word & (mask<<shift) )){//bII
                    return DEG_bII|(MAJ <<4);
                }else return 0; //error case 

                   
            }else {return 0;} //error case 



        }else if((word & (mask<<shift))== (WORD_BITS_V)<<shift){ //bV?
               
            shift+=3;
            if((word & (mask<<shift))== (WORD_BITS_I)<<shift){//bVI?
                shift+=3;
                if((word & (mask<<shift))== (WORD_BITS_I)<<shift){//bVII?
                    shift+=3;
                    
                    if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//bVIIm
                        return DEG_bVII|(MIN <<4);
                    }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//bVII+
                        return DEG_bVII|(AUG <<4);
                    }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//bVII-
                        return DEG_bVII|(DIM <<4);
                    }else if( !(word & (mask<<shift) )){//bVII
                        return DEG_bVII|(MAJ <<4);
                    }else return 0; //error if char other than correct ones
                    
                }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//bVIm
                    return DEG_bVI|(MIN <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//bVI+
                    return DEG_bVI|(AUG <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//bVI-
                    return DEG_bVI|(DIM <<4);
                }else if( !(word & (mask<<shift) )){//bVI
                    return DEG_bVI|(MAJ <<4);  
                }else return 0; //error if char other than correct ones

            }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//bVm
                return DEG_bV|(MIN <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//bV+
                return DEG_bV|(AUG <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//bV-
                return DEG_bV|(DIM <<4);
            }else if( !(word & (mask<<shift) )){//bV
                return DEG_bV|(MAJ <<4);  
            }else return 0; //error if char other than correct ones
        }else{
           //("in error b\n");
            return 0;
        }

    }else if((word & (mask))== (WORD_BITS_I)){//I?
        //cases: I Im I+ I- II III IV 
        shift+=3;
        
        if((word & (mask<<shift))== (WORD_BITS_I)<<shift){ //II?
                shift+=3;
                if( (word & (mask<<shift))== (WORD_BITS_I)<<shift){//III?
                   shift+=3; 
                    if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//IIIm
                        return DEG_III|(MIN <<4);

                    }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//III+
                        return DEG_III|(AUG <<4);

                    }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//III-
                        return DEG_III|(DIM <<4);

                    }else if( !(word & (mask<<shift) )){//III 
                        return DEG_III|(MAJ <<4);

                    }else 
                        return 0; //error if char other than correct ones

                }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//IIm
                    return DEG_II|(MIN <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//II+
                    return DEG_II|(AUG <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//II-
                    return DEG_II|(DIM <<4);
                }else if( !(word & (mask<<shift) )){//II
                    return DEG_II|(MAJ <<4);
                }else return 0; //error case 

                   
        
        
        }else if((word & (mask<<shift))== (WORD_BITS_V)<<shift){//IV?
            shift+=3;

            if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//IVm
                return DEG_IV|(MIN <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//IV+
                return DEG_IV|(AUG <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//IV+
                return DEG_IV|(AUG <<4);
            }else if( !(word & (mask<<shift) )){//IV maj
                return DEG_IV|(MAJ <<4);   
            }else return 0; //error if char other than correct ones
            
        }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//Im
            return DEG_I|(MIN <<4);
        }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//I+
            return DEG_I|(AUG <<4);
        }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//I-
            return DEG_I|(DIM <<4);
        }else if( !(word & (mask<<shift) )){//I maj
            return DEG_I|(MAJ <<4);
        }else return 0; //error case 
        

    }else if ( (word & (mask<<shift))== (WORD_BITS_V)<<shift){//V?
        //cases : V VI VII
      

        shift+=3;
        if((word & (mask<<shift))== (WORD_BITS_I)<<shift){//VI?
            shift+=3;
            if((word & (mask<<shift))== (WORD_BITS_I)<<shift){//VII?
                shift+=3;
                    
                if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//VIIm
                    return DEG_VII|(MIN <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//VII+
                    return DEG_VII|(AUG <<4);
                }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//VII-
                    return DEG_VII|(DIM <<4);
                }else if( !(word & (mask<<shift) )){//VII
                    return DEG_VII|(MAJ <<4);
                }else return 0; //error if char other than correct ones
                    
            }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//VIm
                return DEG_VI|(MIN <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//VI+
                return DEG_VI|(AUG <<4);
            }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//VI-
                return DEG_VI|(DIM <<4);
            }else if( !(word & (mask<<shift) )){//VI
                return DEG_VI|(MAJ <<4);  
            }else return 0; //error if char other than correct ones

        }else if((word & (mask<<shift))== (WORD_BITS_m)<<shift){//Vm
            return DEG_V|(MIN <<4);
        }else if((word & (mask<<shift))== (WORD_BITS_aug)<<shift){//V+
            return DEG_V|(AUG <<4);
        }else if((word & (mask<<shift))== (WORD_BITS_dim)<<shift){//V-
            return DEG_V|(AUG <<4);
        }else if( !(word & (mask<<shift) )){//V
            return DEG_V|(MAJ <<4);   
        }else return 0; //error if char other than correct ones
        
    }else{
        return 0;
    }
    return 0;
}


CHORD str_to_chord( char* str){
    if(!str) return 0;

    return word_bits_to_chord(str_to_wordbits(str));
}



char ** chprog_str_to_tab_chord_str( char* str, LENGTH length){//turns a string containing 
//a chord prog to a tab of string where each index of the tab contains a substring of str w one chord 
    if(!str) return NULL;
    if(!length) return NULL;

    char ** ret= malloc(length* sizeof(char*));
    INDEX i=0;
    CPT cpt=0;
int debug=0;
    char * tmp= str, *tmp1=str; 

    while(*tmp!='\0' && *tmp1!='\0'){

        while(*tmp1!= ',' && *tmp1!=']' && *tmp1!='\0'){
            cpt++;
            tmp1++;
             
        }

        if(*tmp1== ']'){
           
            ret[i++]= strndup(tmp, cpt);
            break;
        }
        else if(*tmp1== '\0'){//useless normally

            ret[i++]= strndup(tmp, cpt);
            break;
        }else{
             
            ret[i++]= strndup(tmp, cpt);
            cpt=0;
            tmp=tmp1; 
            tmp++;
            tmp1++;
        }
    }
    return ret;
}

void free_str_tab(char ** str_tab, LENGTH length){
    for (CPT i=0; i<length; i++){
        free(str_tab[i]);
    }
    free(str_tab);
}


S_CHORD_PROG* str_to_chord_prog( char* str){//turns the string containing a chord prog to a S_CHORD_PROG* .


    //first step is to divide the chord in substrings. To do so , we begin at '[' n then count the number of ',' to allocate an 
    //array of string (char** ) that will contain each word. then fill each string of the array w what is between the ',' then analyze each string to create the chord prog. 
    //at the end check if every chord is not null and return zero if so
    if(!str) return NULL;

    char * tmp= strstr(str , "["), *tmp1=tmp;

    
    if(!tmp) return NULL; //checks that str contains [
    
    if(!strstr(str, "]")) return NULL; //checks that the string contains a closing bracket

    if(*(++tmp)=='\0') return NULL; //checks that [ isnt the last character of the string

    CPT num_of_chord=1;

    while( *tmp!=']' ){
        if(*tmp==',') num_of_chord++;
        tmp++;
    }


    
    tmp1++;

    char ** chord_tab= chprog_str_to_tab_chord_str(tmp1, num_of_chord);
    
    S_CHORD_PROG * ch_prog= malloc(sizeof(S_CHORD_PROG));

    ch_prog->length=num_of_chord; 
    ch_prog->chord_prog=malloc(num_of_chord* sizeof(CHORD));

    for(CPT i=0; i<num_of_chord; i++){
        
        ch_prog->chord_prog[i]= str_to_chord(chord_tab[i]);

        if( !(ch_prog->chord_prog[i])){ 
          
            free(ch_prog->chord_prog);
            free(ch_prog); 
            free_str_tab(chord_tab, num_of_chord); 

            return NULL;

        }
    }

    free_str_tab(chord_tab, num_of_chord);
    return ch_prog;

}


unsigned char next_not_blank_comment( char *str, char chr){
//when given a string returns 1 if the first not space or tabulation or comment (#) character is chr n 0 otherwise 
//WARGNING: RETURNS  \n AS AN END OF LINE
    if(!str ) return 0;
    while(*str!='\0' && *str!='\n'){
        if(*str=='#'){
            return 2;
        }
        if(*str==' ' || *str=='\t' ) str++;
        else if( *str == chr){
            return 1; 
        }else { return 0;}
    }
    return 2;
}


char* syntax_error_flag_to_str(SYNTAX_ERROR flag ){
    if(!flag ) return NULL; //case syntax ok; shouldn't be passed
    switch (flag) {
    case SYNTAX_INVALID_SCALE : return "scale passed isn't valid\n";
    case SYNTAX_NO_ARG : return "no args passed\n"; //passed 0 args when one or more needed
    case SYNTAX_INVALID_CHAR: return "invalid char\n";  //passed invalid chars
    case SYNTAX_UNCLOSED_SCALE: return "scale was opened but never closed\n";  //scale opened n never closed
    case SYNTAX_UNCLOSED_PROG : return "chprog was opened but never closed\n";  //chprog opened n never closed 
    case SYNTAX_TOO_MUCH_ARGS : return "too much arguments given\n";//too much args passed 
    case SYNTAX_TOO_FEW_ARGS : return "too few arguments given\n"; //passed too few args 
    case SYNTAX_INVALID_PROG:return "invalid chprog\n"; //invalid prog
    case SYNTAX_GENERIC_ERROR: return "generic error\n";//generic error
    case SYNTAX_INVALID_ARG: return "argument passed isn't valid\n"; //invalid argument error


    case SYNTAX_TWO_PAR_OPEN: return "two parenthesis opened\n";  //two ( (  not separated by a ) in an env file.
    case SYNTAX_TWO_PAR_CLOSED: return "two parenthesis closed\n";  //same with ))
    case SYNTAX_UNMATCHED_OPENED_PAR :return "parenthesis was opened but never closed \n"; //par opened never closed. 
    case SYNTAX_UNMATCHED_CLOSED_PAR: return "parenthesis was closed but never open\n"; //par closed never opened
    case SYNTAX_UNCLOSED_ENV: return "environment was never closed\n";
    case SYNTAX_MISSING_PAR: return "parenthesis missing\n";
    case SYNTAX_INVALID_SOF: return "invalid start of file\n";
    default: return NULL;

    }
}

char* file_to_string( char* str){

    if(!str) return NULL;
    char * buffer = 0;
    long length;
    FILE * f = fopen (str, "rb");

    if (f){
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length+1);
    if (buffer){
        fread (buffer, 1, length, f);
    }
    fclose (f);
    }else{ return NULL;}

    if(!buffer ) return NULL;
    buffer[length]='\0';
    return buffer;
}