#ifndef USER_INFO_H_INCLUDED
#define USER_INFO_H_INCLUDED

#include "types.h"

#define SET_SAVED_SCALE(saved_scales, scl) ( (saved_scales)->scale= (scl))

extern void init_saved_scale(S_SAVED_SCALES* saved_scales); //initialises a saved_scales struct

extern void add_scale(S_SAVED_SCALES * saved_scales, S_SCALE scale); //allocates more space to the userinfo structure
extern void save_scale( S_SCALE scale, S_USERINFO * user_info); //saves a scale in the userinfo structure

extern void print_saved_scale( S_USERINFO * user_data, LENGTH index);
extern void free_saved_scale( S_SAVED_SCALES * saved_scales);

extern void init_saved_mode(S_SAVED_MODES* saved_modes); //initialises a saved modes struct
extern void save_modes(S_MODES modes, S_USERINFO *user_info);
extern void add_mode(S_SAVED_MODES * saved_modes, S_MODES modes);
extern void free_saved_modes(S_SAVED_MODES * saved_modes);
extern void set_modes( S_SAVED_MODES * saved_modes, S_MODES modes);
extern void print_saved_modes(S_USERINFO *user_data, LENGTH index);


extern void init_userinfo( S_USERINFO* user_data); //initialises the userinfo structure
extern void free_userinfo(S_USERINFO * user_data);

extern S_SCALE get_scale_of_modes ( S_USERINFO * user_data, CPT modes_num, CPT scale_num);

extern void remove_scale( S_USERINFO * user_info, CPT index );
extern void remove_modes( S_USERINFO * user_info, CPT index );



#endif // USER_INFO_H_INCLUDED
