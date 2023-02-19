#include <stddef.h>
#include "chordgen.h"
#include "misc.h"
#include "progbook.h"
#include "rand.h"
#include "types.h"
#include "globals.h"
#include "triadgen.h"
#include "triadprint.h"
#include "scalegen.h"
#include "harmo.h"
#include "bitop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
PROGBOOK operations 
*/

//chord macros
#define GETDEGREES(chord) ((chord) & 0xF)
#define GETEXTENSIONS(chord) ( ((chord) & ~0xF) >>4)

#define ENTRY_GETENTRY(entry) ((entry) >> 16 )
#define ENTRY_GETPCS(entry)     ((entry) & 0x7FF)
#define ENTRY_GETLENGTH(entry) (((entry)>>12) & 0xF)


unsigned char init_book( PROGBOOK *pbook, size_t init_size ){

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
    pbook->maxentries= init_size;

    pbook->book=malloc( init_size* sizeof(BOOKENTRY));
    if(!pbook->book ) return 1;
    return 0;
}//tested; works


unsigned char realloc_book( PROGBOOK* pbook, size_t realloc_size){
    //modify return type to handle errors
    //need to be able to customize realloc size
    if(!pbook) return BOOK_REALLOC_NULLBOOK_ERR;
    if(! (pbook->maxentries== pbook->nbentries))  return BOOK_REALLOC_INVALID_CALL;
    
    BOOKENTRY* tmpbook= pbook->book;

    pbook->book=realloc(pbook->book, (pbook->maxentries+realloc_size) * sizeof(unsigned long long));
    if(! pbook->book) { //handles realloc problem
        pbook->book=tmpbook; 
        printf("couldn't allocate more memory; please try again");
        return BOOK_REALLOC_FAILURE ;
    }else {
      //  memcpy(pbook->book, tmpbook, pbook->maxentries*sizeof( BOOKENTRY));
        pbook->maxentries+=realloc_size;
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
    if(!entry_in_book(pbook, entry)) return 2;

    if(pbook->maxentries==pbook->nbentries) realloc_book(pbook, _book_realloc); //handles realloc
    pbook->book[pbook->nbentries++]=entry;
   // pbook->nbentries++;
    return 0;
}//tested; works

void free_book(PROGBOOK* pbook){
    if(!pbook) return ;
    free(pbook->book); 
    free(pbook);
}//tested 


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

        degree= GETDEGREES(prog->chprog[i]);
        
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

        degree=GETDEGREES(prog->chord_prog[i]);
        
        ret_pcs|= 1<<(degree); //retrieves degree n turns it into a PCS element.

        ret_prog|= ( (unsigned long long ) ( degree+1)<<(4*i)); //sets element in the compacted array
        
    }
    ret= ret_pcs | (length<<12) | (ret_prog<<16);
   
    return ret; 
}//not tested but is the same as chprog_to_bookentry so it should be ok


void print_book_entry(BOOKENTRY entry){
    printf("PCS of the entry is: ");
    print_scale( ENTRY_GETPCS(entry)>>1);
    printf("and the prog is:\n");
    printf("[ ");
    DEGREES_BITS curdeg=0;
    LENGTH length= ENTRY_GETLENGTH(entry);
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



void print_progbook( PROGBOOK* book){
    if(!book) return; 
    if(! (book->book && book->nbentries)) return;

    for(CPT i=0; i<book->nbentries; i++){
        print_book_entry(book->book[i]);
    }
}

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
//Might be useless bc book_length_table is way cooler tbh



/*
book length table functions
*/

BOOK_LENGTH_TABLE* init_length_table(){
    /*
    creates a book length table ; by allocating 
    */

    BOOK_LENGTH_TABLE * ret= malloc(sizeof( BOOK_LENGTH_TABLE));
    ret->nbentries=0;
    ret->book_arrays= calloc( sizeof(PROGBOOK*), 12);

    return ret;
}


BOOK_LENGTH_TABLE* progbook_constrained_to_book_length( PROGBOOK* progbook, PITCH_CLASS_SET pcs){
    /*
    creates a BOOK_LENGTH_TABLE containing every progbook BOOKENTRY that u can generate 
    w the pcs passed as argument
    */
    if(! (progbook && pcs)) return NULL;
    if(!progbook->book) return init_length_table();

    BOOKENTRY * bookentries= progbook->book;

    BOOK_LENGTH_TABLE* ret= init_length_table();
    LENGTH length=0;

    for(unsigned short i=0; i<progbook->nbentries; i++){

         if( (pcs & progbook->book[i] & 0xFFF) == (progbook->book[i] & 0xFFF)){
            
            length= (bookentries[i]>>12) & 0xF; //retrieves length from bookentry

            if(! ret->book_arrays[length-1]){
               // printf("length is %d\n", length);
                ret->book_arrays[length-1]= malloc(sizeof(PROGBOOK));
                init_book(ret->book_arrays[length-1], _booksize_default);
            
            }else if( ret->book_arrays[length-1]->nbentries==ret->book_arrays[length-1]->maxentries){
                realloc_book(ret->book_arrays[length-1], _book_realloc_small); //i do not trust this tbh 
            }

            ret->book_arrays[length-1]->book[ret->book_arrays[length-1]->nbentries++]=bookentries[i];      
            ret->nbentries++;
        }
    }
    return ret;
}//not tested ; 
//return a sorted table length containing the progs u can generate w a given pcs. 
//makes some functions kinda useless.
//should customize dynamic array size allocation




BOOK_LENGTH_TABLE * proggbook_to_length_table( PROGBOOK* progbook){
    /* 
    converts a valid progbook to a valid length table; return NULL otherwise .
    */

    if(!progbook) return NULL;
    if(!progbook->book) return init_length_table();

    BOOK_LENGTH_TABLE * ret= init_length_table();
    BOOKENTRY * bookentries= progbook->book;
    LENGTH length=0;
    for (INDEX i=0; i<progbook->nbentries; i++){

        length= ENTRY_GETLENGTH(bookentries[i]);

        if(! ret->book_arrays[length-1]){
            printf("length is %d\n", length);
            ret->book_arrays[length-1]= malloc(sizeof(PROGBOOK));
            init_book(ret->book_arrays[length-1], _book_init_small);
           
        }else if( ret->book_arrays[length-1]->nbentries==ret->book_arrays[length-1]->maxentries){
            realloc_book(ret->book_arrays[length-1], _book_realloc_small); //i do not trust this tbh 
        }

        ret->book_arrays[length-1]->book[ret->book_arrays[length-1]->nbentries++]=bookentries[i];      
        ret->nbentries++;
    }
    return ret;
}// tested; should customise dynamic array size. 

void print_book_lengthtable (BOOK_LENGTH_TABLE* table){
    if(!table) return;
    if(!(table->book_arrays && table->nbentries)) return;
    
    for(CPT i=0; i<12; i++){
        //printf("%p\n", table->book_arrays[i]);
        if(table->book_arrays[i]){
            printf("prog of length %d are:\n", i+1 );
            print_progbook(table->book_arrays[i]);
        }
    }
}


void free_book_table( BOOK_LENGTH_TABLE* table){
    /* 
    yes.
    */
    if(!table){
        return ;
    }
    for ( CPT i=0; i<12; i++){
        free_book(table->book_arrays[i]);
    }
    free(table->book_arrays);
    free(table);
}//works