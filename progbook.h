#ifndef PROGBOOK_H 
#define PROGBOOK_H

#include "types.h"
#include <stdlib.h>

extern unsigned char init_book( PROGBOOK *pbook, size_t init_size);

extern unsigned char realloc_book( PROGBOOK* pbook , size_t realloc_size);

extern unsigned char entry_in_book( PROGBOOK * pbook, BOOKENTRY entry);

extern unsigned char add_entry (PROGBOOK * pbook, BOOKENTRY entry);

extern void free_book(PROGBOOK* pbook);

extern BOOKENTRY chprog_to_bookentry (S_CHPROG* prog);

extern void print_book_entry(BOOKENTRY entry);

extern BOOK_LENGTH_TABLE * proggbook_to_length_table( PROGBOOK* progbook);

extern void free_book_table( BOOK_LENGTH_TABLE* table); 

extern void print_progbook( PROGBOOK* book);
extern void print_book_lengthtable(BOOK_LENGTH_TABLE* table);

extern BOOK_LENGTH_TABLE* progbook_constrained_to_book_length( PROGBOOK* progbook, PITCH_CLASS_SET pcs);

extern S_DEGREE_PROG* build_deg_prog_from_deg_array( BOOK_LENGTH_TABLE * table, LENGTH proglength );

extern void print_degree_prog( S_DEGREE_PROG* degprog);

extern S_TRIAD_PROG * degree_prog_to_triad_prog( S_DEGREE_PROG * prog, S_SCALE scale);
extern S_CHPROG * degree_prog_to_chprog( S_DEGREE_PROG * prog, S_SCALE scale); 
#ifdef DEBUG 
#endif

#endif