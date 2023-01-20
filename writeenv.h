#ifndef ENV_H
#define ENV_H


#include "types.h"
#include <stdio.h>

extern bool fprint_env(FILE *f, S_USERINFO* user_info);
extern void print_env(S_USERINFO* user_info);
extern bool write_env(char* str , S_USERINFO* user_info);

extern void print_scl_env(S_USERINFO*uinfo);
extern void print_modes_env( S_USERINFO*uinfo);
extern void print_chprog_env (S_USERINFO*uinfo);
extern void print_dodec_env (S_USERINFO*uinfo);

#endif