#ifndef ISR_H
#define ISR_H

#include "registers.h"

#define ISR_COUNT 32

static struct {
	size_t index;
	void (*stub)(void);
} isrs[32 + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void isrs_install_handler(size_t isrs, irq_handler_t handler) {
	isr_routines[isrs] = handler;
}

void isrs_uninstall_handler(size_t isrs) {
	isr_routines[isrs] = 0;
}

void isrs_install(void) {
	char buffer[16];
	for (int i = 0; i < ISR_COUNT; i++) {
		sprintf(buffer, "_isr%d", i);
		isrs[i].index = i;
		isrs[i].stub = symbol_find(buffer);
	}
	isrs[ISR_COUNT].index = 0x7F;
	isrs[ISR_COUNT].stub = symbol_find("_isr127");

	for (int i = 0; i < ISR_COUNT + 1; i++) {
		idt_set_gate(isrs[i].index, isrs[i].stub, 0x08, 0x8E);
	}
}

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

extern void isr0();
extern void isr31();
void isr_handler(regs_t regs){

}


void fault_handler(struct regs * r) {
	irq_handler_t handler = isr_routines[r->int_no];
	if (handler) {
		handler(r);
	} else {

//		debug_print(CRITICAL, "Unhandled exception: [%d] %s", r->int_no, exception_messages[r->int_no]);
	//	HALT_AND_CATCH_FIRE("Process caused an unhandled exception", r);
		while(1) {
      asm volatile ("hlt");
    }
	}
}

#endif // ISR.h
