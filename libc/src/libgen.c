#include "../include/libgen.h"
#include "../include/string.h"

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
    char *p = strrchr (filename, '/');
  return p ? p + 1 : (char *) filename;
}

char * dirname(char * path){

  static const char dot[] = ".";
  char * prevSlash;

  prevSlash = path != NULL ? strrchr(path, '/') : NULL;

  if(prevSlash == path){
    ++prevSlash;
  }else if ( prevSlash != NULL && prevSlash[1] == '\0'){
    prevSlash = memchr(path, prevSlash-path, '/');
  }

  if(prevSlash !=NULL){
    prevSlash[0] = '\0';
  }else

  path = (char *)dot;
  return path;
}
