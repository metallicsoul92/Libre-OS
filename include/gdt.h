#ifndef ARCH_I386_GDT_H
#define ARCH_I386_GDT_H


#include "config.h"
#include "tss.h"
#include "../libc/include/string.h"

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry
{
  #ifdef __IX86__
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
    #endif
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    #ifdef __IX86__
    unsigned short limit;
    unsigned int base;
    #endif
} __attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */
static struct {
  #ifdef __IX86__
    struct gdt_entry entries[6];
    struct gdt_ptr pointer;
    tss_entry_t tss;
    #endif
} gdt __attribute__((used));

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern void gdt_flush();
/* In the future we may need to put a lock on the access of this */
extern void gdt_flush(uintptr_t);

#define ENTRY(X) (gdt.entries[(X)])

void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
  #ifdef __IX86__
  /* Base Address */
	ENTRY(num).base_low = (base & 0xFFFF);
	ENTRY(num).base_middle = (base >> 16) & 0xFF;
	ENTRY(num).base_high = (base >> 24) & 0xFF;
	/* Limits */
	ENTRY(num).limit_low = (limit & 0xFFFF);
	ENTRY(num).granularity = (limit >> 16) & 0X0F;
	/* Granularity */
	ENTRY(num).granularity |= (gran & 0xF0);
	/* Access flags */
	ENTRY(num).access = access;
  #endif
}

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0);

void gdt_install(void) {
  #ifdef __IX86__
	struct gdt_ptr *gdtp = &gdt.pointer;
	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (uintptr_t)&ENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);                /* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data */

	write_tss(5, 0x10, 0x0);

	/* Go go go */
	gdt_flush((uintptr_t)gdtp);
	tss_flush();
  #endif
}

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0) {
  #ifdef __IX86__
	tss_entry_t * tss = &gdt.tss;
	uintptr_t base = (uintptr_t)tss;
	uintptr_t limit = base + sizeof *tss;

	/* Add the TSS descriptor to the GDT */
	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(tss, 0x0, sizeof *tss);

	tss->ss0 = ss0;
	tss->esp0 = esp0;
	tss->cs = 0x0b;
	tss->ss = 0x13;
	tss->ds = 0x13;
	tss->es = 0x13;
	tss->fs = 0x13;
	tss->gs = 0x13;

	tss->iomap_base = sizeof *tss;
  #endif
}

void set_kernel_stack(uintptr_t stack) {
  #ifdef __IX86__
  /* Set the kernel stack */
	gdt.tss.esp0 = stack;
  #endif
}

#endif
