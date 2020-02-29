#include "../include/kmem.h"
#include "../include/config.h"
#include "../libc/include/string.h"
#include "../libc/include/stddef.h"
#include "../include/tty.h"

_vmmu kvmmu;
#define PMAP_SIZE 32768


#ifdef __IX86__
static uint32_t pmap[PMAP_SIZE];
extern uint32_t kernel_end;
extern uint32_t kernel_begin;
uint32_t placement_address = (uint32_t)&kernel_end;
#endif

#ifdef __X86_64__
static uint64_t pmap[PMAP_SIZE];
extern uint64_t kernel_end;
extern uint64_t kernel_begin;
uint64_t placement_address = (uint64_t)&kernel_end;
#endif



void pmmfree(void *address){
  MEMTYPE idx = (((MEMTYPE)address)/4096);
  pmap[idx/MEMBITS] |= (1 << (idx % MEMBITS));
}

void pmmmark(void *address){
  MEMTYPE idx = (((MEMTYPE)address)/4096);
  pmap[idx/MEMBITS] &= ~(1 << ((MEMTYPE)idx % MEMBITS));
}

MEMTYPE pmmcount(){
  MEMTYPE available = 0;
  for(MEMTYPE i = 0; i < PMAP_SIZE/MEMBITS;i++){
    for(MEMTYPE j = 0; j <MEMBITS; j++){
      if(pmap[i] &(1<<j)){
        available++;
      }
    }
  }
  return available;
}

void *pmmAlloc(){
  MEMTYPE x,y;
  for(x = 0; x < PMAP_SIZE; x++){
    if(pmap[x] !=0){
      for(y = 0; y < MEMBITS; y++){
        if(pmap[x] &(1 << y)){
          pmap[x] & ~(1 << y);
            return (void*)((x * MEMBITS + y) * 4096);
        }
      }
    }
  }
  return NULL;
}

MEMTYPE kmalloc_int(MEMTYPE sz, int align, MEMTYPE *phys)
{
    // This will eventually call malloc() on the kernel heap.
    // For now, though, we just assign memory at placement_address
    // and increment it by sz. Even when we've coded our kernel
    // heap, this will be useful for use before the heap is initialised.
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    MEMTYPE tmp = placement_address;
    placement_address += sz;
    return tmp;
}

MEMTYPE kmalloc_a(MEMTYPE sz)
{
    return kmalloc_int(sz, 1, 0);
}

MEMTYPE kmalloc_p(MEMTYPE sz, MEMTYPE *phys)
{
    return kmalloc_int(sz, 0, phys);
}

MEMTYPE kmalloc_ap(MEMTYPE sz, MEMTYPE *phys)
{
    return kmalloc_int(sz, 1, phys);
}

MEMTYPE kmalloc(MEMTYPE sz)
{
    return kmalloc_int(sz, 0, 0);
}

MEMTYPE kcalloc(MEMTYPE sz){
  return (MEMTYPE)memset(kmalloc(sz),0,sz);
}




const char *memtypes[]={
  "Available", "Reserved", "ACPI","NVS","BADRAM"
};

