#ifndef PAGING_H_
#define PAGING_H_

#include "config.h"

#include "../libc/include/stdint.h"



#ifdef CONFIG_NON_PAE_
    #define PAGE_SHIFT 12
    #define PAGE_SIZE ((uint32_t)1<<PAGE_SHIFT)
    #define BPP 32
    #define PAGE_MASK (~(PAGE_SIZE-1))
    #define PAGE_ALIGN(addr) (((addr)+PAGE_SIZE-1)&PAGE_MASK)
    #define PTRMASK (~(sizeof(void*)-1))
    #define SZ_PTR_LOG_2 2
    /* to find an entry in a page-table-directory */
    #define PAGE_DIR_OFFSET(base,address)	((unsigned long*)((base)+\
    ((unsigned long)(address)>>(PAGE_SHIFT-SIZEOF_PTR_LOG2)*2&PTR_MASK&~PAGE_MASK)))
    /* to find an entry in a page-table */
    #define PAGE_PTR(address)		\
    ((unsigned long)(address)>>(PAGE_SHIFT-SIZEOF_PTR_LOG2)&PTR_MASK&~PAGE_MASK)
    /* the no. of pointers that fit on a page */
    #define PTRS_PER_PAGE			(PAGE_SIZE/sizeof(void*))

    typedef struct _page_table_entry_int{
      uint8_t present:1;
      uint8_t rw:1;
      uint8_t user:1;
      uint8_t writeThru:1;
      uint8_t cacheDisabled:1;
      uint8_t accessed:1;
      uint8_t reserved:1; //always 0?
      uint8_t dirty:1; // always 0 for 4kb
      uint8_t ignored:1;
      uint8_t unused:3;
      uint32_t pAddr:20;
    } pageTableEntry_int_t __attribute__((aligned(4)));

    typedef union _pagetable_int{
      pageTableEntry_int_t asPDIT;
      uint32_t asUI;
    } pageTableEntry_t __attribute__((aligned(4)));

    typedef struct _page_dir_entry_int{
      uint8_t present:1;
      uint8_t rw:1;
      uint8_t user:1;
      uint8_t writeThru:1;
      uint8_t dirty:1;
      uint8_t accessed:1;
      uint8_t reserved:1; //always 0?
      uint8_t pageSize:1; // always 0 for 4kb
      uint8_t ignored:1;
      uint8_t unused:3;
      uint32_t ptableAddr:20; //page table physical address
    } pageDir_entry_int_t __attribute__((aligned(4)));

    typedef union _pageDir_entry{
      pageDir_entry_int_t asPDIT;
      uint32_t asUI;
    } pageDir_entry_t __attribute__((aligned(4)));

    typedef struct pageDirectory{
      pageDir_entry_t entries[1024];
    } page_dir_t;
#endif

//Ok so 64-bit structure, bits 36-63 are ignored... 27 bits ....
//Physical address is extended to 24 bytes
#ifdef CONFIG_PAE_

typedef struct _page_table_entry_int{
  uint8_t present:1;
  uint8_t rw:1;
  uint8_t user:1;
  uint8_t writeThru:1;
  uint8_t cacheDisabled:1;
  uint8_t accessed:1;
  uint8_t reserved:1; //always 0?
  uint8_t dirty:1; // always 0 for 4kb
  uint8_t ignored:1;
  uint8_t unused:3;
  uint32_t pAddr:24;
  uint32_t padding:27;// ??
} pageTableEntry_int_t __attribute__((aligned(8)));

typedef union _pagetable_int{
  pageTableEntry_int_t asPDIT;
  uint64_t asUI;
} pageTableEntry_t __attribute__((aligned(8)));

typedef struct _page_dir_entry_int{
  uint8_t present:1;
  uint8_t rw:1;
  uint8_t user:1;
  uint8_t writeThru:1;
  uint8_t dirty:1;
  uint8_t accessed:1;
  uint8_t reserved:1; //always 0?
  uint8_t pageSize:1; // always 0 for 4kb
  uint8_t ignored:1;
  uint8_t unused:3;
  uint32_t ptableAddr:24; //page table physical address
  uint32_t padding:27;
} pageDir_entry_int_t __attribute__((aligned(8)));

typedef union _pageDir_entry{
  pageDir_entry_int_t asPDIT;
  uint64_t asUI;
} pageDir_entry_t __attribute__((aligned(4)));

typedef struct pageDirectory{
  pageDir_entry_t entries[512];
} page_dir_t;

typedef struct ptpd{
  page_dir_t directories[4];
  } ptpd_t;
#endif

//void setupBasicPaging();
void paging_init();
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);


#endif //PAGING_H_
