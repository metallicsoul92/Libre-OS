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
#ifdef CONFIG_IX86_NON_PAE_

static page_dir_t * page_directory = 0;
//pageTableEntry_t * last_page = 0;
static uint32_t page_dir_loc = 0;

#endif


#ifdef CONFIG_IX86_PAE_
//OSDEV STUFF
static ptpd_t * pageDirPtrTab = 0;
uint64_t page_dir_ptr_tab[4] __attribute__((aligned(0x20))); // must be aligned to (at least)0x20, ...
    // ... turning out that you can put more of them into one page, saving memory
// 512 entries
uint64_t page_dir[512] __attribute__((aligned(0x1000)));  // must be aligned to page boundary
uint64_t page_tab[512] __attribute__((aligned(0x1000))); //512 page table entries....
uint16_t currentEnt = 0;
uint16_t currentTab = 0;
uint8_t currentDir =0;

#endif
pageTableEntry_t * last_page = 0;

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
/*

	Ok, so ..... Right now mapping virtual to physical consists of:
	 a frame index [idx], which is the top 10 bits of the virtual address,
	 and the 22 bits which are the offset in the page .... Let me see something

	 so now how am i gonna do this with PAE? 64 bits each? Who the hell knows...



*/

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
#ifdef CONFIG_IX86_NON_PAE_
	uint16_t id = virt >> 22;
	#ifdef CONFIG_VERBOSE_KERNEL
		printk("id 0x%x, virtual: 0x%x\n", id, virt);
		#endif// verbose kernel output
		for(int i = 0; i < 1024; i++)
		{

			#ifdef CONFIG_VERBOSE_KERNEL
				printk("Physical Address Being mapped: 0x%x\n",phys);
			#endif// verbose kernel output
			last_page[i].asUI = phys | 3;
			phys += 4096;
		}
		page_directory[id].entries[id].asUI = ((uint32_t)last_page) | 3;
		last_page = (pageTableEntry_t *)(((uint32_t)last_page) + 4096);

		#ifdef CONFIG_VERBOSE_KERNEL
		printk("Mapping 0x%x(%d) to 0x%x\n", virt, id, phys);
		#endif // verbose kernel output
#endif //Config NON PAE for ix86

#ifdef CONFIG_IX86_PAE_
	uint16_t id = virt >> 22;
	/* Ok Hear me out..... Im gonna try to determine via currentTab and currentDir
	 which table entry to map.... */
	#ifdef CONFIG_VERBOSE_KERNEL
		printk("id 0x%x, virtual: 0x%x\n", id, virt);
	#endif// verbose kernel output
	for(int i = 0; i < 512; i++)
	{
		#ifdef CONFIG_VERBOSE_KERNEL
			printk("Physical Address Being mapped: 0x%x\n",phys);
		#endif// verbose kernel output
		pageDirPtrTab->directories[currentDir].entries[currentDir].asUI = phys | 3;
		phys += 8192;
	}
	currentTab++;
	page_dir_ptr_tab[currentDir] = ((uint32_t)last_page) | 3;
	last_page = (pageTableEntry_t *)(((uint32_t)last_page) + 8192);
#endif
}

void paging_enable()
{
	#ifdef CONFIG_IX86_PAE_
		asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // set bit5 in CR4 to enable PAE
		asm volatile("mov %%eax, %%cr3": :"a"(&page_dir_ptr_tab));
	#endif
	#ifdef CONFIG_IX86_NON_PAE_
		asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc));
	#endif
		asm volatile("mov %cr0, %eax");
		asm volatile("orl $0x80000000, %eax");
		asm volatile("mov %eax, %cr0");
}

void paging_init()
{
  //kvmmu.kheap_mem_end
	printk("Setting up paging\n");

#ifdef CONFIG_IX86_NON_PAE_
	printk("Size of Page directory structure : %d\n",sizeof(page_dir_t));
	page_directory = (page_dir_t*)kvmmu.kheap_mem_end;
	//page_directory = (page_dir_t*)kmalloc(sizeof(page_dir_t));
	page_dir_loc = (uint32_t)page_directory;
	last_page = (pageTableEntry_t*)0x404000;
	for(int j = 0 ; j <128; j++){
		for(int i = 0; i < 1024; i++)
		{
			page_directory[j].entries[i].asUI = 0 | 3;
		}
	}
	paging_map_virtual_to_phys(0, 0);
	paging_map_virtual_to_phys(0x400000, 0x400000);
	//I am trying to get the size of the full page directory
	//Im not sure if its gonna be correct tho, it should be ... 4 Mib???

	printk("Size of Page Directory variable: %d\n", *page_directory);
	/*for(uint32_t i = 0; i < 128; i++){
		paging_map_virtual_to_phys((i)*0x400000,i*0x400000);
	}
	*/
	#ifdef CONFIG_VERBOSE_KERNEL
	  printk("Page Directory Set at : %x\n",page_directory);
	  printk("Last Page at : 0x%x\n", last_page);
		printk("Paging was successfully enabled!\n");
	#endif

#endif //CONFIG_IX86_NON_PAE_

#ifdef CONFIG_IX86_PAE_
	page_dir_ptr_tab[0] = (uint64_t)&page_dir | 1; // set the page directory into the PDPT and mark it present
	page_dir[0] = (uint64_t)&page_tab | 3; //set the page table into the PD and mark it present/writable
	pageDirPtrTab = &page_dir_ptr_tab;
	last_page = (pageTableEntry_t*)0x404000;
	unsigned int i, address = 0;
		for(i = 0; i < 512; i++)
		{
			#ifdef CONFIG_VERBOSE_KERNEL
			//	printk("Physical Address Being mapped: 0x%x\n",address);
			#endif
    	page_tab[i] = address | 3; // map address and mark it present/writable
    	address = address + 0x1000;
		}
		currentDir++; //Right? i map the first page,
									//no need to iterate over currentTab
	paging_map_virtual_to_phys(0, 0);
	paging_map_virtual_to_phys(0x400000, 0x400000);
	/*for(uint32_t i = 0; i < 128; i++){
		paging_map_virtual_to_phys((i)*0x400000,i*0x400000);
	}
	*/
#endif


	paging_enable();


}
