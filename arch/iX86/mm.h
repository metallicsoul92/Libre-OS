#ifndef IX86_MM_H
#define IX86_MM_H

#include "../../include/config.h"

#include "../../include/multiboot.h"

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
  //As of right now ill have this static, but i eventually want to
  //set this up so dynamically finds more memory.... ill put 6 in for now
  uint64_t availAddrStart[6];
  uint64_t availAddrSize[6];
  uint8_t availableMemAmount;
};

typedef struct __vmmu_ _vmmu;
#define MAX_PALIGN_ALLOCS 32
void initMem(_vmmu * vmmu, multiboot_info_t * mb);

extern  _vmmu kvmmu;

#endif // ix86_mm_h
