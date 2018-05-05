#ifndef __TASK_H__
#define __TASK_H__

#include "../libc/include/sys/cdefs.h"
#include "config.h"
#if __IX86__ == 1
extern void initTasking();

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct Task {
    Registers regs;
    struct Task *next;
} Task;

 void initTasking();
 void createTask(Task*, void(*)(), uint32_t, uint32_t*);

 void yield(); // Switch task frontend
 #endif // __IX86__
#endif /* __TASK_H__ */
