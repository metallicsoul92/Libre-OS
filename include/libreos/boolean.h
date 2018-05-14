#ifndef BOOLEAN_H_
#define BOOLEAN_H_

#include "../../libc/include/sys/cdefs.h"

#ifndef HAS_BOOL
#define HAS_BOOL 1
//For countermeasures
#undef bool
struct _bool{
  uint8_t flag:1;
}
#define checkBool(b) (b.flag ==0) ? return FALSE : return TRUE
typedef struct _bool bool;
#define TRUE 1
#define FALSE 0

enum boolean{
  false = 0, true=1;
}

inline bool boolset(boolean b){
  bool tmp;

  b == false ? tmp.flag = 0 : tmp.flag = 1;

  return tmp;
}
#endif //HAS_BOOL


#endif //boolean
