#include "parsing.h"
#include "types.h"
#include "string.h"
#include "init.h"
#include "scalegen.h"
#include <stdio.h>
#include <stdlib.h>

LENGTH parse_scale_length(const char* string){// it's embarrassing how bad I am at string parsing
    //used to retrieve the length of a random scale to generate from the terminal in scale mode
    LENGTH ret= rand()%12;

    //case if parsing from the scalegen mode
    if (!strncmp(string, "Gen_Rand_Scale",14)){

        if (string[14]==0 || string[14]==10){ //0 is the value of \0 10 is the value of backspace
            ret=rand()%12;
            printf("\nsize of scale isn't specified, length generated is %d\n", ret);
            return ret;
        }else if(string[14]==32){ //32 is the value of [space]

            if( (string[15]>=49 && string[15]<=57) || (string[15]>=65) && (string[15] <=67) || (string[15]>=97) && (string[15] <=99) ){
                switch ((LENGTH) string[15]){ //very messy; should change it tbh
                    case 49: return (LENGTH) 1; break;
                    case 50: return (LENGTH) 2; break;
                    case 51: return (LENGTH) 3; break;
                    case 52: return (LENGTH) 4; break;
                    case 53: return (LENGTH) 5; break;
                    case 54: return (LENGTH) 6; break;
                    case 55: return (LENGTH) 7; break;
                    case 56: return (LENGTH) 8; break;
                    case 57: return (LENGTH) 9; break;

                    case 65: return (LENGTH) 10; break;
                    case 66: return (LENGTH) 11; break;
                    case 67: return (LENGTH) 12; break;

                    case 97: return (LENGTH) 10; break;
                    case 98: return (LENGTH) 11; break;
                    case 99: return (LENGTH) 12; break;

                    default: return (LENGTH) rand()%12; break;
                }
            }
        }
    }

    //case if parsing from the harmo_scale mode

     if (!strncmp(string, "Harmo_Rand_Scale",16)){

        if (string[16]==0 || string[16]==10){ //0 is the value of \0 10 is the value of backspace
            ret=rand()%12;
            printf("\nsize of scale isn't specified, length generated is %d\n", ret);
            return ret;
        }else if(string[16]==32){ //32 is the value of [space]

            if( (string[17]>=49 && string[17]<=57) || (string[17]>=65) && (string[17] <=67) || (string[17]>=97) && (string[17] <=99) ){
                switch ((LENGTH) string[17]){ //very messy; should change it tbh
                    case 49: return (LENGTH) 1; break;
                    case 50: return (LENGTH) 2; break;
                    case 51: return (LENGTH) 3; break;
                    case 52: return (LENGTH) 4; break;
                    case 53: return (LENGTH) 5; break;
                    case 54: return (LENGTH) 6; break;
                    case 55: return (LENGTH) 7; break;
                    case 56: return (LENGTH) 8; break;
                    case 57: return (LENGTH) 9; break;

                    case 65: return (LENGTH) 10; break;
                    case 66: return (LENGTH) 11; break;
                    case 67: return (LENGTH) 12; break;

                    case 97: return (LENGTH) 10; break;
                    case 98: return (LENGTH) 11; break;
                    case 99: return (LENGTH) 12; break;

                    default: return (LENGTH) rand()%12; break;
                }
            }
        }
    }

    ret=rand()%12;
    printf("\nstring wasn't parsed correctly; length of the scale set to %d\n", ret);
    return ret;
}

S_SCALE * parse_scale( char * string){ //parses a scale from a string containing numbers from 0 to 11(b) written in hexadecimal form

    S_SCALE * rep=malloc(sizeof (S_SCALE));
    partial_init_scale(rep);

    if(strlen(string)>50){
        printf("\nstring parsed is too long, please try a shorter string\n");
        init_scale(rep);
        return rep;
    }

    int i=11;
    NOTE note=13;
    if(!strncmp(string, "Harmo_Scale",11)){
        while((string[i]!=(char)10 )&& (string[i]!=(char)0)){

            if( (string[i]>=48 && string[i]<=57) || (string[i]>=65) && (string[i] <67) || (string[i]>=97) && (string[i] <99) ){

                switch ((NOTE) string[i]){ //very messy; should change it tbh
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

                    default: note= 13; break;
                }
                add_note(rep, note);
            }
            i++;
        }
    }
    return rep;
}

