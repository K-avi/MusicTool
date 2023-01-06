#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "types.h"
#include <stdbool.h>

extern bool syntaxcheck(char *str);


//testing only
extern bool savescalecheck(char *str);

extern bool scalecheck(char* str);
extern bool removecheck(char *str);

extern bool printcheck(char *str);

extern bool harmocheck(char * str);

extern bool two_num_args_check(char * str);

#endif