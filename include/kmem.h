#ifndef KMEM_H_
#define KMEM_H_

#include "../include/config.h"
#
#ifndef HAS_CDEFS
#include "../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif

#ifdef __IX86__
#include "../arch/iX86/mm.h"
 _vmmu kvmmu;
#endif

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
uint32_t kcalloc(uint32_t sz);


struct vm_entry {
  uint32_t flags; // marked as kernel, or User, permissions possibily and if free
  uint32_t size;
  void *address;
};

typedef struct vm_entry vm_entry_t;

struct vm_manager{
  uint32_t size;
  uint32_t used;
  vm_entry_t * head;
  vm_entry_t * tail;
  vm_entry_t * freed;
};

#endif
