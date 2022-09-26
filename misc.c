#include "misc.h"


int modulo_euclidean(int a, int b) { //returns a modulo b
  int m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}
