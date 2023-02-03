#ifndef BITOP_H_INCLUDED
#define BITOP_H

#include "types.h"

#define SCALE_BITS 16
#define ERROR_FLAG 0x8000 // way to return error from functions that generates scale 

// error flag's bit rep is: 1000 0000 0000 0000
#define SET_NTH(bits, n) ( 1<<n | bits)

#define GET_NTH(bits,n) (1 & bits>>n)
#define POP_BIT(bits, n) (1<<n ^ bits)

#define ROTATE_LEFT(bits, n, nb_bits) (bits << n)|(bits >> (nb_bits - n)) //rotates "bits" by n if bits size is nb_bits
#define ROTATE_RIGHT(bits, n, nb_bits) (bits >> n)|(bits << (nb_bits - n))

#define FULLSCALE 2047 //value of a fullscale as a ushort
#define MAXLENGTH 12 //max length of a scale 



////////////////////////// MASKS //////////////////////

//MASK FOR S_SCALE -> CHORD_BITS
#define TRIAD_MASK 0xEC 
#define EXTTRIAD_MASK 0xFE
/* binary rep is 0000 0000 1110 1100; used to retrieve the bits where 
relevant notes  (aug/dim/ just 5th , min/maj third) are stored for triad generation */

//MASKS FOR CHORD_BITS -> TRIADS_IN_SCALE
#define MIN_MASK 9 // 0000 1001
#define MAJ_MASK 0xA // 0000 1010
#define DIM_MASK 5 // 0000 0101
#define AUG_MASK 0x12 // 0001 0010
#define SUS2_MASK 0x28 // 0011 0000 
#define SUS4_MASK 0x48 // 0101 0000 


//MASKS FOR TRIADS_IN_SCALE 

#define MIN_CHORD 1 
#define MAJ_CHORD 2
#define DIM_CHORD 4
#define AUG_CHORD 8
#define SUS2_CHORD 16 
#define SUS4_CHORD 32

//masks for S_CHORD_PROG 

#define LAST_CHORD 0x80

//masks for CHORD 

#define FIRST4 0x0F 
#define LAST4 0xF0

//triad in scale :
//!!!!!!!!!!!!!!!!!!!!!!! NOT THE SAME AS _CHORD DO NOT INTERCHANGE BE VERY CAREFULL    
#define MIN 1 
#define MAJ 2
#define DIM 3
#define AUG 4
#define SUS2 5
#define SUS4 6


enum { DEG_I , DEG_bII, DEG_II , DEG_bIII ,DEG_III, DEG_IV, DEG_bV, DEG_V, DEG_bVI, DEG_VI, DEG_bVII, DEG_VII};
//end of masks for chord

///////////////////MACROS USED IN STR TO CHORD PARSING (for WORD_BITS) //////////////

#define MAX_CHORD_STRING_LENGTH 5
#define WORD_BITS_I 1 
#define WORD_BITS_V 2 
#define WORD_BITS_b 3 
#define WORD_BITS_m 4
#define WORD_BITS_aug 5 
#define WORD_BITS_dim 6
#define WORD_BITS_sus2 7
#define WORD_BITS_sus4 8 //fuck fuck fuck fuck fuck fuck

#define ERROR_WORD 32768

//for PITCH_CLASS_SET : 

#define MINOR_PCS 0x89 // 0000 0000 1000 1001
#define MAJOR_PCS 0x91 // 0000 0000 1001 0001
#define DIM_PCS 0x49 // 0000 0000 0100 1001
#define AUG_PCS 0x111 // 0000 0001 0001 0001
#define SUS2_PCS 0x85 //0000 0000 1000 0101
#define SUS4_PCS 0xA1 // 0000 0000 1010 0001

#define PCS_TO_SCALE(pcs)  ((pcs)>>1)
#define ERROR_FLAG_PCS 0xF000



//redudant w chord bits
// TRIADS_IN_SCALE to CHORDENDED
//!!!!!!!!!!!!!!!!!!!!!!! NOT THE SAME AS _CHORD DO NOT INTERCHANGE BE VERY CAREFULL    
#define MIN_EXT 0x44 // 0000 0000 0100 0100
#define MAJ_EXT 0x48 // 0000 0000 0100 1000
#define DIM_EXT 0x24 // 0000 0000 0010 0100
#define AUG_EXT 0x88 // 0000 0000 1000 1000
#define SUS2_EXT 0x42 // 0000 0000 0100 0010
#define SUS4_EXT 0x50 // 0000 0000 0101 0000


//flags to get 1 specific note/degree of S_SCALE / S_EXTENSIONS structure 

#define NOTE_b2 1 
#define NOTE_2 2
#define NOTE_b3 1<<2 
#define NOTE_3 1<<3
#define NOTE_4 1<<4
#define NOTE_b5 1<<5
#define NOTE_5 1<<6
#define NOTE_b6 1<<7
#define NOTE_6 1<<8
#define NOTE_b7 1<<9
#define NOTE_7 1<<10

#endif
