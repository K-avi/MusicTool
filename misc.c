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

bool isprime(unsigned n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0){ 
            return false;
        }
    }
    return true;
}

unsigned nextprime( unsigned n){
  if( isprime(n+1) ) return n+1;
  else return(nextprime(n+1));
}