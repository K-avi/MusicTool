#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "types.h"

extern LENGTH parse_scale_length(const char* string);
extern S_SCALE  parse_scale( char * string);
extern char * set_to_beginning( char* str);

extern SIGNED_LENGTH parse_index(const char* string);
extern SIGNED_LENGTH parse_next (const char* string);

extern CHORD str_to_chord( char * str);
extern S_CHORD_PROG* str_to_chord_prog( char* str);
extern unsigned char next_not_blank_comment( char *str, char chr);


/*  test only*/
extern CHORD word_bits_to_chord (WORD_BITS word);
extern WORD_BITS str_to_wordbits( char * str);

extern char ** chprog_str_to_tab_chord_str( char* str, LENGTH length);

extern void free_str_tab(char ** str_tab, LENGTH length);



#endif // PARSING_H_INCLUDED
