#ifndef PROGBOOK_H 
#define PROGBOOK_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>

extern unsigned char init_book( PROGBOOK *pbook, size_t init_size);

extern unsigned char realloc_book( PROGBOOK* pbook , size_t realloc_size);

extern unsigned char entry_in_book( PROGBOOK * pbook, BOOKENTRY entry);

extern unsigned char add_entry (PROGBOOK * pbook, BOOKENTRY entry);

extern void free_book(PROGBOOK* pbook);

extern BOOKENTRY chprog_to_bookentry (S_CHPROG* prog);


extern BOOK_LENGTH_TABLE * proggbook_to_length_table( PROGBOOK* progbook);

extern void free_book_table( BOOK_LENGTH_TABLE* table); 

extern void print_progbook( PROGBOOK* book);
extern void print_book_lengthtable(BOOK_LENGTH_TABLE* table);

extern BOOK_LENGTH_TABLE* progbook_constrained_to_book_length( PROGBOOK* progbook, PITCH_CLASS_SET pcs);

extern BOOKENTRY degprog_to_bookentry( S_DEGREE_PROG* prog);

extern void fprint_book_entry(FILE * f, BOOKENTRY entry);

extern void fprint_progbook( FILE * f, PROGBOOK* pbook);

extern void free_degree_prog(S_DEGREE_PROG* degprog);

#ifdef DEBUG 


#endif


#endif