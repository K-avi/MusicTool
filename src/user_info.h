#ifndef USER_INFO_H_INCLUDED
#define USER_INFO_H_INCLUDED

#include "types.h"

#define SET_SAVED_SCALE(saved_scales, scl) ( (saved_scales)->scale= (scl))

extern void add_scale(S_SAVED_SCALES * saved_scales, S_SCALE scale); //allocates more space to the userinfo structure
extern void save_scale( S_SCALE scale, S_USERINFO * user_info); //saves a scale in the userinfo structure

extern void print_saved_scale( S_USERINFO * user_data, LENGTH index);
extern void free_saved_scale( S_SAVED_SCALES * saved_scales);


extern void save_modes(S_MODES modes, S_USERINFO *user_info);
extern void add_mode(S_SAVED_MODES * saved_modes, S_MODES modes);
extern void free_saved_modes(S_SAVED_MODES * saved_modes);
extern void set_modes( S_SAVED_MODES * saved_modes, S_MODES modes);
extern void print_saved_modes(S_USERINFO *user_data, LENGTH index);


extern void save_triadprog(S_TRIAD_PROG* chprog, S_USERINFO * user_info);
extern void remove_triadprog(  S_USERINFO * user_info, CPT index );
extern void print_saved_triadprog( S_USERINFO * user_data, INDEX index);

extern S_SCALE get_scale_of_modes ( S_USERINFO * user_data, CPT modes_num, CPT scale_num);

extern void remove_scale( S_USERINFO * user_info, CPT index );
extern void remove_modes( S_USERINFO * user_info, CPT index );
extern void remove_dodec(  S_USERINFO * user_info, CPT index );

extern void save_dodec( S_DODEC serie, S_USERINFO * user_info);
extern void print_saved_serie( S_USERINFO * user_data, INDEX index);

extern S_TRIAD_PROG* get_triadprog( S_USERINFO *user_data, INDEX index);
extern S_MODES get_modes( S_USERINFO *user_data, INDEX index);
extern S_SCALE get_saved_scale( S_USERINFO * user_data, INDEX index);
extern S_DODEC get_saved_dodec( S_USERINFO * user_data, INDEX index);

extern S_CHPROG* get_chord_prog( S_USERINFO *user_data, INDEX index);
extern void remove_chprog(  S_USERINFO * user_info, CPT index );
extern void save_chprog( S_CHPROG* chprog , S_USERINFO * user_info);
extern void print_saved_chprog( S_USERINFO * user_data, INDEX index);
extern S_TRIAD_PROG * duplicate_triadprog( S_TRIAD_PROG * chprog);

#ifdef DEBUG

extern CPT modes_in_saved (S_MODES mode, S_SAVED_MODES * saved_modes);
#endif

#endif // USER_INFO_H_INCLUDED
