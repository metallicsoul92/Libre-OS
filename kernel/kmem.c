#include "../include/kmem.h"
#include "../include/config.h"
#include "../libc/include/string.h"
#include "../libc/include/stddef.h"
#include "../include/tty.h"

#ifdef __IX86__
 _vmmu kvmmu;
#endif


// end is defined in the linker script.
extern uint32_t kernel_end;
uint32_t placement_address = (uint32_t)&kernel_end;

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys)
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
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc_a(uint32_t sz)
{
    return kmalloc_int(sz, 1, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, 0, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, 1, phys);
}

uint32_t kmalloc(uint32_t sz)
{
    return kmalloc_int(sz, 0, 0);
}

const char *memtypes[]={
  "Available", "Reserved", "ACPI","NVS","BADRAM"
};

#ifdef __IX86__
#define MAX_PALIGN_ALLOCS 32
void initMem(_vmmu * vmmu , multiboot_info_t * mb ){
                vmmu->availableMemAmount = 0;
                #if CONFIG_VERBOSE_KERNEL
                printk("Pulling mmap from GRUB\n");
                #endif

                multiboot_memory_map_t *mmap = mb->mmap_addr;

                #if CONFIG_VERBOSE_KERNEL
                printk("Memory Address : 0x%x , Length : %d\n", mb->mmap_addr, mb->mmap_length);
                #endif

                while(mmap < mb->mmap_addr + mb->mmap_length){

                  #if CONFIG_VERBOSE_KERNEL
                  printk("Memory Address At : 0x%X  Length: %U kb type: %u (%s) \n",
                  mmap->addr, mmap->len , mmap->type, memtypes[(mmap->type-1)]);
                  #endif

                  if(mmap->type ==1){
                  vmmu->availableMemAmount++;
                  vmmu->availAddrStart[vmmu->availableMemAmount-1] = mmap->addr;
                  vmmu->availAddrSize[vmmu->availableMemAmount-1] = mmap->len;
                  }
                  mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(mmap->size));

                }
                vmmu->kmem_end = (uint32_t)&kernel_end;
                vmmu->heap_begin = vmmu->kmem_end + 0x1000;
                vmmu->kheap_mem_end = 0x400000;
                placement_address = vmmu->kheap_mem;
                vmmu->kheap_mem = vmmu->kheap_mem_end - (MAX_PALIGN_ALLOCS *4096);
                vmmu->heap_end = vmmu->kheap_mem;
                memset((char *)vmmu->heap_begin,0,(vmmu->heap_end - vmmu->heap_begin));
                vmmu->pageDesc = (uint8_t *)kmalloc(MAX_PALIGN_ALLOCS);

                #if CONFIG_VERBOSE_KERNEL
                printk("VMMU Data:\n");
                printk("Kernel End: 0x%x\nKernel Heap Begin: 0x%x   Kernel Heap End: 0x%x\n",vmmu->kmem_end,
                        vmmu->kheap_mem,vmmu->kheap_mem_end);
                printk("Heap Memory Begin: 0x%x  Heap Memory End: 0x%x\n",vmmu->heap_begin,vmmu->heap_end);
                printk("Vmmu pageDesc at: 0x%x\n",vmmu->pageDesc);
                #endif

              }

#endif
