#ifndef MM_H_
#define MM_H_

#ifdef __IX86__
#include "arch/ix86/mm.h"
#define MEMTYPE uint32_t 
#define MEMBITS 32
#endif

#ifdef __X86_64__
#include "arch/x86_64/mm.h"
#define MEMTYPE uint64_t
#define MEMBITS 64
#endif





#endif
