#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

extern bool QUIT_INFO;
extern void init_scale( S_SCALE * scale );
extern void partial_init_scale( S_SCALE*scale);

extern void init_modes(S_MODES * modes);
extern void partial_init_modes(S_MODES * modes);

//extern void init_saved_struct(S_SAVED* user_data, LENGTH length);

#endif // INIT_H_INCLUDED
