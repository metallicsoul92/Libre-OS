#ifndef ARCH_I386_REGISTERS_H
#define ARCH_I386_REGISTERS_H

#include "../libc/include/stdio.h"
#include "../libc/include/string.h"



struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

typedef struct regs regs_t;


// IRQ handling
typedef void (*irq_handler_t) (struct regs *);
typedef int (*irq_handler_chain_t) (struct regs *);

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



#endif// ARCH_I386_REGISTERS_H
