#include "../include/config.h"
#include "../include/paging.h"
#include "../arch/iX86/mm.h"
#include "../libc/include/sys/cdefs.h"
#include "../include/inlineAssembly.h"
#include "../include/tty.h"

/** uint32_t page_dir[1024] __attribute__((aligned(4096)));
    uint32_t first_page_table[1024] __attribute__((aligned(4096)));

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

uint16_t numPages = 0;

void setupBasicPaging(){

  for(int i =0; i < 1024; i++){
    page_dir[i] = 0x00000002;
  }

  for(int j=0; j < 1024; j++){
    first_page_table[j] = (j * 0x1000) | 3;
  }
  numPages++;

  page_dir[0] = ((unsigned int)first_page_table) | 3;

  loadPageDirectory(page_dir);
  enablePaging();
  #ifdef CONFIG_VERBOSE_KERNEL
  //printk("page directory at %x\npageTable at: %x\n",&page_dir,&first_page_table);
  for(unsigned int i = 0; i <1024; i++){
  //  printk("Page %d of Page Table 1 at : 0x%x\n",i,(uint32_t)&first_page_table[i]);
  }
  #endif

  **/


static uint32_t page_dir_loc = 0;
#ifdef CONFIG_IX86_NON_PAE_
static page_dir_t * page_directory = 0;
#endif
#ifdef CONFIG_IX86_PAE_
static ptpd_t * _ptpd = 0;
#endif
pageTable_entry_t * last_page = 0;
/*
static uint32_t* page_directory = 0;
static uint32_t page_dir_loc = 0;
static uint32_t* last_page = 0;
*/


/* Paging now will be really simple
 * we reserve 0-8MB for kernel stuff
 * heap will be from approx 1mb to 4mb
 * and paging stuff will be from 4mb
 */


void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{

	uint16_t id = virt >> 22;
#ifdef CONFIG_VERBOSE_KERNEL
		//printk("id 0x%x, virtual: 0x%x\n", id, virt);
#endif
	for(int i = 0; i < 1024; i++)
	{
		last_page[i].asUI = phys | 3;
		phys += 4096;
	}
	page_directory[id].entries[id].asUI = ((uint32_t)last_page) | 3;
	last_page = (pageTable_entry_t *)(((uint32_t)last_page) + 4096);

#ifdef CONFIG_VERBOSE_KERNEL
	printk("Mapping 0x%x(%d) to 0x%x\n", virt, id, phys);
#endif

}

void paging_enable()
{
	asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc));
	asm volatile("mov %cr0, %eax");
	asm volatile("orl $0x80000000, %eax");
	asm volatile("mov %eax, %cr0");
}

void paging_init()
{
  //kvmmu.kheap_mem_end
	printk("Setting up paging\n");
	printk("Size of Page directory : %d\n",sizeof(page_dir_t));
	page_directory = (page_dir_t*)kvmmu.kheap_mem_end;
	//page_directory = (page_dir_t*)kmalloc(sizeof(page_dir_t));
	page_dir_loc = (uint32_t)page_directory;
	last_page = (pageTable_entry_t*)0x404000;
	for(int j = 0 ; j <128; j++){
	for(int i = 0; i < 1024; i++)
	{
		page_directory[j].entries[i].asUI = 0 | 2;
	}
}
	paging_map_virtual_to_phys(0, 0);
	paging_map_virtual_to_phys(0x400000, 0x400000);
	/*for(uint32_t i = 0; i < 128; i++){
		paging_map_virtual_to_phys((i)*0x400000,i*0x400000);
	}
	*/

	paging_enable();

#ifdef CONFIG_VERBOSE_KERNEL
  printk("Page Directory Set at : %x\n",page_directory);
  printk("Last Page at : 0x%x\n", last_page);
	printk("Paging was successfully enabled!\n");
#endif
}
