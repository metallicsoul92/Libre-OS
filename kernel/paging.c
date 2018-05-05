#include "../include/config.h"
#include "../include/paging.h"
#include "../libc/include/sys/cdefs.h"
#include "../include/inlineAssembly.h"
#include "../include/tty.h"

uint32_t page_dir[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();


void setupBasicPaging(){

  for(int i =0; i < 1024; i++){
    page_dir[i] = 0x00000002;
  }

  for(int j=0; j < 1024; j++){
    first_page_table[j] = (j * 0x1000) | 3;
  }
  #ifdef CONFIG_VERBOSE_KERNEL
  printk("page directory at %x\npageTable at: %x\n",page_dir,first_page_table);
  #endif
  page_dir[0] = ((unsigned int)first_page_table) | 3;

  loadPageDirectory(page_dir);
  enablePaging();
}
