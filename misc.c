#include "types.h"
#include "bitop.h"
#include "misc.h"
#include <stdio.h>
#include <sys/types.h>


#ifdef WIN32 
#include <string.h> 
//from strndup.c
char *
strndup (const char *s, size_t n)
{
  size_t len = strnlen (s, n);
  char *new = (char *) malloc (len + 1);
  if (new == NULL)
    return NULL;
  new[len] = '\0';
  return (char *) memcpy (new, s, len);
}
#endif


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

INDEX nth_bit_pos( unsigned  long long bits, INDEX index){
  //returns the shift of the nth bits in bits
  if( (!bits)|| (!index)) return 0;

  CPT cpt=0; 
  INDEX ret= 0; 

  for( CPT i=0; i<32; i++){
    if( (1<<i) & bits) {
      ret=i;
      cpt++;
    }
    if(cpt==index) break;
  }
  
  return ret;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}