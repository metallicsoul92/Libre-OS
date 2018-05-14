#ifndef __TASK_H__
#define __TASK_H__



#include "config.h"

#ifndef HAS_CDEFS
#include "../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif


#if __IX86__ == 1
extern void initTasking();

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct Task {
    Registers regs;
    struct Task *next;
} Task;

 void createTask(Task*, void(*)(), uint32_t, uint32_t*);

 void yield(); // Switch task frontend
 #endif // __IX86__
#endif /* __TASK_H__ */
