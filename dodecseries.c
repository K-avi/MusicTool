#include "dodecseries.h"
#include "bitop.h"
#include "scalegen.h"
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


////utility functions ///////////

bool isvalid_serie(S_DODEC serie){//returns true is a serie is full and has each number from 0 to eleven 
//exactly once in it .
    
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

S_DODEC add_to_dodec( S_DODEC serie, NOTE note){ //adds a note to a dodec serie passed as arg.
    //adds a note to a dodec serie on the first empty index if it's not full
    if(ISFULL_SERIE(serie)) return serie;
    if(note>11) return serie;
    S_DODEC i=0;
    S_DODEC ullnote= note;
    S_DODEC ullflag= 0xF;
    while( ( ((serie >> (4*i)) & 0xF)!=0xD )&& i<12) {
        i++;
    }
    if(i==12) return serie;
 
    serie=  (( serie &  ~((ullflag)<< (4*i))) |  ( ullnote <<  4*i) );
    return serie;
}


//////////////random generation functions////////

S_DODEC add_rand_dodec(S_DODEC serie){//adds a random note in a dodec serie ; doesn't check for max length
    
    NOTE note= rand()%12; 
    while(note_in_dodec(serie, note)) note=rand()%12;
    return add_to_dodec(serie,  note);
}
S_DODEC generate_serie(){//generates a random dodec serie 

    S_DODEC ret=INIT_DODEC;
    for(int i=0; i<12; i++){
        ret=add_rand_dodec(ret);
    }
    return ret;
}


S_DODEC shuffle_once( S_DODEC seed, INDEX i1, INDEX i2){//shuffles a serie passed as a seed at the indexes 1 n 2
   
    if(! (i1<12) & (i2<12)) return seed;

    S_DODEC value = ( (seed >> (4*i1)) ^ (seed >> (4*i2))) & 0xF;
    S_DODEC shuffler= (value<<(4*i1)) | (value << (4*i2));

    return seed ^ shuffler;
}
S_DODEC shuffle_serie(S_DODEC seed, u_long num){//randomly shuffles a serie passed as seed num times

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

///////// utility functions//////////

S_DODEC inverse_serie(S_DODEC serie){ //calculates I0 of a serie 

    S_DODEC ret=0; 
    NOTE root = (serie & 0xF); //? (serie & 0xF): 12;
    S_DODEC current=0;
    for(CPT i=0; i<12; i++){
        current= (serie >> (4*i)) & 0xF; 
        current = (((12- current)%12 + root)%12 +root) %12;
        ret|= (current)<<(4*i);
    }

    return ret;
    
}

S_DODEC retrograde_serie (S_DODEC serie) {//calculates R0 of a serie 
    S_DODEC ret= 0;
    S_DODEC current=0;
    for (CPT i=0; i<12; i++){
        current= (serie >> (4*i)) & 0xF;
        ret|=  (current<<( (11-i)*4 ));
    }
    return ret;

}
S_DODEC retrograde_inverse_serie(S_DODEC serie){// calculates RI0 of a serie
    return retrograde_serie(inverse_serie(serie));
}

S_DODEC first_prime(S_DODEC serie){//not relevant but needed to pass generic_dodec_dodec lol
    return serie;
}
S_DODEC nth_prime( S_DODEC serie, INDEX n ){ //calculates the nth prime form of a dodec serie
    S_DODEC ret=0; 
    S_DODEC currnum=0;

    for (CPT i=0; i< 12; i++){
        currnum= ( (serie >>(4*i)& 0xF)+n) %12;
        ret|= currnum << (4*i);
    }
    return ret;
}

S_DODEC nth_inv (S_DODEC serie, INDEX n){
    if(! (isvalid_serie(serie) && n<12)) return DODEC_ERRFLAG;
    return inverse_serie(nth_prime(serie, n));
}

S_DODEC nth_retrograde (S_DODEC serie, INDEX n){
    if(! (isvalid_serie(serie) && n<12)) return DODEC_ERRFLAG;
    return retrograde_serie(nth_prime(serie, n));
}

S_DODEC nth_retrograde_inverse( S_DODEC serie, INDEX n){
    if(! (isvalid_serie(serie) && n<12)) return DODEC_ERRFLAG;
    return retrograde_inverse_serie(nth_prime(serie, n));
}

S_DODEC * serie_to_12tmat( S_DODEC serie){

    S_DODEC *ret= malloc(12*sizeof(S_DODEC));
    NOTE root= serie & 0xF;
    S_DODEC inverse= inverse_serie(serie);
    //print_serie(inverse);
    ret[0]= serie;
    for (CPT i=1; i<12; i++){
        ret[i]= nth_prime(serie,   (12-(root - ((inverse>>(4*i)) & 0xF )))%12 );
    }
    return ret;
}


//stdio functions /////////////
void print_serie(S_DODEC serie){//prints a dodec serie

    printf("{ ");
    for( CPT cpt=0; cpt <12; cpt ++){
        printf("%llu ",  (serie>> (4*cpt))& 0xF);
    }
    printf(" }\n");
}

void print_serie_num(S_DODEC serie){//prints the num of a dodec serie
    for( CPT cpt=0; cpt <12; cpt ++)  printf("%llu ",  (serie>> (4*cpt))& 0xF); 

}

void print_12t_mat(S_DODEC* mat){//prints a 12tone mat to stdout
    if(!mat) return;
    // printf("  I0 I1 I2 I3 I4 I5 I6 I7 I8 I9 I10 I11  \n");
    for(CPT i=0; i<12; i++){
        //printf("P%d ",i); 
        print_serie_num(mat[i]);
       //printf(" R%d\n",i);
       printf("\n");
    }
    //printf("  RI0 RI1 RI2 RI3 RI4 RI5 RI6 RI7 RI8 RI9 RI10 RI11  \n");
}//need to add the lil indexes like I0 I1,....

S_DODEC parse_serie(char * str){//parses a str into a serie

    char * tmp=str;
    NOTE note=13;
    S_DODEC ret=INIT_DODEC;
    while(*tmp!= '\0'){
        if(isdigit(*tmp) ){
            note=atoi(tmp);
            ret=add_to_dodec(ret,  note);
            while(isdigit(*tmp)) tmp++;
            continue;
        }else tmp++;
    }
    if(isvalid_serie(ret)) return ret;

    return ret;

}
