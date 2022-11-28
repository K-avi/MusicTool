#include <stdio.h>
#include <stdlib.h>
#include "chordgen.h"
#include "harmo.h"
#include "globals.h"
#include "scalegen.h"
#include "types.h"
#include "misc.h"
#include "chordprog.h"
#include "harmo.h"
#include "chordpattern.h"

//////////////////// chord prog pattern identification: 




SIGNED_BOOL contains_pattern( S_SCALE scale, CHORD_DEGREES chord_degrees){//returns 1 if a scale contains triads at the degrees relev degrees n zero otherwise.

 SIGNED_BOOL ret=-1;

 for(CPT i=0; i<12; i++){
    if (ret==0) break;
    if ( (1<<i)& chord_degrees){
      if(i==0) ret= (triads_at_fund(scale)) ? 1 : 0 ; 
      
      else if( scale & (1<< (i-1)))  ret= (triads_at_fund(rot(scale, i))) ? 1 : 0 ; //no clue what this statement does
      
      else ret=0;
    } 
 }
  if(ret==-1) return 0;
  return  ret;
} //not sufficiently tested


//fucking awful ffs 

void add_book_entry(S_CHORD_BOOK chord_book, CHORD_DEGREES relev_deg, LENGTH length ){
    if(!chord_book) return;
    S_CHORD_ENTRY* new_entry=malloc(sizeof(S_CHORD_ENTRY));
    new_entry->length=length;
    new_entry->relev_deg=relev_deg;
    new_entry->next=NULL;

    unsigned id=0;

    S_CHORD_BOOK tmp= chord_book; 
    while(tmp){
        id=tmp->id;
        tmp=tmp->next;
    }
    new_entry->id=nextprime(id);
    tmp->next=new_entry;
}
void init_chord_book( S_CHORD_BOOK chord_book , CPT * nb_entries){//initialises the default chord book
//chord book is the book where the chord pattern recognised are stored.

  *nb_entries=10;
 
  chord_book= malloc(sizeof(S_CHORD_ENTRY));

  (chord_book)->length=3; //I IV V  progression
  (chord_book)->relev_deg=0xA1;
  chord_book->id=2;

  add_book_entry(chord_book, 0x85, 3); //I IV V
  add_book_entry(chord_book,0x81, 2); //I V
  add_book_entry(chord_book, 0x21, 2); //I IV
  
  add_book_entry(chord_book, 0x581, 4) ; //I bVII bVI V

  add_book_entry(chord_book, 0x2A1, 4); //I VI IV V 

  add_book_entry(chord_book,0x201, 2);//I VI
  
  add_book_entry(chord_book, 0x2B1, 5) ;// I VI III IV V
  
  add_book_entry(chord_book,0x83, 3); //I V bII
  add_book_entry(chord_book, 0x29, 3); //I III IV


}//pain, suffering even

//need to do function that takes a scale n gets a struct w every pattern it contains; 
CHORD_PROG_ID chord_book_of_scale( S_SCALE scale, S_CHORD_BOOK chord_book){
   //generates the sub-book of a scale as an unique key calculated by multiplicating prime numbers
  if(!scale) return 1;
  if(!chord_book) return 1;
  CHORD_PROG_ID id=1; //product of prime to keep track who is who etc

  S_CHORD_BOOK tmp=chord_book; 

  while (tmp) {
    if(contains_pattern(scale, chord_book->relev_deg)) id*=chord_book->id; 
  }
  return id;
}//not tested!!!

//then function that takes this struct n adds them by length to match a certain length 
//needs to do smtg where I just take whatever degree if a length of 1 is missing



/*
S_CHORD_PROG *generate_blocks( S_SCALE scale, LENGTH length){//whorthless if I let the book be customised


  if(!scale) return NULL;
  if(length==0) return NULL;
  if(length ==1) return NULL;


  CHORD_PROG_ID chords= chord_book_of_scale(scale); //generates relevant degrees
  
  if(chords==1) return NULL;


  LENGTH scale_length= count_bits(scale); 
    
  TRIADS_IN_SCALE * scl_triads= get_triads_length(scale, scale_length);

    //initialises return
  S_CHORD_PROG* ret= malloc( sizeof(S_CHORD_PROG));

  ret->triads=malloc(length* sizeof(TRIADS_IN_SCALE));
  ret->degrees= malloc(length* sizeof(DEGREES));
  ret->length=length;

  CPT i=0;
  CPT ran= (rand()%4+1) %length; //5 is the max length of pattern
  LENGTH lgt_remaining =  length;

  while (lgt_remaining>1) {

    ran= (rand()%4+1) %lgt_remaining;
     
    if(ran==2 && (chords%5 || chords%7 || chords%17)){
      if(chords%(5*7*17)){

      }else if(chords%(5*7)){

      }else if(chords%(5*17)){

      }
    }
    if(ran==3 && (chords%2 || chords%3 || chords%29 || chords%31)){
      
    }
    if(ran==4 && (chords%11 || chords%13)){
      
    }
    if(ran==5 && (chords%5 || chords%23)){
      
    }
    lgt_remaining =  length-ran; 
    
  }

  if(lgt_remaining==0){
    return ret;
  }else if (lgt_remaining==1){
    ret->triads[length-1]= 0;
    return ret;
  }


  return ret;
}

*/