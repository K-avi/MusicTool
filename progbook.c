#include <stdlib.h>
#include "chordgen.h"
#include "progbook.h"
#include "types.h"
#include "globals.h"
#include "triadgen.h"
#include "triadprint.h"
#include "scalegen.h"
#include <stdio.h>
#include <string.h>



unsigned char init_book( PROGBOOK *pbook){

    //need to define error messages of init; 
    /*
    initialises a PROGBOOK by :
    allocating it memory;
    setting its  entries to 0 
    setting its maxentry value to _booksize_default 
    n allocating _booksize_default slots for the progs it can contain
    */
    if(!pbook) return BOOK_INIT_INVALID_CALL;

    pbook->nbentries=0;
    pbook->maxentries=_booksize_default;

    pbook->book=malloc(_booksize_default* sizeof(BOOKENTRY));
    if(!pbook->book ) return 1;
    return 0;
}//tested; works
unsigned char realloc_book( PROGBOOK* pbook){
    //modify return type to handle errors

    if(!pbook) return BOOK_REALLOC_NULLBOOK_ERR;
    if(! (pbook->maxentries== pbook->nbentries))  return BOOK_REALLOC_INVALID_CALL;
    
    BOOKENTRY* tmpbook= pbook->book;

    pbook->book=realloc(pbook->book, (pbook->maxentries+_book_realloc) * sizeof(unsigned long long));
    if(! pbook->book) { //handles realloc problem
        pbook->book=tmpbook; 
        printf("couldn't allocate more memory; please try again");
        return BOOK_REALLOC_FAILURE ;
    }else {
      //  memcpy(pbook->book, tmpbook, pbook->maxentries*sizeof( BOOKENTRY));
        pbook->maxentries+=_book_realloc;
        //free(tmpbook);
        return BOOK_REALLOC_SUCCES ;
    }
    return BOOK_REALLOC_GENERIC_ERR;
}//kinda tested; seems to work

unsigned char entry_in_book( PROGBOOK * pbook, BOOKENTRY entry){
//error messages r placeholder
/*
checks if an entry is in the progbook returns 0 if 
*/
    if(! (pbook && entry)) return 1;
    if(!pbook->book) return 2;

    for (CPT cpt= 0; cpt <pbook->nbentries; cpt++){
        if(pbook->book[cpt]== entry){
            return 0;
        }
    }
    return 3;
}//not tested 



unsigned char add_entry (PROGBOOK * pbook, BOOKENTRY entry){
    
    //error handling; error values r temporary n will be redefined later
    if(!pbook) return 1;
    if(!pbook->book) return 1;
    if(entry_in_book(pbook, entry)) return 2;

    if(pbook->maxentries==pbook->nbentries) realloc_book(pbook); //handles realloc
    pbook->book[pbook->nbentries+1]=entry;
    pbook->nbentries++;
    return 0;
}//tested; works

void free_book(PROGBOOK* pbook){
    if(!pbook) return ;
    free(pbook->book); 
    free(pbook);
}//tested 



PITCH_CLASS_SET chprog_degs_to_pcs_relev_deg(S_CHPROG *prog){
    /*
    returns the PCS containing the degrees of a chord. This isn't the same as 
    returning the pcs containing the PCS containing every note of the prog. 
    What this does is that it only includes the degrees w/o caring about which triad
    /extensions the chord has.
    */
    if(!prog) return 0;
    if(!prog->chprog) return 0;
    PITCH_CLASS_SET ret=0;
    for (CPT i=0; i<prog->length; i++){
        ret|= 1<<(prog->chprog[i]& 0xF); //retrieves degree n turns it into a PCS element.
    }
    return ret;
}//usefull when checking if a prog is in the saved book; not tested  


PITCH_CLASS_SET triad_degs_to_pcs_relev_deg(S_TRIAD_PROG *prog){
    /*
    returns the PCS containing the degrees of a chord. This isn't the same as 
    returning the pcs containing the PCS containing every note of the prog. 
    What this does is that it only includes the degrees w/o caring about which triad
    /extensions the chord has.
    */
    if(!prog) return 0;
    if(!prog->chord_prog) return 0;
    PITCH_CLASS_SET ret=0;
    for (CPT i=0; i<prog->length; i++){
        ret|= 1<<(prog->chord_prog[i]& 0xF); //retrieves degree n turns it into a PCS element.
    }
    return ret;
}//usefull when checking if a prog is in the saved book; not tested  

