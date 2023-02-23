#ifndef COHERAND_H
#define COHERAND_H


#include "types.h"


extern S_DEGREE_PROG* build_deg_prog_from_deg_array( BOOK_LENGTH_TABLE * table, LENGTH proglength );

extern void print_degree_prog( S_DEGREE_PROG* degprog);

extern S_TRIAD_PROG * degree_prog_to_triad_prog( S_DEGREE_PROG * prog, S_SCALE scale);
extern S_CHPROG * degree_prog_to_chprog( S_DEGREE_PROG * prog, S_SCALE scale); 



extern void pop_prog_extensions( S_CHPROG* chprog, CPT num_ext);
extern void pop_prog_extensions_rand( S_CHPROG* chprog);

extern void set_options( char * str, unsigned char mode , char* extnum, char* extmax, S_SCALE *scl, LENGTH *length , LENGTH * scllen);

#endif