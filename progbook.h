#ifndef PROGBOOK_H 
#define PROGBOOK_H

#include "types.h"


extern unsigned char init_book( PROGBOOK *pbook);

extern unsigned char realloc_book( PROGBOOK* pbook);

extern unsigned char entry_in_book( PROGBOOK * pbook, BOOKENTRY entry);

extern unsigned char add_entry (PROGBOOK * pbook, BOOKENTRY entry);

extern void free_book(PROGBOOK* pbook);

extern BOOKENTRY chprog_to_bookentry (S_CHPROG* prog);

extern void print_book_entry(BOOKENTRY entry);

#ifdef DEBUG 
#endif

#endif