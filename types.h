#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>


#define DEBUG


#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif //DEBUG

//different renames of char to make reading easier;
typedef unsigned char NOTE;
typedef unsigned char LENGTH;
typedef unsigned char CPT;
typedef unsigned char DEGREES;

typedef short SIGNED_LENGTH; //length with the possibility to set at -1 to check for errors
typedef char SIGNED_BOOL; //1 if true; 0 false ; -1 error

typedef unsigned short S_SCALE; 

/*
  0000 0000 0000 0000
  Scale stored from bit 0 to bit 11; (if first bit set then min2 in scale; 2nd bit then Maj2 etc)
  last 4 bits are flags.
*/

typedef S_SCALE* S_MODES; //array containing n scales 

typedef struct S_LINKED_SCALE{ //basic linked list w scales
  S_SCALE scale; 
  struct S_LINKED_SCALE * next;
}S_SAVED_SCALES;

typedef struct S_LINKED_MODE{
  S_MODES modes;
  struct S_LINKED_MODE * next;
}S_SAVED_MODES;

typedef struct{ 
    S_SAVED_MODES *saved_modes;
    S_SAVED_SCALES *saved_scales;
    CPT scales_num;
    CPT modes_num;
}S_USERINFO;

//-----------------------------------------------------------------------------------------------//

// CHORD MODE


//the following redefinitions of char and short are done to make the chord more readable; and bc theyre used in different contexts. 

typedef unsigned char S_CHORD; //dunno how to use it just yet tbh; might make it a short

/*
typedef struct CHORDS{
  S_CHORD chord;
  struct CHORDS * next;
}S_CHORD_PROG;

typedef struct{
  CHORDS * chords;
  LENGTH length;
}S_CHORD_PROG;
*/


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

typedef struct SCL_INFO{
  S_SCALE scale; 
  TRIADS_IN_SCALE * chords_at_deg; 
}SCL_INFO;

typedef struct CHORD_PROG{ //have to be carefull w allocations n shit
  DEGREES* degrees;
  TRIADS_IN_SCALE *triads;
  LENGTH length;
}S_CHORD_PROG;


/*
typedef struct chord_book{//custom book structure; irrelevant

  CHORD_DEGREES relev_deg;
  LENGTH length; //length takes more memory but makes it so u don't need to calculate length every time

  struct chord_book * next;

}S_CUSTOM_BOOK;*/

typedef unsigned short CHORD_PROG_ID; //unique id obtained by multiplicating primes to associate each chord 
//in the chord book to a scale 


typedef struct chord_entry{//chord_book structure.
  CHORD_DEGREES relev_deg;
  LENGTH length;
  CHORD_PROG_ID id; 
}S_CHORD_ENTRY;
typedef struct chord_entry * S_CHORD_BOOK;



//chord book should prolly be an array tho bc ill need to go through it n shit 
#endif
