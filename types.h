#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

//different renames of char to make reading easier;
typedef unsigned char NOTE;
typedef unsigned char LENGTH;
typedef unsigned char CPT;
typedef unsigned char DEGREES;
typedef unsigned char INDEX;

typedef short SIGNED_LENGTH; //length with the possibility to set at -1 to check for errors
typedef char SIGNED_BOOL; //1 if true; 0 false ; -1 error

typedef unsigned short S_SCALE; 

/*
  0000 0000 0000 0000
  Scale stored from bit 0 to bit 11; (if first bit set then min2 in scale; 2nd bit then Maj2 etc)
  last 4 bits are flags.
*/

typedef S_SCALE* S_MODES; //array containing n scales 



//-----------------------------------------------------------------------------------------------//

// CHORD MODE


//the following redefinitions of char and short are done to make the chord more readable; and bc theyre used in different contexts. 

typedef unsigned char S_CHORD; //dunno how to use it just yet tbh; might make it a short


typedef unsigned char CHORD_BITS; //used to know which fifth and thirds are in a scale
// 0000 0000
// lsb bit is wether minor third; 7th major third; 6th dim fifth; 5th just fifth; 4th aug fifth 

typedef unsigned char TRIADS_IN_SCALE; //used to know which triads are contained in a scale 
/* lsb is set if minor chord, is in the scale 7 bit if major chord, 6th bit if dim chord, 5th if augmented chord */

typedef unsigned short CHORD_DEGREES; //used to know which degrees are in a scale. 
//behaves similarly to S_SCALE but w an important difference: the LSB corresponds to the fundamental note in the scale 

/* for example: the I IV V chord pattern would be stored as 
  0000 0000 1010 0001
  LSB is fund next set bit is 4th and the last set bit is the fifth 

  and II V I would be: 
  0000 0000 1000 0101
*/







typedef struct chord_entry{//chord_book structure.
  CHORD_DEGREES relev_deg;
  LENGTH length;
  struct chord_entry* next;
  unsigned id;
}S_CHORD_ENTRY;
typedef struct chord_entry * S_CHORD_BOOK;

/////////////////////////// saved stuff

typedef struct S_LINKED_SCALE{ //basic linked list w scales
  S_SCALE scale; 
  struct S_LINKED_SCALE * next;
}S_SAVED_SCALES;

typedef struct S_LINKED_MODE{
  S_MODES modes;
  struct S_LINKED_MODE * next;
}S_SAVED_MODES;

typedef struct CHORD_PROG{ //have to be carefull w allocations n shit
  DEGREES* degrees;
  TRIADS_IN_SCALE *triads;
  LENGTH length;
}S_CHORD_PROG;


typedef struct S_LINKED_CHPROGS{
 
  S_CHORD_PROG *ch_prog;
  struct S_LINKED_CHPROGS * next ; 
}S_SAVED_PROGS;

typedef struct{ 
    S_SAVED_MODES *saved_modes;
    S_SAVED_SCALES *saved_scales;
    S_SAVED_PROGS * saved_progs;
    CPT progs_num;
    CPT scales_num;
    CPT modes_num;
}S_USERINFO;

typedef void* DEGREES_IN_CHPROG; //4 bits per degree, 0 is end of chprog, 1 is I, 2 is bII, ......
typedef void* TRIADS_IN_CHPROG; // 4 bits per triad, 0 is terminated , 1 is minor , 2 is major, 3 is diminished, 4 is augmented

typedef struct CHORD_PROG_NEW{
  DEGREES_IN_CHPROG degrees; 
  TRIADS_IN_CHPROG triads;
}S_CHPROG_NEW;

//u can store up to 16 chords in one unsigned long long ; so the allocation is an array %16


#endif
