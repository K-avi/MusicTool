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
/* binary rep is 0000 0000 1110 1100; used to retrieve the bits where 
relevant notes  (aug/dim/ just 5th , min/maj third) are stored for triad generation */

//MASKS FOR CHORD_BITS -> TRIADS_IN_SCALE
#define MIN_MASK 9 // 0000 1001
#define MAJ_MASK 0xA // 0000 1010
#define DIM_MASK 5 // 0000 0101
#define AUG_MASK 0x12 // 0001 0010


//MASKS FOR TRIADS_IN_SCALE 

#define MIN_CHORD 1 
#define MAJ_CHORD 2
#define DIM_CHORD 4
#define AUG_CHORD 8

//masks for S_CHORD_PROG 

#define LAST_CHORD 0x80

//masks for CHORD 

#define FIRST4 0x0F 
#define LAST4 0xF0

//!!!!!!!!!!!!!!!!!!!!!!! NOT THE SAME AS _CHORD DO NOT INTERCHANGE BE VERY CAREFULL    
#define MIN 1 
#define MAJ 2
#define DIM 3
#define AUG 4


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

#define ERROR_WORD 32768

#endif
