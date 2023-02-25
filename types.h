#ifndef TYPES_H
#define TYPES_H


#include <sys/types.h>
//#define DEBUG
#include <stdbool.h>

#ifdef WIN32 
typedef unsigned char u_char; 
typedef unsigned short u_short; 
typedef unsigned short ushort; 
typedef unsigned int uint;
typedef unsigned long long u_long; 
typedef unsigned long long ulong;
#endif

#define NEUTRAL_CHAR( chr) ( (chr)==' ' || (chr)=='\t' || (chr)=='\n')

#define END_OF_LINE_CHAR( chr) (chr == '\0' || chr=='#')

//different renames of char to make reading easier;
typedef unsigned char NOTE; //generic uchar to rpz notes
typedef unsigned char LENGTH; // -/- length
typedef unsigned char CPT; // -/- cpt 
typedef unsigned char DEGREES; // -/- 
typedef signed char TRIADS_BITS; // specific use ; symbolises the 4 bits of a chord that contain the triad
typedef signed char DEGREES_BITS; // -/- that contains the degree
typedef unsigned char INDEX; // generic index
typedef unsigned char TRIAD; //chord rpz : first 4 bits r degree ; last 4 r triad
typedef unsigned char SYNTAX_ERROR;
typedef unsigned char BITS; //generic uchar 
typedef unsigned char RUNTIME_ERROR;
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


typedef unsigned long long S_DODEC; /*

*/
#define DODEC_ERRFLAG 0xF00000000000 // 
#define DODEC_INITFLAG 0xD

#define HARMO_SERIE 0xCBA9876543210

//-----------------------------------------------------------------------------------------------//

// CHORD MODE


//the following redefinitions of char and short are done to make the chord more readable; and bc theyre used in different contexts. 


typedef unsigned char CHORD_BITS; //used to know which fifth and thirds are in a scale
// 0000 0000
// lsb bit is wether minor third; 7th major third; 6th dim fifth; 5th just fifth; 4th aug fifth ; 3rd bit is for second; 2nd bit is for fourth

typedef unsigned char TRIADS_IN_SCALE; //used to know which triads are contained in a scale 
/* lsb is set if minor chord, is in the scale 7 bit if major chord, 6th bit if dim chord, 5th if augmented chord */

typedef unsigned short PITCH_CLASS_SET; //used to know which degrees are in a scale. 
//behaves similarly to S_SCALE but w an important difference: the LSB corresponds to the fundamental note in the scale 

/* 
  for example: the I IV V chord pattern would be stored as 
  0000 0000 1010 0001
  LSB is fund next set bit is 4th and the last set bit is the fifth 

  and II V I would be: 
  0000 0000 1000 0101
*/



typedef struct S_TRIAD_PROG{
   unsigned char* chord_prog;
   LENGTH length;
}S_TRIAD_PROG; //each chord is stored as a uchar w the first 4 bits being the degrees 
//n the next 3 bits the triad type (min/maj/aug/dim); 




typedef unsigned short CHORD; //used to rpz chord w extensions
  //first 4 bits r degree; 
  //next 11 bits r a scale interpreted as a chord 
  //last bit is an error flag


typedef unsigned short S_EXTENSIONS; //used to rpz extension in CHORD_EXt; 
//encoded the same way as S_SCALE but synonym cuz it makes me happier
//uses the same error flag than S_SCALE due to it being the same thing in another context.

typedef struct S_CHPROG{
  CHORD* chprog; 
  LENGTH length;
}S_CHPROG;

//////////////chord parsing///////////////


typedef unsigned int WORD_BITS; //bits representing the characters parsed from a string to make a chord. 
//each symbol takes 3 bits ; the symbols are defined as macro in bitop.h. the longest symbol is bVIIm which has a length of 5. 
//any symbol longer than that is invalid. The 16 bit is a mask. If it is set then the WORD is invalid.





typedef unsigned long long S_INTERVAL_STRUCTURE; //only uses up to 48 of the 64 bits so this makes me kinda sad

//the interval structure is divided into 4 bits sections containing numbers from 1 to 11 .
//from bit 48 onward bits are flags. 
//special case : a scale containing only 1 note is translated into an empty interval structure which 
//is printed as [12]

//S_INTERVAL_STRUCTURE of { 0 2 4 5 7 9 11} (maj scale)
// (40x0)  0001 0010 0010 0001 0010 0010 

#define INTERVAL_STRUCT_ERRFLAG 0x1000000000000

typedef unsigned int S_INTERVAL_VECTOR; //needs 24 bits ; 
//the interval vecotr is divided in 6  4bits sections containing numbers from 0 to 12.
// if u take the intv vector < 2, 5, 4, 3, 6, 1> (intv vector of the major scale) 
//ur bitwise rep would be: 0001 0110 0011 0100 0101 0010 (or 0x163452)
//                          1     6    3    4    5    2 
//the edge cases are the intv vect of the chromatic scale : <12 , 12, 12, 12 ,12,6>
//its rep is :  0110 1100 1100 1100 1100 1100

