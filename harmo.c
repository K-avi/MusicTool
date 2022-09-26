#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "harmo.h"
#include "scalegen.h"
#include "init.h"
#include "misc.h"
//#include "scalegen.h"


S_SCALE* generate_nth_mode(S_SCALE *scale, LENGTH mode){ //generates and returns the scale corresponding to the n th mode of the scale. returns the scale if the mode isn't recognised as valid


    if(mode<=scale->length && mode>0){
            S_SCALE *ret;
            ret=malloc(sizeof(S_SCALE));
            partial_init_scale(ret);
            int i;
            for(i=0; i<scale->length; i++){
                ret->scale[i]=  modulo_euclidean((scale->scale[i]-scale->scale[mode-1]),12);

            }
            ret->length=scale->length;
            sort_scale(ret);
            return ret;

    }else if(mode ==0){
        return scale;
    }else{
        printf("\n%d\n",mode);
        printf("\nmode not valid, length of scale is %d ; scale is returned\n", scale->length);
        return scale;
    }
}

S_MODES * generate_modes( S_SCALE *scale){ //generates and return all of the modes of a scale given this scale

    S_MODES* rep;
    rep=malloc(sizeof(S_MODES));
    S_SCALE *tmp;
    tmp= malloc(sizeof(S_SCALE));

    partial_init_modes(rep);

    int i,j, count=1;
    for(i=0; i<=scale->length-1; i++){ //confused as to why that works might cause bugs

            tmp=generate_nth_mode(scale, count++);
            for(j=0; j<scale->length; j++){
                rep->scale[i][j]=tmp->scale[j];
            }
    }
    rep->length=scale->length;
    free(tmp);
    return rep;

}

//need to do the parsing function for modes



void print_modes(S_MODES * modes){

    int i;
    for(i=0; i<modes->length; i++){
        print_array(modes->scale[i], modes->length);
    }
}
