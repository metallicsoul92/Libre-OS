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
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t eflags;
    uint32_t cr3;
} reg_t;


//I Still dont know how i should go about this lol, lets see how well this works
//Im deciding to use not only a doubly linked list, but kinda like a map type
//data structure?
typedef struct Task {
    reg_t regs;
    struct Task *prev;
    struct Task *next;
    struct Task *parent;
    struct Task **children;
    uint32_t numChild; //index into parent's children index
    uint32_t numChildren;
    uint32_t maxChildren;
} task_t;

 void createTask_sp(task_t*, void(*)(), uint32_t, uint32_t*);
 task_t *createTask_p(void(*main)(), uint32_t flags, uint32_t *pagedir);
 void spawnTask_sp(task_t *task, void (*main)(), uint32_t flags, uint32_t *pagedir);
 task_t *spawnTask_p(void (*main)(), uint32_t flags, uint32_t *pagedir);


 void yield(); // Switch task frontend
 #endif // __IX86__
#endif /* __TASK_H__ */