//n the unisson {0} scale : <0 ,0 ,0,0,0,0>
//its rep is: 0000 0000 0000 0000 0000 0000

#define INTV_VECT_ERRFLAG 1<<25


//macro functions for environment syntax check

#define NEUTRAL_CHAR_ENV( chr) ((chr)==' ' || chr=='\t')
#define EOL_ENV( chr) ((chr)=='\n')
#define EOF_ENV( chr) ((chr)=='\0')
#define COMMENT_ENV( chr) ((chr)=='#')



//////////////////////////////////////////////// SYNTAX_FLAGS


//some of the error messages are defined but never used !

#define SYNTAX_OK 0 //case when no error
#define SYNTAX_INVALID_SCALE 1
#define SYNTAX_NO_ARG 2 //passed 0 args when one or more needed
#define SYNTAX_INVALID_CHAR 3  //passed invalid chars
#define SYNTAX_UNCLOSED_SCALE 4  //scale opened n never closed
#define SYNTAX_UNCLOSED_PROG 5  //chprog opened n never closed 
#define SYNTAX_TOO_MUCH_ARGS 6 //too much args passed 
#define SYNTAX_TOO_FEW_ARGS 7 //passed too few args 
#define SYNTAX_INVALID_PROG 8 //invalid prog
#define SYNTAX_GENERIC_ERROR 9//generic error
#define SYNTAX_INVALID_ARG 10 //invalid argument error

////env only error
#define SYNTAX_TWO_PAR_OPEN 11  //two ( (  not separated by a ) in an env file.
#define SYNTAX_TWO_PAR_CLOSED 12  //same with ))
#define SYNTAX_UNMATCHED_OPENED_PAR 13 //par opened never closed. 
#define SYNTAX_UNMATCHED_CLOSED_PAR 14 //par closed never opened
#define SYNTAX_UNCLOSED_ENV 15
#define SYNTAX_MISSING_PAR 16
#define SYNTAX_INVALID_SOF 17 //invalid start of file
#define SYNTAX_INVALID_DODEC 18

/////////////// saved stuff//////////////

typedef struct S_LINKED_SCALE{ //basic linked list w scales
  S_SCALE scale; 
  struct S_LINKED_SCALE * next;
}S_SAVED_SCALES;

typedef struct S_LINKED_MODE{
  S_MODES modes;
  struct S_LINKED_MODE * next;
}S_SAVED_MODES;

typedef struct S_LINKED_TRIAD{
 
  S_TRIAD_PROG *ch_prog;
  struct S_LINKED_TRIAD * next ; 
}S_SAVED_TRIAD;

typedef struct S_LINKED_CHPROG{

  S_CHPROG* chprog; 
  struct S_LINKED_CHPROG* next;
}S_SAVED_PROG; 

typedef struct  S_LINKED_DODEC{
    S_DODEC serie; 
    struct S_LINKED_DODEC*next; 
}S_SAVED_DODEC;

typedef struct{ 
    S_SAVED_MODES *saved_modes;
    S_SAVED_SCALES *saved_scales;
    S_SAVED_TRIAD * saved_triads; //triads
    S_SAVED_DODEC * saved_dodecs;
    S_SAVED_PROG * saved_prog;
    CPT triads_num; //triads
    CPT scales_num;
    CPT modes_num;
    CPT dodec_num;
    CPT prog_num;

}S_USERINFO;


/////////////////////////PROG BOOK PART

typedef unsigned long long BOOKENTRY;
 /*
 formated ull; first 12 bits r PCS to check if degree passed contains the prog; 
 bit 13 to 16 contain the length of the prog. 

 bits 17 to MSB are the prog in itself stored as a compact array w each degree stored on 4 bits
 the compact array contains values from 1 to 12 representing the degrees. 0 is used to know when the last value is.
 */


typedef struct{ 
  BOOKENTRY* book; 
  unsigned short nbentries, maxentries; 
}PROGBOOK;


typedef struct{ 
  unsigned short* indexes; 
  LENGTH length; 
}S_BOOK_INDEX_ARRAY; 
/*
stores the relevant degrees in a book when trying to know which bookentry u can generate with a given PCS. 
This struct might be unnessecary. But I'm too dumb not to use it tbh.
*/

typedef struct{ 
  unsigned char* degree_prog; 
  LENGTH length; 
}S_DEGREE_PROG;  
/*
generic degree prog struct to use before converting to triad prog/ chord prog
*/


typedef struct { 
  PROGBOOK ** book_arrays;
  unsigned short nbentries;
}BOOK_LENGTH_TABLE;

/*
array of smaller book tables sorted by length; 
index 0 contains bookentries of length 1; 
index 1 entries of length 2 n so on. 
*/
#define BOOK_REALLOC_SUCCES 0
#define BOOK_REALLOC_NULLBOOK_ERR 1 
#define BOOK_REALLOC_INVALID_CALL 2 
#define BOOK_REALLOC_FAILURE 3
#define BOOK_REALLOC_GENERIC_ERR 4
#define BOOK_INIT_INVALID_CALL 5

////////////////////////////////////
#endif
