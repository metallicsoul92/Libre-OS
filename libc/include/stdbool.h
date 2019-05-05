#ifndef LIBC_STDBOOL_H_
#define LIBC_STDBOOL_H_

#include "sys/cdefs.h"

#ifndef HAS_BOOL
#define bool uint8_t
#define false 0
#define true !false

#define HAS_BOOL 1
#endif

#endif //
