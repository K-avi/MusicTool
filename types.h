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

typedef struct{ //scale structure

    NOTE scale[12];
    LENGTH length;
} S_SCALE;

typedef struct{ //scale modes structure

    NOTE scale[12][12]; //arrays each containing a scale
    LENGTH length; //the length of the scales is the same as the number of scales thus onnly one length index is necessary

}S_MODES;

typedef struct{// user saved Data structure 

    S_SCALE* scales; //used to save scales //could allocate it w array instead dunno

    LENGTH scale_num; //number of scales saved
	LENGTH scale_tot ;//number of scale u can save

}S_SAVED_SCALES;

typedef struct{// user saved Data structure 

    S_MODES* modes; //used to save modes

    LENGTH mode_num; //number of modes saved
	LENGTH mode_tot; //number of modes u can save 

}S_SAVED_MODES;



/*typedef struct{ //structure to store up to 20 slots of the saved structure  //might be useless tbh 

    S_SAVED saved[20];
    LENGTH length;

}S_SAVED_ARR;*/



#endif
