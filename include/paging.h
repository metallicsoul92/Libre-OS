#ifndef PAGING_H_
#define PAGING_H_


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



//void setupBasicPaging();
void paging_init();


#endif //PAGING_H_
