#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "types.h"

extern LENGTH parse_scale_length(const char* string);
extern S_SCALE  parse_scale( char * string);
extern char * set_to_beginning( char* str);

extern SIGNED_LENGTH parse_index(const char* string);
extern SIGNED_LENGTH parse_next (const char* string);

#endif // PARSING_H_INCLUDED
