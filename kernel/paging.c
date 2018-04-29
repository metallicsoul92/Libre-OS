#include "../include/paging.h"
#include "../include/tty.h"
#include "../include/kmem.h"
#include "../include/idt.h"
// The kernel's page directory
page_directory_t *kernelDirectory=0;

// The current page directory;
page_directory_t *currDirectory=0;

// A bitset of frames - used or free.
uint32_t *frames;
uint32_t nframes;

// Defined in kmem.c
extern uint32_t placement_address;


// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
static void set_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static uint32_t test_frame(uint32_t frame_addr)
{
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
static uint32_t first_frame()
{
    uint32_t i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                uint32_t toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
}

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
    if (page->frame != 0)
    {
        return;
    }
    else
    {
        uint32_t idx = first_frame();
        if (idx == (uint32_t)-1)
        {
            // PANIC! no free frames!!
        }
        set_frame(idx*0x1000);
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

// Function to deallocate a frame.
void free_frame(page_t *page)
{
    uint32_t frame;
    if (!(frame=page->frame))
    {
        return;
    }
    else
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}


void initializePaging(){
    // The size of physical memory. For the moment we
    // assume it is 16MB big.
    uint32_t mem_end_page = 0x1000000;

    nframes = mem_end_page / 0x1000;
    frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    // Let's make a page directory.
    kernelDirectory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    memset(kernelDirectory, 0,0x1000);
    currDirectory = kernelDirectory;

    // We need to identity map (phys addr = virt addr) from
    // 0x0 to the end of used memory, so we can access this
    // transparently, as if paging wasn't enabled.
    // NOTE that we use a while loop here deliberately.
    // inside the loop body we actually change placement_address
    // by calling kmalloc(). A while loop causes this to be
    // computed on-the-fly rather than once at the start.
    int i = 0;
    while (i < placement_address)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame( getPage(i, 1, kernelDirectory), 0, 0);
        i += 0x1000;
    }
    // Before we enable paging, we must register our page fault handler.
    isrs_install_handler(14, pageFault);

    // Now, enable paging!
    switchPageDirectory(kernelDirectory);
}



void switchPageDirectory(page_directory_t *dir){
 currDirectory = dir;
  asm volatile ("mov %0, %%cr3" :: "r"(&dir->tablesPhysical));
  uint32_t cr0;
  asm volatile ("mov %%cr0, %0": "=r"(cr0));
  cr0 |=0x80000000;
  asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

page_t *getPage(uint32_t addr, int make, page_directory_t *dir){
  addr /=0x1000;
  uint32_t table_idx = addr /1024;

  if(dir->tables[table_idx]){
    return &dir->tables[table_idx]->pages[addr%1024];
  }else if(make){
    uint32_t tmp;
    dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[addr%1024];
    }
    else
    {
        return 0;
    }
}

void pageFault(regs_t regs){
  uint32_t faultingAddr;
  asm volatile("mov %%cr2, %0" : "=r"(faultingAddr));

  int present = !(regs.err_code & 0x1);
  int rw = regs.err_code &0x2;
  int us = regs.err_code &0x4;
  int reserved = regs.err_code &0x10;

  printk("Page Fault! ( ");
  if(present)
    printk("present ");
  if(rw)
    printk("read-only ");
  if(us)
    printk("user-mode ");
  if(reserved)
    printk("reserved ");

  printk(") at 0x%x",faultingAddr);

}
