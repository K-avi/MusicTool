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

#define MAJ_SCALE {0, 2, 4, 5, 7, 9,11, 13, 13, 13, 13,13}

typedef unsigned char NOTE;
typedef unsigned char LENGTH;
typedef unsigned char CPT;

typedef unsigned short S_SCALE; 

/*
  0000 0000 0000 0000
  Scale stored from bit 0 to bit 11; (if first bit set then min2 in scale; 2nd bit then Maj2 etc)
  last 4 bits are flags.
*/

typedef S_SCALE* S_MODES; //array containing n scales 

typedef struct{// user saved Data structure


    LENGTH scale_num; //number of scales saved
	  LENGTH scale_tot ;//number of scale u can save

    S_SCALE** scales; //used to save scales


}S_SAVED_SCALES;

typedef struct{// user saved Data structure

    LENGTH mode_num; //number of modes saved
	  LENGTH mode_tot; //number of modes u can save

    S_MODES** modes; //used to save modes

}S_SAVED_MODES;



typedef struct{ //structure to store up to 20 slots of the saved structure  //might be useless tbh

    S_SAVED_MODES * saved_modes;
    S_SAVED_SCALES * saved_scales;

}S_USERINFO;


//-----------------------------------------------------------------------------------------------//

// CHORD MODE

typedef struct{
  NOTE * note;
  LENGTH length;
}S_CHORD;

typedef struct CHORDS{
  S_CHORD chord;
  struct CHORDS * next;
}CHORDS;

typedef struct{
  CHORDS * chords;
  LENGTH length;
}S_CHORD_PROG;


typedef unsigned char CHORD_BITS; //used to know which fifth and thirds are in a scale
// 0000 0000
//8th bit is wether minor third; 7th major third; 6th dim fifth; 5th just fifth; 4th aug fifth

#endif
