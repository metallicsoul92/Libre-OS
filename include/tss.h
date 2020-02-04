#ifndef TSS_H
#define TSS_H

#include "../libc/include/sys/cdefs.h"
#include "config.h"

#ifdef __IX86__
#include "../arch/iX86/task.h"
#endif

#ifdef __X86_64__
#include "../arch/x86_64/task.h"
#endif


extern void tss_flush(void);




#endif /* ARCH_I386_TSS_H */
