#include "types.h"
#include "scalegen.h"
#include "init.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


int cmpfunc (const void * a, const void * b) { //comparative function to be used w qsort()

   return ( *(NOTE*)a - *(NOTE*)b );
}

bool IsValidNote( NOTE note){ //checks wether a note is valid or not (valid meaning that it's value is between 0 and 11


    return (note >=0 && note <=11);
}

bool IsInScale( S_SCALE* scale, NOTE note){ //asserts wether a note is already in a scale or not



    int i;
    for(i=0; i<scale->length; i++){
        if(note ==scale->scale[i]){
            return true;
        }
    }
    return false;

}

void add_note(S_SCALE* scale, NOTE note){ //adds a note to a scale


    if(!IsValidNote(note)) return;

    if(!IsInScale(scale, note)){
        scale->scale[scale->length++]= note;
    }

};

void add_rand_note(S_SCALE* scale){ //adds a random note to a scale

    NOTE note= rand()%12;
    int comp=scale->length;
    while(comp == scale->length){
        add_note(scale, note);
        note= rand()%12;
    }

}

void sort_scale(S_SCALE * scale){ //sorts a scale w quicksort; could have been a macro tbh

    qsort( &(scale->scale[0]), scale->length, sizeof(NOTE), cmpfunc );
}

S_SCALE* generate_ran_scale(LENGTH length){ //generates a random scale of 'length' notes

    S_SCALE * ret;
    ret=malloc(sizeof(S_SCALE));
    init_scale(ret);
    int i;
    for(i=0; i<length-1; i++){
        add_rand_note(ret);
    }
    sort_scale(ret);
    return ret;

}


void set_scale( S_SCALE* scale, NOTE *arr, LENGTH length){ //sets a scale to the array passed as argument n sets it's length to the arrays length

    partial_init_scale(scale);
    int i;
    for(i=0; i<length; i++){
        scale->scale[i]=arr[i];
    }
    scale->length=length;
}



void print_scale( const S_SCALE *scale){ //prints the notes of a scale and it's length in a nice way :)


    int i;
    printf("\n{");
    for(i=0; i<scale->length; i++){
        printf("%d ", scale->scale[i]);
    }

    printf("}\n");
    printf("the scale's length is %d\n", scale->length);
}

void print_array( NOTE *scale, LENGTH length){ //prints the notes of a scale passed as an array w the length


    int i;
    printf("\n{");
    for(i=0; i<length; i++){
        printf("%d ", scale[i]);
    }

    printf("}\n");
    printf("the scale's length is %d\n", length);

}

S_SCALE * make_scale( NOTE *scale, LENGTH length){ //generates a scale from an array + a length passed as argument

    S_SCALE* ret = malloc(sizeof(S_SCALE));

    set_scale( ret, scale, length);

    return ret;

}
