#ifndef MISC_H
#define MISC_H

#include "types.h"
extern LENGTH count_bits( unsigned bits);
extern unsigned nextprime(unsigned n);

extern INDEX nth_bit_pos( unsigned bits, INDEX index);

extern int mod(int a, int b);

#endif