BOOKENTRY chprog_to_bookentry (S_CHPROG* prog){
    //turns a bookentry into a chord prog. Does so by assigning the first 12 bits of the prog to 
    //the PCS of the bookentry n then adds each element of the prog into the compacted array.
    //if a prog's length is greater than 12; will add it's first 12 elements to the bookentry bc 
    //max length of progs in book is 12.
    if(!prog) return 0;
    if(!prog->chprog) return 0;
    BOOKENTRY ret= 0;
    LENGTH length= prog->length<=12 ? prog->length : 12; //maxlength of progs in books is 12.
    PITCH_CLASS_SET ret_pcs=0;
    unsigned long long ret_prog=0;
    DEGREES_BITS degree=0;
    for(CPT i=0; i<length; i++){

        degree=prog->chprog[i]& 0xF;
        
        ret_pcs|= 1<<(degree); //retrieves degree n turns it into a PCS element.

        ret_prog|=  ( (unsigned long long )( degree+1)<<(4*i)); //sets element in the compacted array
        
    }
    ret= ret_pcs | (length<<12) |(ret_prog<<16);
 
    return ret; 
}//tested

BOOKENTRY triad_to_bookentry( S_TRIAD_PROG* prog){
    //works exactly the same as chprog_to_bookentry.


   if(!prog) return 0;
    if(!prog->chord_prog) return 0;
    BOOKENTRY ret= 0;
    LENGTH length= prog->length<=12 ? prog->length : 12; //maxlength of progs in books is 13.
    PITCH_CLASS_SET ret_pcs=0;
    unsigned long long ret_prog=0;
    DEGREES_BITS degree=0;
    for(CPT i=0; i<length; i++){

        degree=prog->chord_prog[i]& 0xF;
        
        ret_pcs|= 1<<(degree); //retrieves degree n turns it into a PCS element.

        ret_prog|= ( (unsigned long long ) ( degree+1)<<(4*i)); //sets element in the compacted array
        
    }
    ret= ret_pcs | (length<<12) | (ret_prog<<16);
   
    return ret; 
}//not tested but is the same as chprog_to_bookentry so it should be ok


void print_book_entry(BOOKENTRY entry){
    printf("PCS of the entry is: ");
    print_scale( (entry>>1)& 0x7FF);
    printf("and the prog is:\n");
    printf("[ ");
    DEGREES_BITS curdeg=0;
    LENGTH length= (entry>>12) & 0xF;
    for(CPT i=0; i<length; i++){
        
        curdeg=(entry>>(4*i+16)) & 0xF ;
        
       
        if(curdeg==0){
             break;
        }
       
       if(i!=length-1){
        printf("%s, ", bits_deg_to_str(curdeg-1) );
       }else{
        printf("%s ", bits_deg_to_str(curdeg-1) );
       }
    }
    printf("]\n");
}//tested ; works 


S_BOOK_INDEX_ARRAY * generation_indexes( PROGBOOK* progbook, PITCH_CLASS_SET pcs){
    /*
    returns the array of indexes of the progs in a book that a pcs passed as argument contains. 
    This is done in O(n*n) even though it could be easily done in O(n) cuz I wanna allocate the exact amount 
    of memory needed to store the short array. 

    The problem I have w the O(n) implementation is that I don't see how not to allocate progbook->nbentries to ret value. 
    The design philosophy of MusicTool kinda is to be as compact as possible  
    so I chose compactness over performance 

    It might be a shitty decision n I'm hesitant about this but I'm gonna leave it this way for now. 
    I might go back on this at some point though
    */
    if(!(progbook && pcs)) return NULL;
    if(!progbook->book) return NULL;

    LENGTH ret_length=0;
    unsigned short* ret_array=NULL;
    for (CPT i=0; i<progbook->nbentries; i++){
        if( (pcs & progbook->book[i] & 0xFFF) == (progbook->book[i] & 0xFFF)) ++ret_length ;
        //0xFFF is mask for first 12 bits cuz it's where the PCS is n so on
    }

    if(!ret_length) return NULL; 

    ret_array=malloc(ret_length* sizeof(unsigned short));

    INDEX ret_i=0;
    for (CPT i=0; i<progbook->nbentries; i++){
        if( (pcs & progbook->book[i] & 0xFFF) == (progbook->book[i] & 0xFFF)){
            ret_array[ret_i++]= i;
        }
    }

    S_BOOK_INDEX_ARRAY *ret= malloc(sizeof(S_BOOK_INDEX_ARRAY));
    ret->indexes=ret_array;
    ret->length=ret_length; 
    return ret;
}//not tested


S_DEGREE_PROG* build_deg_prog_from_deg_array( S_BOOK_INDEX_ARRAY* relevant_indexes, PROGBOOK* progbook, LENGTH length ){
    /*
    builds a degree prog of the length passed as argument usinf the relevant indexes in a progbook. 

    The fact that any prog of length n CAN be generated with this is assumed?? 
    returns NULL if error/ problem 
    */

    if(!(relevant_indexes && progbook && length)) return NULL;
    if(!(relevant_indexes->indexes && progbook->book)) return NULL;

    return NULL; 
}