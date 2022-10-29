#include "types.h"
#include "scalegen.h"
#include "bitop.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


int cmpfunc (const void * a, const void * b) { //comparative function to be used w qsort(); maybe useless

   return ( *(NOTE*)a - *(NOTE*)b );
}

bool IsValidNote( NOTE note){ //checks wether a note is valid or not (valid meaning that it's value is between 0 and 11
    return (note >=1 && note <=11);
}

bool IsInScale( S_SCALE scale, NOTE note){ //asserts wether a note is already in a scale or not

    if (note==0) return true; 

    else return ( GET_NTH(scale, (note-1) ));

}

void add_note(S_SCALE* scale, NOTE note){ //adds a note to a scale


    if(!IsValidNote(note)) return;

    if(!IsInScale(*scale, note)){
        *scale= SET_NTH(*scale, (note-1)) ;
    }

};

void add_rand_note(S_SCALE* scale){ //adds a random note to a scale

    if(*scale >= FULLSCALE) return;
    else{
        NOTE note= rand()%12;
        while(IsInScale(*scale,  note)){
            note=rand()%12;
        }
        add_note(scale, note);
    }

}



LENGTH get_length( S_SCALE scale){
    
    if(scale==0 || scale <<5==0) return 1;
    else{
        LENGTH n=0;

        for(CPT i=0; i<11; i++){
            if( GET_NTH(scale, i)) n++;
        }
        return n+1;
    }
}

LENGTH get_length_kerni( S_SCALE scale){
    if(scale==0 || scale <<5==0) return 1;
    else{
        LENGTH cnt=0; 
        while(scale!=0){
            cnt++;
            scale=scale & scale-1;
        }
        return cnt+1;
    }   
    
}


S_SCALE* generate_ran_scale(LENGTH length){ //generates a random scale of 'length' notes

    S_SCALE * ret=malloc(sizeof( S_SCALE));
    
    int i;
    for(i=0; i<length-1; i++){
        add_rand_note(ret);
    }
   
    return ret;

}


void set_scale(S_SCALE* scale, NOTE* array, LENGTH length ){//sets a scale to the values of an array; 
    //maybe useless
    for(CPT i=0; i<length; i++){
        add_note(scale, array[i]);
    }
}

S_SCALE * make_scale( NOTE *array, LENGTH length){ //generates a scale from an array + a length passed as argument

    S_SCALE* ret = malloc(sizeof(S_SCALE));
    set_scale(ret, array, length);
    return ret;
}

void print_scale( const S_SCALE scale){ //prints the notes of a scale and it's length in a nice way :)


    int i;
    printf("\n{ 0 ");
    for(CPT i=0; i<11; i++){
        if(GET_NTH(scale, i)) printf("%d ", i+1);
    }

    printf("}\nthe scale's length is %d\n", get_length_kerni(scale));
}


/*

void sort_scale(S_SCALE * scale){ //sorts a scale w quicksort; could have been a macro tbh
//useless

    qsort( &(scale->scale[0]), scale->length, sizeof(NOTE), cmpfunc );
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
*/