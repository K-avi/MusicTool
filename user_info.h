#ifndef USER_INFO_H_INCLUDED
#define USER_INFO_H_INCLUDED

#include "types.h"


extern void init_saved_scale(S_SAVED_SCALES* user_data, LENGTH  scale_tot); //initialises a saved_scales struct

extern void init_saved_mode(S_SAVED_MODES* user_data, LENGTH  modes_tot); //initialises a saved modes struct

extern S_SCALE** realloc_scales( S_USERINFO* user_data); //allocates more space to the userinfo structure

extern void save_scale( S_SCALE* user_data, S_USERINFO * user_info); //saves a scale in the userinfo structure

extern void init_userinfo( S_USERINFO* user_data); //initialises the userinfo structure

extern void print_saved_scale( S_USERINFO * user_data, LENGTH index);

extern void clear_userinfo(S_USERINFO * user_data);

extern void save_mode(S_MODES * user_data, S_USERINFO *user_info);


#endif // USER_INFO_H_INCLUDED
