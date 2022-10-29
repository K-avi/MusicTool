#ifndef BITOP_H_INCLUDED
#define BITOP_H

#include "types.h"

#define SCALE_BITS 16
#define SET_NTH(bits, n) ( 1<<n | bits)
#define GET_NTH(bits,n) (1 & bits>>n)
#define POP_BIT(bits, n) (1<<n ^ bits)

#define ROTATE_LEFT(bits, n, nb_bits) (bits << n)|(bits >> (nb_bits - n)) //rotates "bits" by n if bits size is nb_bits
#define ROTATE_RIGHT(bits, n, nb_bits) (bits >> n)|(bits << (nb_bits - n))

#define FULLSCALE 2047 //value of a fullscale as a ushort
#define MAXLENGTH 12 //max length of a scale 

#endif
