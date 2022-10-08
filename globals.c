#include "globals.h"
#include "types.h"
#include "user_info.h"
#include "init.h"
#include <stdlib.h>

S_USERINFO * user_saved=NULL ;

bool EXIT_INFO; //used to exit the app at any moment, set to false when starting the app, if set to true, will terminate execution
