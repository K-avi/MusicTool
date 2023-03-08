#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "types.h"
#include <stdbool.h>
#include <stdio.h>





extern SYNTAX_ERROR syntaxcheck(char *str);

extern SYNTAX_ERROR scalecheck(char* str);
extern SYNTAX_ERROR harmocheck(char * str);
extern SYNTAX_ERROR triadcheck(char * str);
extern SYNTAX_ERROR dodeccheck(char*str);
extern SYNTAX_ERROR progcheck(char *str );

extern SYNTAX_ERROR helpcheck(char * str);

extern SYNTAX_ERROR readcommandcheck( char * str);
extern SYNTAX_ERROR filename_check_var(char * str);

extern SYNTAX_ERROR env_check(char * str);
extern SYNTAX_ERROR prog_triad_randcheck(char * str, char mode);
extern PITCH_CLASS_SET rot_pcs( PITCH_CLASS_SET scale, CPT n);

#ifdef DEBUG

extern SYNTAX_ERROR prog_triad_randargcheck(char * str, int* size, char mode );

extern SYNTAX_ERROR parsescalecheck(char *str);


extern SYNTAX_ERROR removecheck(char *str);

extern SYNTAX_ERROR printcheck(char *str);

extern SYNTAX_ERROR harmocheck(char * str);

extern SYNTAX_ERROR two_num_args_check(char * str);
extern SYNTAX_ERROR parenthesis_check( FILE * f);




extern SYNTAX_ERROR env_scale_check ( char *str) ;
extern char* file_to_string( char* str);
#endif
#endif