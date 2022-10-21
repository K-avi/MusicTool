#include <stdlib.h>
#include "chordgen.h"
#include "types.h"
#include "globals.h"
#include "bitop.h"


CHORD_BITS triads_at_fund (S_SCALE * scale){//returns the triads you can generate on the first degree of a scale

  if(scale==NULL) return 0;
  CHORD_BITS ret=0;
  for(LENGTH i=0; i<scale->length; i++){
    if(scale->scale[i]==3) ret=SET_NTH(ret,0);
    else if(scale->scale[i]==4) ret=SET_NTH(ret,1);
    else if(scale->scale[i]==6) ret=SET_NTH(ret,2);
    else if(scale->scale[i]==7) ret=SET_NTH(ret,3);
    else if(scale->scale[i]==8) ret=SET_NTH(ret,4);
  }
    return ret;
}

CHORD_BITS * triads_from_scale( S_SCALE* scale){// returns the triads you can generate from a scale

//not done yet
  CHORD_BITS* ret= malloc(scale->legnth*sizeof(CHORD_BITS));
  for(LENGTH i=0; i<scale->length; i++){
    ret[i]=triads_at_fund(scale->scale[i]);
  }
  return ret
}
