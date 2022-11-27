#include "types.h"
#include "bitop.h"
#include "misc.h"


LENGTH count_bits( unsigned bits){ 
//counts the number of bits set in a number
  unsigned n=0, ret=0;
  while( bits){
    if( (1<<n) & bits){bits=POP_BIT(bits, n); ret++;}
    n++;
  }
  return ret;
}//should be moved to somewhere else; 