#ifndef __TASK_H__
#define __TASK_H__



#include "config.h"

#ifndef HAS_CDEFS
#include "../libc/include/sys/cdefs.h"
#define HAS_CDEFS 1
#endif



#define PRIORITY_LOWEST       1
#define PRIORITY_LOWER        2
#define PRIORTIY_LOW          3
#define PRIORITY_MEDIUM       4
#define PRIORITY_HIGH         5
#define PRIORITY_HIGHER       6
#define PRIORITY_HIGHEST      7

#define STATE_CREATED         1
#define STATE_WAITING         2
#define STATE_BLOCKED         3
#define STATE_TERMINATED      4
#define STATE_SWAPPED_WAITING 5
#define STATE_SWAPPED_BLOCKED 6
#define STATE_RUNNING         7

#define TYPE_PROCESS          1
#define TYPE_THREAD           2


#if __IX86__ == 1
extern void initTasking();

#include "registers.h"
//I Still dont know how i should go about this lol, lets see how well this works
//Im deciding to use not only a doubly linked list, but kinda like a map type
//data structure?
typedef struct Task {
    regs_t regs;
    uint8_t priority;
    uint8_t state;
    uint8_t type;
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
