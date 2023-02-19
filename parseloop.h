#ifndef PARSELOOP_H
#define PARSELOOP_H

#include "types.h"

extern void cmdline_parseloop(S_USERINFO* user_saved, PROGBOOK * pbook);
extern RUNTIME_ERROR parse_command( char * argv[],  S_USERINFO * user_info, PROGBOOK * pbook);

#ifdef DEBUG
extern void file_command_parseloop(char * filename, S_USERINFO* user_saved);
extern void file_environment_parseloop(char * filename, S_USERINFO * user_info);

extern void readparse(char * str ,S_USERINFO* user_info);
extern void scaleparse(char *str, S_USERINFO*user_info);

#endif
#endif