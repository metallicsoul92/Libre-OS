#ifndef REGISTERS_H
#define REGISTERS_H

#include  "config.h"
#include "../libc/include/stdio.h"
#include "../libc/include/string.h"


#ifdef __IX86__
#include "arch/ix86/registers.h"
#endif

#ifdef _X86_64_
#include "arch/x86_64/registers.h"
#endif

typedef struct registers regs_t;



// IRQ handling
typedef void (*irq_handler_t) (regs_t *);
typedef int (*irq_handler_chain_t) (regs_t *);

//Kernel Symbols
typedef struct {
	uintptr_t addr;
	char name[];
} kernel_symbol_t;

extern char kernel_symbols_start[];
extern char kernel_symbols_end[];

//How to find the symbols
inline void (* symbol_find(const char * name))(void) {
	kernel_symbol_t * k = (kernel_symbol_t *)&kernel_symbols_start;

	while ((uintptr_t)k < (uintptr_t)&kernel_symbols_end) {
		if (strcmp(k->name, name)) {
			k = (kernel_symbol_t *)((uintptr_t)k + sizeof *k + strlen(k->name) + 1);
			continue;
		}
		return (void (*)(void))k->addr;
	}

	return NULL;
}



#endif//REGISTERS_H
