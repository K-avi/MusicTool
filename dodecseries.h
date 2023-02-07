#ifndef SERIE_H 
#define SERIE_H

#include "types.h"
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

#define INIT_DODEC 0xDDDDDDDDDDDD
#define ISFULL_SERIE(serie) ( ((serie)& 0xF00000000000)!= 0xD00000000000)


//random gen function
extern S_DODEC generate_serie();
extern S_DODEC shuffle_serie(S_DODEC seed, unsigned long long num);


//utility functions 
extern S_DODEC inverse_serie(S_DODEC serie);
extern S_DODEC retrograde_serie (S_DODEC serie);
extern S_DODEC retrograde_inverse_serie(S_DODEC serie);
extern S_DODEC first_prime(S_DODEC serie);

extern S_DODEC nth_prime( S_DODEC serie, INDEX n );
extern S_DODEC nth_inv (S_DODEC serie, INDEX n);
extern S_DODEC nth_retrograde (S_DODEC serie, INDEX n);
extern S_DODEC nth_retrograde_inverse( S_DODEC serie, INDEX n);

//stdio functions
extern void print_serie(S_DODEC serie);
extern void print_12t_mat(S_DODEC* mat);
void fprint_serie( FILE* f,const S_DODEC serie );

extern S_DODEC parse_serie(char * str);

//12 tone mat functions

extern S_DODEC * serie_to_12tmat( S_DODEC serie);

#ifdef DEBUG 

extern S_DODEC add_rand_to_dodec( S_DODEC serie);
extern bool isvalid_serie(S_DODEC serie);
extern bool note_in_dodec( S_DODEC serie, NOTE note);
extern S_DODEC add_to_dodec( S_DODEC serie, NOTE note);
extern S_DODEC shuffle_once( S_DODEC seed, INDEX i1, INDEX i2);
#endif
#endif
