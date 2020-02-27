#ifndef ARCH_X86_64_MM_H
#define ARCH_X86_64_MM_H

#include "../../include/config.h"
#include "../../include/multiboot.h"

#ifndef HAS_CDEFS
#include "../../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif

struct __vmmu_{

  uint64_t kmem_end;
  uint64_t heap_begin;
  uint64_t kheap_mem;
  uint64_t kheap_mem_end;
  uint64_t heap_end;
};


#endif
