#ifndef STDBOOL_H_
#define STDBOOL_H_

#include "sys/cdefs.h"

#ifndef HAS_BOOL
#define bool uint8_t
#define true 0
#define false !true

#define HAS_BOOL 1
#endif

#endif //
