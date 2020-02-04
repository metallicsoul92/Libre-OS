#ifndef ARCH_X86_64_REGISTERS
#define ARCH_X86_64_REGISTERS


struct registers{

  bit_t rax,rbx,rcx,rdx,rsi,rdi,r8,r9,r10,r11,r12,r13,r14,r15;

 unsigned short rbp;

 unsigned short cs;
 unsigned short ds;
 unsigned short es;
 unsigned short fs;
 unsigned short gs;
 unsigned short ss;
 bit_t irq_no;
 bit_t error;
 bit_t rip;
 bit_t rflags;
 bit_t rsp;
}__attribute__((packed));

#endif
