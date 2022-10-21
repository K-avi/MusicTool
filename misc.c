#include "misc.h"
#include <stdlib.h>

int modulo_euclidean(int a, int b) { //returns a modulo b
  int m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}

char * set_to_num( char * str){
  //returns a pointer to the first integer character in a given sring
  if(str == NULL) return NULL;
  int i=0;
  while(str[i]!='\0'){
    if(str[i]>='0' && str[i]<='9'){

      return &str[i];
    }
    i++;
  }
  return NULL;
}
