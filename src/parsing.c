#include "parsing.h"
#include "chordgen.h"
#include "types.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "init.h"
#include "scalegen.h"
#include "user_info.h"
#include "misc.h"
#include "bitop.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "triadprint.h"


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


WORD_BITS str_to_wordbits( char * str, unsigned char mode){ //turns a string into WORD_BITS so that it can then be analyzed 
//word bits is an intermediate format for chord prog parsing between a chord written as a string and a chord 
//written as a short 
//mode t is for triad ; c is for chord ; d is for degree
    if(!str) return 0;
    char * tmp= str; 

    while(*tmp==' ') tmp++; //goes to the first non space character in the string

    WORD_BITS word=0;

    CPT cpt=0; //the longest word of the lang is bVIIm , cpt is a filter -> any word longer than bVIIm is not valid

    
    while(*tmp!='\0' && tmp && cpt<=5){

        
        if( *tmp == ' ') break;

        else if(*tmp=='I' )
            word |= (WORD_BITS_I<<(4*cpt));
        
        else if(*tmp=='V' )
            word |= (WORD_BITS_V<<(4*cpt));

        else if(*tmp=='b'  )
            word |= (WORD_BITS_b<<(4*cpt));
        else if(*tmp=='m' && mode!='d' )
            word |= (WORD_BITS_m<<(4*cpt));
        
        else if(*tmp=='+' && mode!='d' )
            word |= (WORD_BITS_aug<<(4*cpt));
        else if(*tmp=='-' && mode!='m' )
            word |= (WORD_BITS_dim<<(4*cpt));
        else if(!strncmp(tmp, "sus2", 4) && mode!='d' ){
            word|= (WORD_BITS_sus2<<(4*cpt));
            tmp+=3;
        }else if(!strncmp(tmp, "sus4", 4) && mode!='d' ){
            word|= (WORD_BITS_sus4<<(4*cpt));
            tmp+=3;
        }
        
        else { 
            if (mode=='t' || mode=='d')return 0; //case if the word contains a non valid character
            else if(mode=='c'){ 
                if(!strncmp(tmp, "add", 3) )
                return word;
            }
            else return 0;
        }
        cpt++;
        tmp++;
    }
    

    if(cpt>6) return 0; //case if word too big 

    if(*tmp!='\0' &&  mode=='t'){
        while(*tmp== ' ') tmp++; //makes sure that there isn't two substrings separated by spaces in str
        if(*tmp!= '\0') return 0; //error if two sets of characters separated by a space.
    }

    if(*tmp!='\0' &&  mode=='c'){
        while(*tmp== ' ') tmp++; //makes sure that there isn't two substrings separated by spaces in str
        if(strncmp(tmp, "add", 3) && (*tmp!='\0')) return 0; //error if not EOL or add 
    }

    return word;
}

