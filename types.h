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

typedef short SIGNED_LENGTH; //length with the possibility to set at -1 to check for errors

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

typedef struct CHORDS{
  S_CHORD chord;
  struct CHORDS * next;
}S_CHORD_PROG;

/*
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

typedef unsigned short DEG_IN_SCALE; //used to know which degrees are in a scale. Behaves like the S_SCALE structure; 
//but used for a different purpose.

typedef struct SCL_INFO{
  S_SCALE scale; 
  TRIADS_IN_SCALE * scale_at_deg; 
  LENGTH scale_length;
}SCL_INFO;

#endif
