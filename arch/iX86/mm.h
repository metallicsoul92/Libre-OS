#ifndef IX86_MM_H
#define IX86_MM_H

#include "../../include/config.h"

#ifndef HAS_CDEFS
#include "../../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif

struct __vmmu_{

  uint32_t kmem_end;
  uint32_t heap_begin;
  uint32_t kheap_mem;
  uint32_t kheap_mem_end;
  uint32_t heap_end;
  uint8_t *pageDesc;
};

typedef struct __vmmu_ _vmmu;
#define MAX_PALIGN_ALLOCS 32
void initMem(_vmmu * vmmu);

#endif // ix86_mm_h
