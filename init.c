#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



void init_scale( S_SCALE * scale ){ //initializes the length of a scale to 1; sets it's first note to the fundamental and fills it with the value 13 as placeholder


    int i;
    for(i=1; i<12; i++){

        scale->scale[i]= 13;

    }

    scale->length=1;
    scale->scale[0]=0;
}

void partial_init_scale( S_SCALE*scale){ //initialises the length of the scale to 0; fills it with the value 13 as a placeholder


    int i;
    for(i=0; i<12; i++){
        scale->scale[i]= 13;

    }
    scale->length=0;

}

void init_modes(S_MODES * modes){ //initialises the length of the structure to 1; set the first note of every scale to 0 and fills the rest with the value 13 as placeholder

    int i, j;

    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
                modes->scale[i][j]=(j==0)? 0: 13;
        }
    }
    modes->length=1;
}

void partial_init_modes( S_MODES * modes){ ////initialises the length of the structure to 0; fills it with the value 13 as a placeholder

    int i, j;

    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
            modes->scale[i][j]=13;
        }
    }
    modes->length=0;
}
