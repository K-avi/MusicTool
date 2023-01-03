#ifndef TYPES_H
#define TYPES_H



#include <stdbool.h>

//different renames of char to make reading easier;
typedef unsigned char NOTE; //generic uchar to rpz notes
typedef unsigned char LENGTH; // -/- length
typedef unsigned char CPT; // -/- cpt 
typedef unsigned char DEGREES; // -/- 
typedef signed char TRIADS_BITS; // specific use ; symbolises the 4 bits of a chord that contain the triad
typedef signed char DEGREES_BITS; // -/- that contains the degree
typedef unsigned char INDEX; // generic index
typedef unsigned char CHORD; //chord rpz : 
/*
first 4 bits are which degree w 0 being I and 11 being major 7 and last 4 bits which triad with 1 being minor, 2 major 
3 diminished and 4 augmented
*/

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



typedef struct S_CHORD_PROG{
   unsigned char* chord_prog;
   LENGTH length;
}S_CHORD_PROG; //each chord is stored as a uchar w the first 4 bits being the degrees 
//n the next 3 bits the triad type (min/maj/aug/dim); 

//////////////chord parsing///////////////


typedef unsigned short WORD_BITS; //bits representing the characters parsed from a string to make a chord. 
//each symbol takes 3 bits ; the symbols are defined as macro in bitop.h. the longest symbol is bVIIm which has a length of 5. 
//any symbol longer than that is invalid. The 16 bit is a mask. If it is set then the WORD is invalid.

/////////////// saved stuff//////////////

typedef struct S_LINKED_SCALE{ //basic linked list w scales
  S_SCALE scale; 
  struct S_LINKED_SCALE * next;
}S_SAVED_SCALES;

typedef struct S_LINKED_MODE{
  S_MODES modes;
  struct S_LINKED_MODE * next;
}S_SAVED_MODES;

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



#endif
