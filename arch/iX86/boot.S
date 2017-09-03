#define ASM_FILE        1
#include "../../include/multiboot.h"

# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot


/* The size of our stack (16KB). */
#define STACK_SIZE                      0x4000

/* The flags for the Multiboot header. */
#ifdef __ELF__
# define MULTIBOOT_HEADER_FLAGS         0x00000003
#else
# define MULTIBOOT_HEADER_FLAGS         0x00010003
#endif


# Declare a header as in the Multiboot Standard.
multiboot_header:
.align  4
      /* magic */
      .long   MULTIBOOT_HEADER_MAGIC
      /* flags */
      .long   MULTIBOOT_HEADER_FLAGS
      /* checksum */
      .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
       /* header_addr */
       .long   multiboot_header
       /* load_addr */
       .long   _start
       /* load_end_addr */
       .long   _edata
       /* bss_end_addr */
       .long   _end
       /* entry_addr */
       .long   multiboot_entry
#endif /* ! __ELF__ */

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
.section .text
# The kernel entry point.
.global _start
.type _start, @function
_start:
jmp     multiboot_entry

multiboot_entry:
        /* Initialize the stack pointer. */
        movl    $(stack + STACK_SIZE), %esp

        /* Reset EFLAGS. */
        pushl   $0
        popf

        /* Push the pointer to the Multiboot information structure. */
        pushl   %ebx
        /* Push the magic value. */
        pushl   %eax

        /* Now enter the C main function... */
        call    kernel_main

        /* Halt. */
        pushl   $halt_message

loop:   hlt
        jmp     loop

halt_message:
        .asciz  "Halted."

        /* Our stack area. */
        .comm   stack, STACK_SIZE

.size _start, . - _start
