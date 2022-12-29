#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "types.h"

extern LENGTH parse_scale_length(const char* string);
extern S_SCALE  parse_scale( char * string);
extern char * set_to_beginning( char* str);

extern SIGNED_LENGTH parse_index(const char* string);
extern SIGNED_LENGTH parse_next (const char* string);


/*  test only*/
extern CHORD word_bits_to_chord (WORD_BITS word);
extern WORD_BITS str_to_wordbits( char * str);



#endif // PARSING_H_INCLUDED
