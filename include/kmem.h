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

#define KR 1 //kernel read
#define KW 2 //kernel write
#define KX 4 //kernel execute
#define KF 8 //kernel free

#define UR 16 //user read
#define UW 32 //user write
#define UX 64 //user execute
#define UF 128 //user free

#define VM_HEAD 0xdeadbeef
#define VM_FOOT 0xbeefdead

struct vm_entry {
  uint32_t header;
  uint32_t flags; // marked as kernel, or User, permissions possibily and if free
  uint32_t size;
  void **address;
  uint32_t footer;
  struct vm_entry *next;
};

typedef struct vm_entry vm_entry_t;

struct vm_manager{
  uint32_t size;
  uint32_t used;
  vm_entry_t * head;
  vm_entry_t * tail;
  vm_entry_t * freed;
};

typedef struct vm_manager vm_manager_t;

extern vm_manager_t vm;

void vm_manager_init();
vm_entry_t * prevEntry(vm_entry_t *node);
vm_entry_t * entryTail(vm_entry_t * node);
vm_entry_t * addressToEntry(void *address);
void * vm_allocate(size_t size,uint32_t flags);
void vm_entry_free(void *address);

#endif
