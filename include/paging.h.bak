#ifndef PAGING_H_
#define PAGING_H_


#include "inlineAssembly.h"

#include "../libc/include/sys/cdefs.h"
#include "registers.h"

typedef struct _page
{
	uint32_t present:1;
	uint32_t rw:1;
	uint32_t user:1;
	uint32_t accessed:1;
	uint32_t dirty:1;
	uint32_t unused:7;
	uint32_t frame:20;
	} page_t;

typedef struct _page_table{
	page_t pages[1024];
	} page_table_t;


typedef struct _page_directory{
	page_table_t *tables[1024];
	uint32_t tablesPhysical[1024];
	uint32_t physicalAddr;
	} page_directory_t;

void initializePaging();
void switchPageDirectory(page_directory_t *new);
page_t *getPage(uint32_t addr, int make, page_directory_t *dir);
void pageFault(regs_t regs);

#endif //Paging.h
