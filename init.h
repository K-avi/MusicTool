#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "types.h"

extern void init_saved_scale(S_SAVED_SCALES* saved_scales);
extern void free_saved_scale( S_SAVED_SCALES * saved_scales);

extern void init_saved_mode(S_SAVED_MODES* saved_modes);
extern void free_saved_modes( S_SAVED_MODES * saved_modes);

extern void init_userinfo( S_USERINFO* user_data);
extern void free_userinfo( S_USERINFO* user_info);


#endif // INIT_H_INCLUDED
