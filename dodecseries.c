#include "dodecseries.h"
#include "bitop.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>



bool isvalid_serie(S_DODEC serie){
    
    unsigned short seriecheck=0;
    NOTE note= 0 ,notenum=0;
    
    for (CPT i=0; i<12; i++){

        if( (serie >> (4*i) & 0xF )== 0xD ) return 0; //case if serie isn't full.

        note= serie >> (4*i) & 0xF;
        seriecheck=  POP_BIT(seriecheck, note);
        
    }
    return (seriecheck==0xFFF);
}




bool note_in_dodec( S_DODEC serie, NOTE note){
    //returns true if a note is in a dodec serie; false otherwise
    if(note > 11) return 0;

    for (CPT i=0; i<12; i++){
        if( note == ((serie >> 4*i) & 0xF)) return 1;
    }
    return 0;
 
}

S_DODEC add_to_dodec( S_DODEC serie, NOTE note){ //doesnt work
    //adds a note to a dodec serie on the first empty index if it's not full
    CPT i=0;
    while( ( ((serie >> (4*i)) & 0xF)!=0xD )&& i<12) {
        
        print_serie(serie);
        i++;
    }
    printf("%llu %d\n",((serie >> (4*i)) & 0xF) ,i  );
    if(i==12) return serie;
    serie= (S_DODEC) (((S_DODEC) serie & (S_DODEC) ~((0xF)<<(S_DODEC) (4*i))) | (S_DODEC) ((S_DODEC) note << (S_DODEC) 4*i) );
    return serie;
}


S_DODEC shuffle_once( S_DODEC seed, INDEX i1, INDEX i2){
   
    if(! (i1<12) & (i2<12)) return seed;

    S_DODEC value = ( (seed >> (4*i1)) ^ (seed >> (4*i2))) & 0xF;
    S_DODEC shuffler= (value<<(4*i1)) | (value << (4*i2));

    return seed ^ shuffler;
}
S_DODEC shuffle_serie(S_DODEC seed, u_long num){

    INDEX i1=rand()%12, i2=rand()%12;
    while(i1==i2) i2=rand()%12;

    S_DODEC ret= seed;

    for (u_long i=0; i<num; i++ ){
        ret=shuffle_once(ret, i1,  i2);
        i1=rand()%12; 
        i2=rand()%12;
        while(i1==i2) i2=rand()%12;
    }
    return ret;
}


void print_serie(S_DODEC serie){

    printf("{ ");
    for( CPT cpt=0; cpt <12; cpt ++){
        printf("%llu ",  (serie>> (4*cpt))& 0xF);
    }
    printf(" }\n");
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



