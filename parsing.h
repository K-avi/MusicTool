#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "types.h"

extern LENGTH parse_scale_length(const char* string);
extern S_SCALE  parse_scale( char * string);
extern char * set_to_first_bracket( char* str);

extern SIGNED_LENGTH parse_index(const char* string);
extern SIGNED_LENGTH parse_next (const char* string);

extern TRIAD str_to_triad( char * str, unsigned char mode);
extern S_TRIAD_PROG* str_to_triad_prog( char* str);
extern unsigned char next_not_blank_comment( char *str, char chr);
extern char* file_to_string( char* str);
extern char* syntax_error_flag_to_str(SYNTAX_ERROR flag );

extern S_CHPROG* str_to_chprog( char* str);


#ifdef DEBUG
extern TRIAD word_bits_to_chord (WORD_BITS word);
extern WORD_BITS str_to_wordbits( char * str, unsigned char mode);

extern char ** chprog_str_to_tab_chord_str( char* str, LENGTH length, char separator);

extern void free_str_tab(char ** str_tab, LENGTH length);

extern CHORD str_to_chord( char * str);
#endif


#endif // PARSING_H_INCLUDED
