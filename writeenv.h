#ifndef ENV_H
#define ENV_H


#include "types.h"
#include <stdio.h>

extern bool fprint_env(FILE *f, S_USERINFO* user_info);
extern void print_env(S_USERINFO* user_info);
extern bool write_env(char* str , S_USERINFO* user_info);

#endif