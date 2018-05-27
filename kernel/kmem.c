#include "../include/kmem.h"
#include "../include/config.h"
#include "../libc/include/string.h"
#include "../libc/include/stddef.h"
#include "../include/tty.h"

#ifdef __IX86__
 _vmmu kvmmu;
#endif
#define PMAP_SIZE 32768


// end is defined in the linker script.
extern uint32_t kernel_end;
extern uint32_t kernel_begin;
uint32_t placement_address = (uint32_t)&kernel_end;

static unsigned int pmap[PMAP_SIZE];



void pmmfree(void *address){
  unsigned int idx = (((uint32_t)address)/4096);
  pmap[idx/32] |= (1 << (idx % 32));
}

void pmmmark(void *address){
  unsigned int idx = (((uint32_t)address)/4096);
  pmap[idx/32] &= ~(1 << ((uint32_t)idx % 32));
}

uint32_t pmmcount(){
  uint32_t available = 0;
  for(uint32_t i = 0; i < PMAP_SIZE/32;i++){
    for(uint32_t j = 0; j <32; j++){
      if(pmap[i] &(1<<j)){
        available++;
      }
    }
  }
  return available;
}

void *pmmAlloc(){
  int32_t x,y;
  for(x = 0; x < PMAP_SIZE; x++){
    if(pmap[x] !=0){
      for(y = 0; y < 32; y++){
        if(pmap[x] &(1 << y)){
          pmap[x] & ~(1 << y);
            return (void*)((x * 32 + y) * 4096);
        }
      }
    }
  }
  return NULL;
}

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

                    uint32_t addr = mmap->addr;
                    uint32_t mmend = (uint8_t*)addr + mmap->len;
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


                uint32_t kPageSetup = &kernel_begin;

                while(kPageSetup < (uint32_t)&kernel_end){
                  pmmmark((void*)kPageSetup);
                  kPageSetup += 0x1000;
                }

                uint32_t other = (uint32_t)0x00;
                uint32_t otherEnd = (uint32_t)0x800000;
                while(other < otherEnd){
                  pmmmark((void*)other);
                  other +=0x1000;
                }


                vmmu->kmem_end = (uint32_t)&kernel_end;
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

#endif
