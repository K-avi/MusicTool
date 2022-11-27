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
void init_chord_book( S_CHORD_BOOK *chord_book , CPT * nb_entries, CPT* nb_entries_max){//initialises the default chord book
//chord book is the book where the chord pattern recognised are stored.

  *nb_entries=10;
  *nb_entries_max=10;
  *chord_book= malloc(10 * sizeof(S_CHORD_ENTRY));

  (*chord_book)->length=3; //I IV V  progression
  (*chord_book)->relev_deg=0xA1;
  (*chord_book)->id=2;

  (*chord_book+1)->length=3; //I II V progression
  (*chord_book+1)->relev_deg=0x85;
  (*chord_book+1)->id=3;

  (*chord_book+2)->length=2; //I V  prog
  (*chord_book+2)->relev_deg=0x81;
  (*chord_book+2)->id=5;
  
  (*chord_book+3)->length=2; //I IV 
  (*chord_book+3)->relev_deg=0x21;
  (*chord_book+3)->id=7;

  (*chord_book+4)->length=4; //andalusian boii I bVII bVI V 
  (*chord_book+4)->relev_deg=0x581;
  (*chord_book+4)->id=11;

  (*chord_book+5)->length=4;  //I VI IV V 
  (*chord_book+5)->relev_deg=0x2A1;
  (*chord_book+5)->id=13;

  (*chord_book+6)->length=2; //I VI  ehehe
  (*chord_book+6)->relev_deg=0x201;
  (*chord_book+6)->id=17;

  (*chord_book+7)->length=5; //I VI III IV V  eheheheheheeh
  (*chord_book+7)->relev_deg=0x2B1;
  (*chord_book+7)->id=23;

  (*chord_book+8)->length=3; //I V bII 
  (*chord_book+8)->relev_deg=0x83;
  (*chord_book+8)->id=29;

  (*chord_book+9)->length=3; //I III IV  80% of blues n hardrock ; 60% of thrash metal lessgo
  (*chord_book+9)->relev_deg=0x29;
  (*chord_book+9)->id=31;

}//pain, suffering even

//need to do function that takes a scale n gets a struct w every pattern it contains; 

CHORD_PROG_ID chord_book_of_scale( S_SCALE scale){
   //generates the sub-book of a scale as an unique key calculated by multiplicating prime numbers
  if(!scale) return 1;
  LENGTH nb_deg_scl= get_length(scale);

  if(!contains_pattern(scale, 0x1)) return 1;
  if(!contains_pattern(scale, 0x80)){
    if(!contains_pattern(scale, 0x20)) return 1;
    else return 1; //returns only IV
  }//change 

  CHORD_PROG_ID id=1; //sum of prime to keep track who is who etc
  
  if(contains_pattern(scale, chord_book[1].relev_deg)) id*=3;//contains I II V     
      
  if(contains_pattern(scale, chord_book[4].relev_deg)) id*=11;  // contains andalusian boii I bVII bVI V  
  
  if(contains_pattern(scale, chord_book[8].relev_deg)) id*=29; //contains I V bII 
 
  //this part is about who contains who; is u contain the big ass prog u contain the smaller ones n so on
  if(contains_pattern(scale, chord_book[7].relev_deg )){
    return id*(2*5*7*13*17*23*31);

  }else if (contains_pattern(scale, chord_book[5].relev_deg )){
    return id*(2*5*7*13);

  }else if (contains_pattern(scale, chord_book[0].relev_deg )){
    return id*(5*7*13);

  }else if (contains_pattern(scale, chord_book[2].relev_deg )){ 
    return id*5;
  }
  return id;
}//not tested!!!

//then function that takes this struct n adds them by length to match a certain length 
//needs to do smtg where I just take whatever degree if a length of 1 is missing

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