#ifdef __IX86__
#define MAX_PALIGN_ALLOCS 32
void initMem(_vmmu * vmmu , multiboot_info_t * mb ){
                vmmu->availableMemAmount = 0;
                #ifdef CONFIG_VERBOSE_KERNEL
                printk("Pulling mmap from GRUB\n");
                #endif

                multiboot_memory_map_t *mmap = mb->mmap_addr;

                #ifdef CONFIG_VERBOSE_KERNEL
                printk("Lower Memory Amount : %dkb\n" , mb->mem_lower);
                printk("Upper Memory Amount : %dkb\n" , mb->mem_upper);
                printk("Memory Map Address : 0x%x , Length : %d\n", mb->mmap_addr, mb->mmap_length);
                #endif
                memset(pmap,0,sizeof(pmap));

                while(mmap < mb->mmap_addr + mb->mmap_length){

                  #ifdef CONFIG_VERBOSE_KERNEL
                  printk("Memory Address At : 0x%X  Length: %U bytes type: %u (%s) \n",
                  mmap->addr, mmap->len , mmap->type, memtypes[(mmap->type-1)]);
                  #endif

                  if(mmap->type ==1){

                    MEMTYPE addr = mmap->addr;
                    MEMTYPE mmend = (uint8_t*)addr + mmap->len;
                      while(addr < mmend){
                        pmmfree((void*)addr);
                        addr += 0x1000;
                      }

                    vmmu->availableMemAmount++;
                    vmmu->availAddrStart[vmmu->availableMemAmount-1] = mmap->addr;
                    vmmu->availAddrSize[vmmu->availableMemAmount-1] = mmap->len;
                    }


                  mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(mmap->size));

                }


                MEMTYPE kPageSetup = &kernel_begin;

                while(kPageSetup < (MEMTYPE)&kernel_end){
                  pmmmark((void*)kPageSetup);
                  kPageSetup += 0x1000;
                }

                MEMTYPE other = (uint32_t)0x00;
                MEMTYPE otherEnd = (uint32_t)0x800000;
                while(other < otherEnd){
                  pmmmark((void*)other);
                  other +=0x1000;
                }


                vmmu->kmem_end = (MEMTYPE)&kernel_end;
                vmmu->heap_begin = vmmu->kmem_end + 0x1000;
                vmmu->kheap_mem_end = 0x400000;
                placement_address = vmmu->kheap_mem;
                vmmu->kheap_mem = vmmu->kheap_mem_end - (MAX_PALIGN_ALLOCS *4096);
                vmmu->heap_end = vmmu->kheap_mem;
                memset((char *)vmmu->heap_begin,0,(vmmu->heap_end - vmmu->heap_begin));
                vmmu->pageDesc = (uint8_t *)kmalloc(MAX_PALIGN_ALLOCS);

                vmmu->_pmap = pmap;
                vmmu->initramamount = mb->mem_lower + mb->mem_upper;



                #ifdef CONFIG_VERBOSE_KERNEL
                printk("VMMU Data:\n");
                printk("Kernel End: 0x%x\nKernel Heap Begin: 0x%x   Kernel Heap End: 0x%x\n",vmmu->kmem_end,
                        vmmu->kheap_mem,vmmu->kheap_mem_end);
                printk("Heap Memory Begin: 0x%x  Heap Memory End: 0x%x\n",vmmu->heap_begin,vmmu->heap_end);
                printk("Vmmu pageDesc at: 0x%x\n",&vmmu->pageDesc);
                printk("pmap at: 0x%x\n",vmmu->_pmap);
                printk("pmap size : %d\n",sizeof(pmap));
                printk("Initial ram amount : %d\n", vmmu->initramamount);
                #endif

              }

vm_manager_t vm;

void vm_manager_init(){
  vm.size = 0;
  vm.used = 0;
  vm.head = NULL;
  vm.tail = NULL;
  vm.freed = NULL;
}

vm_entry_t * prevEntry(vm_entry_t *node){
  if(memcmp(&vm.head,node,sizeof(vm_entry_t))){
    return NULL;
  }else if(memcmp(vm.head->next,node,sizeof(vm_entry_t))){
    return vm.head;
  }else{
    vm_entry_t *temp = vm.head->next;
    while(temp != NULL){
      if(memcmp(temp->next,node, sizeof(vm_entry_t))){
        return temp;
      }else
      temp = temp->next;
    }
  }
  return NULL;
}


void * vm_allocate(size_t size, uint32_t flags){
  vm_entry_t * out = kmalloc(sizeof(vm_entry_t));
  out->header = VM_HEAD;
  out->flags = flags;
  out->size = size;
  out->address = kmalloc(size);
  out->footer = VM_FOOT;
  out->next = NULL;

  if(vm.head == NULL){
    vm.head = out;
    vm.tail = out;
  }else{
    vm_entry_t * temp = entryTail(vm.head);
    temp->next = out;
    vm.tail = out;
  }
  vm.size +=size;
  vm.used +=size;

  return out->address[0];
}

vm_entry_t * entryTail(vm_entry_t * node){
  if(node->next == NULL){
    return node;
  }else{
    entryTail(node->next);
  }
  return NULL;
}

vm_entry_t * addressToEntry(void *address){
  vm_entry_t * entry = (vm_entry_t*)(address - offsetof(vm_entry_t,address));
    return entry;
  }



void vm_entry_free(void *address){
    vm_entry_t *entry = addressToEntry(address);
    MEMTYPE flags = entry->flags;
    vm_entry_t *prev = prevEntry(entry);
    prev->next = entry->next;
    entry->next = NULL;
    switch(flags){
      case KR:
      case KW:
      case KX:
      case KA:
      entry->flags = F;
      break;
      case UR:
      case UW:
      case UX:
      case UA:
      entry->flags = F;
      break;
      case F:
      printk("Error: Entry at %x Freed already.\n", address);
      break;
    }
    if(vm.freed == NULL){
      vm.freed = entry;
    }else{
    vm_entry_t * freedTail = entryTail(vm.freed);
    freedTail->next = entry;
    vm.used -= entry->size;
  }
}

#endif
