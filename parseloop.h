#ifndef PARSELOOP_H
#define PARSELOOP_H

#include "types.h"

extern void cmdline_parseloop(S_USERINFO* user_saved);

//test only 
extern void file_command_parseloop(char * filename, S_USERINFO* user_saved);
extern void file_environment_parseloop(char * filename, S_USERINFO * user_info);

extern void readparse(char * str ,S_USERINFO* user_info);
#endif