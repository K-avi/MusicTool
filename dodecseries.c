#include "dodecseries.h"
#include "types.h"
#include <stdio.h>


#define ISFULL_SERIE(serie) (((serie)>>44) & 0xD)

bool isvalid_serie(S_DODEC serie){
    
    return 1;
}


S_DODEC init_dodec(){
    S_DODEC ret= 0;
    for (CPT i=0; i<12; i++){
        ret=ret | 0xD <<(4*i);
    }
    return ret;
}

bool note_in_dodec( S_DODEC serie, NOTE note){
    //returns true if a note is in a dodec serie; false otherwise
    //if(!isvalid_serie(serie)) return 0;
    BITS mask= 0xF;

    for (CPT i=0; i<12; i++){
        if( (mask & (serie >> (4*i))) == note ) return 1; 
    }
    return 0;
}

S_DODEC add_to_dodec( S_DODEC serie, NOTE note){
    //adds a note to a dodec serie on the first empty index if it's not full
    if(note > 12 ) return serie;
   // if(serie & DODEC_ERRFLAG) return serie;
    //if (ISFULL_SERIE(serie)) {//maybe the number of zeros is wrong 
        return serie;
    //}


    CPT i=0;
    if(!note_in_dodec(serie, note)){
        while( (((serie>>4*i) & (0xF)) != 0xD )&& i<12) i++;
        printf("%d\n",i);
        if(i==12) return serie;
        else return (serie  & ~(0xF<<4*i)) | (note << 4*i);
    }
    return serie;
}

S_DODEC add_rand_to_dodec( S_DODEC serie){

    if(ISFULL_SERIE(serie)) return serie;

    NOTE note = rand()%12; 
    while(note_in_dodec(serie,  note)) note=rand()%12;

    return add_to_dodec(serie, note);
}

S_DODEC generate_serie(){
    S_DODEC ret= init_dodec();
    for(CPT i=0; i<12; i++){
        
        ret=add_rand_to_dodec(ret);
    }
    return ret;
}


void print_serie(S_DODEC serie){

    printf("{ ");
    for( CPT cpt=0; cpt <12; cpt ++){
        printf("%llu ",  (serie>> (4*cpt))& 0xF);
    }
    printf(" }");
}
S_DODEC inverse_serie(S_DODEC serie, INDEX inversion){

    return 0;
}

S_DODEC retrograde_serie (S_DODEC serie, INDEX inversion){
    return 0;
}

S_DODEC * serie_to_12tmat( S_DODEC serie){

    return NULL;
}



