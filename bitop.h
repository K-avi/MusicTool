#ifndef BITOP_H_INCLUDED
#define BITOP_H

#include "types.h"

#define SET_NTH(bits, n) ( 1<<n | bits)
#define GET_NTH(bits,n) (1<<n & bits)

#endif
