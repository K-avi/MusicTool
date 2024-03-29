#ifndef GENFUNCS_H
#define GENFUNCS_H
#include "types.h"

extern bool generic_rand( char* str, char mode);

extern u_char generic_print_uinfo (void (*print_uinfo)(S_USERINFO* uinfo, LENGTH index), void (*print_env)( S_USERINFO* uinfo),char*str, S_USERINFO*usaved );
extern u_char generic_remove (void  (* remove)(S_USERINFO* uinfo, INDEX index), char* str, S_USERINFO*uinfo);
extern u_char generic_scl_scl( S_SCALE (*operation)(S_SCALE scl),char* str, S_USERINFO*uinfo );
extern void generic_save( char*str, S_USERINFO* uinfo, char mod);

u_char generic_dodec_dodec( S_DODEC (*operation)(S_DODEC serie), S_DODEC(*nth_operation)(S_DODEC serie, INDEX index), char*str, S_USERINFO*user_saved );
#endif