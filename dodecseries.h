#ifndef SERIE_H 
#define SERIE_H

#include "types.h"
#include <stdlib.h>

extern S_DODEC generate_serie();
extern S_DODEC inverse_serie(S_DODEC serie, INDEX inversion);
extern S_DODEC retrograde_serie (S_DODEC serie, INDEX inversion);
extern S_DODEC * serie_to_12tmat( S_DODEC serie);

extern void print_serie(S_DODEC serie);
extern S_DODEC init_dodec();

#ifdef DEBUG 

S_DODEC add_rand_to_dodec( S_DODEC serie);

#endif
#endif
