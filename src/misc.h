#ifndef MISC_H
#define MISC_H

#include "types.h"
#include <stdlib.h>
extern LENGTH count_bits( unsigned bits);
extern unsigned nextprime(unsigned n);

extern INDEX nth_bit_pos( unsigned long long bits, INDEX index);

extern int mod(int a, int b);
#ifdef WIN32 

char * strndup( const char * str, size_t chars);
#endif

#endif