TRIAD word_bits_to_chord (WORD_BITS word){//translates word bits into a chord. Returns zero if the word isn't valid
    
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
    unsigned short mask = 0xF; // 111 

    if( (word &mask)== WORD_BITS_b ){ //b? 
        //priprintf("in b\n");
        shift+=4;

        //printf("%b\n", word & (mask<<shift));
        if( (word & (mask<<shift))== (unsigned)(WORD_BITS_I)<<shift){ //bI?

            shift+=4;
            if((word & (mask<<shift))== (unsigned)(WORD_BITS_I)<<shift){ //bII?
                shift+=4;
                if((word & (mask<<shift))== (unsigned)(WORD_BITS_I)<<shift){//bIII?
                   shift+=4 ;
                    if((word & (mask<<shift))== (unsigned)(WORD_BITS_m)<<shift){//bIIIm
                        return DEG_bIII|(MIN <<4);

                    }else if((word & (mask<<shift))== (unsigned)(WORD_BITS_aug)<<shift){//bIII+
                        return DEG_bIII|(AUG <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//bIII-
                        return DEG_bIII|(DIM <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//bIIIsus2
                        return DEG_bIII|(SUS2 <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//bIIIsus4
                        return DEG_bIII|(SUS4 <<4);
                    }else if( !(word & (mask<<shift) )){//bIII 
                        return DEG_bIII|(MAJ <<4);

                    }else 
                        return 0; //error if char other than correct ones

                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//bIIm
                    return DEG_bII|(MIN <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//bII+
                    return DEG_bII|(AUG <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//bII-
                    return DEG_bII|(DIM <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//bIIsus2
                        return DEG_bII|(SUS2 <<4);

                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//bIIsus4
                        return DEG_bII|(SUS4 <<4);
                }else if( !(word & (mask<<shift) )){//bII
                    return DEG_bII|(MAJ <<4);
                }else return 0; //error case 
                   
            }else {return 0;} //error case 

        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_V)<<shift){ //bV?
               
            shift+=4;
            if((word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){//bVI?
                shift+=4;
                if((word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){//bVII?
                    shift+=4;
                    
                    if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//bVIIm
                        return DEG_bVII|(MIN <<4);
                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//bVII+
                        return DEG_bVII|(AUG <<4);
                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//bVII-
                        return DEG_bVII|(DIM <<4);
                      
                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//bVIIsus2
                        return DEG_bVII|(SUS2 <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//bVIIsus4
                        return DEG_bVII|(SUS4 <<4);
                    }else if( !(word & (mask<<shift) )){//bVII
                        return DEG_bVII|(MAJ <<4);
                    }else return 0; //error if char other than correct ones
                    
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//bVIm
                    return DEG_bVI|(MIN <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//bVI+
                    return DEG_bVI|(AUG <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//bVI-
                    return DEG_bVI|(DIM <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//bVIsus2
                    return DEG_bVI|(SUS2 <<4);

                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//bVIsus4
                    return DEG_bVI|(SUS4 <<4);
                }else if( !(word & (mask<<shift) )){//bVI
                    return DEG_bVI|(MAJ <<4);  
                }else return 0; //error if char other than correct ones

            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//bVm
                return DEG_bV|(MIN <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//bV+
                return DEG_bV|(AUG <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//bV-
                return DEG_bV|(DIM <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//bVsus2
                return DEG_bV|(SUS2 <<4);

            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//bVsus4
                return DEG_bV|(SUS4 <<4);
            }else if( !(word & (mask<<shift) )){//bV
                return DEG_bV|(MAJ <<4);  
            }else return 0; //error if char other than correct ones
        }else{
            return 0;
        }

    }else if((word & (mask))== (unsigned) (WORD_BITS_I)){//I?
        //cases: I Im I+ I- II III IV 
        shift+=4;
        
        if((word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){ //II?
                shift+=4;
                if( (word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){//III?
                   shift+=4; 
                    if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//IIIm
                        return DEG_III|(MIN <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//III+
                        return DEG_III|(AUG <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//III-
                        return DEG_III|(DIM <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//IIIsus2
                        return DEG_III|(SUS2 <<4);

                    }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//IIIsus4
                        return DEG_III|(SUS4 <<4);
                    }else if( !(word & (mask<<shift) )){//III 
                        return DEG_III|(MAJ <<4);

                    }else 
                        return 0; //error if char other than correct ones

                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//IIm
                    return DEG_II|(MIN <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//II+
                    return DEG_II|(AUG <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//II-
                    return DEG_II|(DIM <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//IIsus2
                        return DEG_II|(SUS2 <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//IIsus4
                    return DEG_II|(SUS4 <<4);
                }else if( !(word & (mask<<shift) )){//II
                    return DEG_II|(MAJ <<4);
                }else return 0; //error case        
        
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_V)<<shift){//IV?
            shift+=4;

            if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//IVm
                return DEG_IV|(MIN <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//IV+
                return DEG_IV|(AUG <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//IV+
                return DEG_IV|(AUG <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//IVsus2
                    return DEG_IV|(SUS2 <<4);

            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//IVsus4
                    return DEG_IV|(SUS4 <<4);
            }else if( !(word & (mask<<shift) )){//IV maj
                return DEG_IV|(MAJ <<4);   
            }else return 0; //error if char other than correct ones
            
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//Im
            return DEG_I|(MIN <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//I+
            return DEG_I|(AUG <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//I-
            return DEG_I|(DIM <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//Isus2
            return DEG_I|(SUS2 <<4);

        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//Isus4
            return DEG_I|(SUS4 <<4);
        }else if( !(word & (mask<<shift) )){//I maj
            //printf("here\n");
            return DEG_I|(MAJ <<4);
        }else return 0; //error case      

    }else if ( (word & (mask<<shift))== (unsigned) (WORD_BITS_V)<<shift){//V?
        //cases : V VI VII

        shift+=4;
        if((word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){//VI?
            shift+=4;
            if((word & (mask<<shift))== (unsigned) (WORD_BITS_I)<<shift){//VII?
                shift+=4;
                    
                if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//VIIm
                    return DEG_VII|(MIN <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//VII+
                    return DEG_VII|(AUG <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//VII-
                    return DEG_VII|(DIM <<4);
                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//VIIsus2
                    return DEG_VII|(SUS2 <<4);

                }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//VIIsus4
                    return DEG_VII|(SUS4 <<4);
                }else if( !(word & (mask<<shift) )){//VII
                    return DEG_VII|(MAJ <<4);
                }else return 0; //error if char other than correct ones
                    
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//VIm
                return DEG_VI|(MIN <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//VI+
                return DEG_VI|(AUG <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//VI-
                return DEG_VI|(DIM <<4);
            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//VIsus2
                return DEG_VI|(SUS2 <<4);

            }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//VIsus4
                return DEG_VI|(SUS4 <<4);
            }else if( !(word & (mask<<shift) )){//VI
                return DEG_VI|(MAJ <<4);  
            }else return 0; //error if char other than correct ones

        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_m)<<shift){//Vm
            return DEG_V|(MIN <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_aug)<<shift){//V+
            return DEG_V|(AUG <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_dim)<<shift){//V-
            return DEG_V|(AUG <<4);
        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus2)<<shift){//Vsus2
            return DEG_V|(SUS2 <<4);

        }else if((word & (mask<<shift))== (unsigned) (WORD_BITS_sus4)<<shift){//Vsus4
            return DEG_V|(SUS4 <<4);
        }else if( !(word & (mask<<shift) )){//V
            return DEG_V|(MAJ <<4);   
        }else return 0; //error if char other than correct ones
        
    }else{
        return 0;
    }
    return 0;
}//need to add sus2 n sus4 support to this (annoying)



TRIAD str_to_triad( char* str, unsigned char mode ){
    if(!str) return 0;
    return word_bits_to_chord(str_to_wordbits(str, mode));
}

DEGREES_BITS str_to_degree( char* str, unsigned char mode ){
    if(!str) return 0;
    return word_bits_to_chord(str_to_wordbits(str, mode))&0xF;
}

CHORD str_to_chord_ext( char* str){
    if(!str) return 0;
    TRIAD chord= word_bits_to_chord(str_to_wordbits(str, 't'));
    CHORD ret = chord & 0xF;
    switch (chord>>4){
        case MIN: ret|= MINOR_PCS<<4; break;
        case MAJ: ret|= MAJOR_PCS<<4; break;
        case AUG: ret|= AUG_PCS<<4; break;
        case DIM: ret|=DIM_PCS<<4; break;
        case SUS2: ret|= SUS2_PCS<<4; break; 
        case SUS4: ret|= SUS4_PCS<<4; break;
        default:  ret=0;
    }
    return ret;
}


char ** chprog_str_to_tab_chord_str( char* str, LENGTH length, char separator){//turns a string containing 
//a chord prog to a tab of string where each index of the tab contains a substring of str w one chord 
    if(!str) return NULL;
    if(!length) return NULL;

    char ** ret= malloc(length* sizeof(char*));
    INDEX i=0;
    CPT cpt=0;

    char * tmp= str, *tmp1=str; 

    for(CPT cpt1=0; cpt1<length; cpt1++){//initialises to null
        ret[cpt1]=NULL;
    }

    while(*tmp!='\0' && *tmp1!='\0'){

        while(*tmp1!= separator && *tmp1!=']' && *tmp1!='\0'){
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
    if(!str_tab) return;
    for (CPT i=0; i<length; i++){
      
        if(str_tab[i]!=NULL)free(str_tab[i]);
    }
    free(str_tab);
}


S_TRIAD_PROG* str_to_triad_prog( char* str){//turns the string containing a chord prog to a S_CHORD_PROG* .
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
    char ** chord_tab= chprog_str_to_tab_chord_str(tmp1, num_of_chord, ',');
    
    S_TRIAD_PROG * ch_prog= malloc(sizeof(S_TRIAD_PROG));

    ch_prog->length=num_of_chord; 
    ch_prog->chord_prog=malloc(num_of_chord* sizeof(TRIAD));

    for(CPT i=0; i<num_of_chord; i++){
        
        ch_prog->chord_prog[i]= str_to_triad(chord_tab[i] , 't');

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

S_DEGREE_PROG* str_to_deg_prog( char* str){//turns the string containing a chord prog to a S_CHORD_PROG* .
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
    char ** chord_tab= chprog_str_to_tab_chord_str(tmp1, num_of_chord, ',');
    
    S_DEGREE_PROG * deg_prog= malloc(sizeof(S_TRIAD_PROG));

    deg_prog->length=num_of_chord; 
    deg_prog->degree_prog=malloc(num_of_chord* sizeof(unsigned char));

    for(CPT i=0; i<num_of_chord; i++){
        //printf("%s\n", chord_tab[i]);
        deg_prog->degree_prog[i]= str_to_degree(chord_tab[i] , 'd'); 
    }
    free_str_tab(chord_tab, num_of_chord);
    return deg_prog;
}//not tested 





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


CHORD str_to_chord( char * str){
    if(!str) return 0;

    TRIAD chord= str_to_triad(str, 'c');

    CHORD ret= chord & 0xF;
    ret |= triadbits_to_chord(ret>>4)<<4;

    return ret;
}

S_EXTENSIONS str_to_extension_degree(char * str){ //turns a string containing ONLY 
//1 extension into a S_EXTENSION (scale degree); can sett endchar to ; or ] 
    char * tmp=str;

    while(*tmp==' ' || *tmp== '\t') tmp++;
    if(*tmp=='\0' ) return 0;
    S_EXTENSIONS ret=0;
    while( *tmp!='\0'){
       
        if(!strncmp(tmp, "b2", 2)){
            tmp+=2; 
            ret|= NOTE_b2;
        }else if(*tmp == '2'){
            tmp++; 
            ret|= NOTE_2;
        }else if(!strncmp(tmp , "b3", 2)){
            tmp+=2; 
            ret|= NOTE_b3;
        }else if(*tmp == '3'){
            tmp++; 
            ret|= NOTE_3;
        }else if(*tmp == '4'){
            tmp++; 
            ret|= NOTE_4;
        }else if(!strncmp(tmp , "b5", 2)){
            tmp+=2; 
            ret|= NOTE_b5;
        }else if(*tmp == '5'){
            tmp++; 
            ret|= NOTE_5;
        }else if(!strncmp(tmp , "b6", 2)){
            tmp+=2; 
            ret|= NOTE_b6;
        }else if(*tmp == '6'){
            tmp++; 
            ret|= NOTE_6;
        }else if(!strncmp(tmp , "b7", 2)){
            tmp+=2; 
            ret|= NOTE_b7;
        }else if(*tmp == '7'){
            tmp++; 
            ret|= NOTE_7;
        }else if(*tmp==',' || *tmp==' '){
            tmp++; 
        }else {//invalid char 
          //  printf("in error ext to deg\n");
            return 0;
        }
    }
    return ret;
}

S_EXTENSIONS str_to_extensions( char * str, char endchar){//turns a string of format "add I, J, K,..."
//into an S_EXTENSIONS short (mirror name for S_SCALE)
    char * tmp=str;
   
    if(strlen(tmp)<=3) return 0;
    if(strncmp( tmp, "add",3 )){
        return 0;
    }
    tmp+=3;
    if(*tmp=='\0') return 0;
    return str_to_extension_degree(tmp);
}

S_CHPROG* str_to_chprog( char* str){//turns the string containing a chord prog to a S_CHORD_PROG* .
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
        if(*tmp==';') num_of_chord++;
        tmp++;
    }

    tmp1++;
    char ** chord_tab= chprog_str_to_tab_chord_str(tmp1, num_of_chord, ';');
    
    S_CHPROG * ch_prog= malloc(sizeof(S_CHPROG));

    ch_prog->length=num_of_chord; 
    ch_prog->chprog=malloc(num_of_chord* sizeof(S_CHPROG));

    TRIADS_BITS curtriad=0; 
    S_EXTENSIONS curextension=0;
    char endchar=';' ;
    for(CPT i=0; i<num_of_chord; i++){

        if(i==num_of_chord-1) endchar=']'; //assigns endchar to ']' in the last iteration
        curtriad= str_to_triad(chord_tab[i], 'c');
       
        tmp=strstr(chord_tab[i], "add");
        if(tmp){ 
            curextension= str_to_extensions(tmp, endchar )<<4;
           
            if( !(curtriad && curextension)){ 
                free(ch_prog->chprog);
                free(ch_prog); 
                free_str_tab(chord_tab, num_of_chord); 
              
                return NULL;
            }
            ch_prog->chprog[i]= curextension| triad_to_chord_ext(curtriad) ;
        }else {
            ch_prog->chprog[i]= triad_to_chord_ext(curtriad);
        }
    }
    free_str_tab(chord_tab, num_of_chord);
    return ch_prog;
}