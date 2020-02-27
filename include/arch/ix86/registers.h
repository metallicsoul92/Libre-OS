#ifndef ARCH_IX86_REGISTERS_H
#define ARCH_IX86_REGISTERS_H


struct registers {

  unsigned int eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
	unsigned short gs, fs, es, ds, cs, ss;
	unsigned int int_no, err_code;
}__attribute__((packed));


#endif
