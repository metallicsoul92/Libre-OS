#include "../include/paging.h"
#include "../libc/include/sys/cdefs.h"
#include "../include/inlineAssembly.h"

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

  page_dir[0] = ((unsigned int)first_page_table) | 3;

  loadPageDirectory(page_dir);
  enablePaging();
}
