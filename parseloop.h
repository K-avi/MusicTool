#ifndef PARSELOOP_H
#define PARSELOOP_H

#include "types.h"

extern void cmdline_parseloop();

//test only 
extern void file_command_parseloop(char * filename);
extern void file_environment_parseloop(char * filename, S_USERINFO * user_info);

#endif