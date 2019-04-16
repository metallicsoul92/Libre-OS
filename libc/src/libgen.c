#include "../include/libgen.h"

#ifndef LIBC_DQPTH
  #ifndef LIBC_SQPTH
    #define LIBC_SQPTH 1
    #undef LIBC_DQPTH
  #endif
#endif

#ifdef LIBC_SQPTH
  #define PTOKEN '/'
#endif

#ifdef LIBC_DQPTH
  #define PTOKEN "//"
#endif



char * basename(char * path){

}

char * dirname(char *){

}
