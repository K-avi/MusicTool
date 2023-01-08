#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "types.h"
#include <stdbool.h>
#include <stdio.h>





extern SYNTAX_ERROR syntaxcheck(char *str);


//testing only
extern SYNTAX_ERROR savescalecheck(char *str);

extern SYNTAX_ERROR scalecheck(char* str);
extern SYNTAX_ERROR removecheck(char *str);

extern SYNTAX_ERROR printcheck(char *str);

extern SYNTAX_ERROR harmocheck(char * str);

extern SYNTAX_ERROR two_num_args_check(char * str);
extern SYNTAX_ERROR parenthesis_check( FILE * f);

extern SYNTAX_ERROR env_check(char * str);

#ifdef DEBUG
extern SYNTAX_ERROR env_scale_check ( char *str) ;
extern char* file_to_string( char* str);
#endif
#endif