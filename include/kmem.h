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


#endif
