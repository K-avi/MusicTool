#include "parsing.h"
#include "types.h"
#include "string.h"
#include "init.h"
#include "scalegen.h"
#include "user_info.h"
#include "bitop.h"
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


WORD_BITS str_to_wordbits( char * str){ //turns a string into WORD_BITS so that it can then be analyzed 

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
    

    /* 
    the words are between 1 and 5 'characters' . The way it's analyzed is  
    I check the validity of every character. 
    this function is ugly AF tbh I might make it cleaner at some point 
    */

   
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
               // printf("in V\n");
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

    }else if((word & (mask<<shift))== (WORD_BITS_I)){//I?
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

                   
        
        
        }else if(word & WORD_BITS_V){//IV?
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


CHORD str_to_chord( char* str){//turns the string representing a chord into a CHORD . Makes the assumption that 
//there is no space between the relevent chars. For example : "        bVIm" is accepted but 
// " b V I m " is not
//also does syntax checking for chord with 0 being the return error

    return 0;
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