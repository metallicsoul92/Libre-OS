#include "../include/task.h"
#include "../include/kmem.h"
#include "../include/registers.h"

#ifndef HAS_NULL
#define NULL ((void*)0)
#define HAS_NULL 1
#endif


#ifdef __IX86__

static task_t *runningTask;
static task_t mainTask;
static task_t otherTask;


static void otherMain() {
    printk("Hello multitasking world!"); // Not implemented here...
    yield();
}

void initTasking() {
    // Get EFLAGS and CR3
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(mainTask.regs.cr3)::"%eax");
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.regs.eflags)::"%eax");

    createTask_sp(&otherTask, &otherMain, mainTask.regs.eflags, (uint32_t*)mainTask.regs.cr3);
    mainTask.priority = PRIORITY_MEDIUM;
    mainTask.type = TYPE_PROCESS;
    mainTask.next = &otherTask;
    mainTask.prev = NULL;
    mainTask.parent  = NULL;
    mainTask.children = NULL;
    otherTask.next = &mainTask;
    otherTask.prev = &mainTask;
    otherTask.parent = NULL;
    otherTask.children = NULL;
    otherTask.type = TYPE_PROCESS;
    runningTask = &mainTask;
    runningTask->state = STATE_RUNNING;
}

//Dynamically Create task and give it a page directory.
task_t *createTask_p(void(*main)(), uint32_t flags, uint32_t *pagedir){
  task_t * newTask = kmalloc(sizeof(task_t));
  newTask->regs.eax = 0;
  newTask->regs.ebx = 0;
  newTask->regs.ecx = 0;
  newTask->regs.edx = 0;
  newTask->regs.esi = 0;
  newTask->regs.edi = 0;
  newTask->regs.eflags = flags;
  newTask->regs.eip = (uint32_t) main;
  newTask->regs.cr3 = (uint32_t) pagedir;
  newTask->regs.esp = kmalloc(0x1000);
  newTask->priority = PRIORITY_MEDIUM;
  newTask->state = STATE_CREATED;
  newTask->type = TYPE_PROCESS;
  newTask->next = NULL;
  newTask->prev = runningTask;
  newTask->parent = NULL;
  newTask->children = NULL;
  newTask->numChildren = 0;
  newTask->maxChildren = 0;

  return newTask;
}

// Creates a task safely (thru parameter passing), and give it a page directory
void createTask_sp(task_t *task, void (*main)(), uint32_t flags, uint32_t *pagedir) {
    task->regs.eax = 0;
    task->regs.ebx = 0;
    task->regs.ecx = 0;
    task->regs.edx = 0;
    task->regs.esi = 0;
    task->regs.edi = 0;
    task->regs.eflags = flags;
    task->regs.eip = (uint32_t) main;
    task->regs.cr3 = (uint32_t) pagedir;
    task->regs.esp = kmalloc(0x1000);
    task->priority = PRIORITY_MEDIUM;
    task->state = STATE_CREATED;
    task->type = TYPE_PROCESS;
    task->next = NULL;
    task->prev = runningTask;
    task->parent = NULL;
    task->children = NULL;
    task->numChildren = 0;
    task->maxChildren = 0;
}

//TODO: Write a createTask functions to:
//        1.a. Create a task safely (thru parameter passing)
//          b. Alloc page specifically for CR3
//        2.a. Dynamcally create a task
//          b. Alloc page specifically for CR3


void spawnTask_sp(task_t *task, void (*main)(), uint32_t flags, uint32_t *pagedir) {
  task->regs.eax = 0;
  task->regs.ebx = 0;
  task->regs.ecx = 0;
  task->regs.edx = 0;
  task->regs.esi = 0;
  task->regs.edi = 0;
  task->regs.eflags = flags;
  task->regs.eip = (uint32_t) main;
  task->regs.cr3 = (uint32_t) pagedir;
  task->regs.esp = kmalloc(0x1000);
  task->priority = PRIORITY_MEDIUM;
  task->state = STATE_CREATED;
  task->type = TYPE_THREAD;
  task->next = NULL;
  task->prev = NULL;
  task->parent = runningTask;
  task->children = NULL;
  task->numChildren = 0;
  task->maxChildren = 0;


  //If this is the first spawn .
  if(runningTask->maxChildren == 0){
    runningTask->children = kmalloc(sizeof(task_t) * 4); //start off with 4

  }
  //If numChildren equals to maxChildren
  if(runningTask->numChildren == runningTask->maxChildren){
    //Allocate memory for new array multiplied by 2 (until i get a better idea)
    runningTask->maxChildren *=2;
    task_t ** newList = kmalloc(sizeof(task_t) * runningTask->maxChildren);
    memcpy(newList,runningTask->children,sizeof(runningTask->children));

    //TODO: FREE THE DAM CHILDREN BEFORE YOU DO THIS SHIT YOU IDIOT
    //TODO: I CANT STRESS THIS ENOUGH, WHRITE A DAMN KERNEL FREE FUNCTION

    void * garbage = &runningTask->children;
    runningTask->children = newList;
  }
  //Now the checks are over....

  runningTask->children[runningTask->numChildren] = task;
  task->numChild = runningTask->numChildren;
  runningTask->numChildren++;



}

task_t *spawnTask_p(void (*main)(), uint32_t flags, uint32_t *pagedir){
  task_t * newTask = kmalloc(sizeof(task_t));
  newTask->regs.eax = 0;
  newTask->regs.ebx = 0;
  newTask->regs.ecx = 0;
  newTask->regs.edx = 0;
  newTask->regs.esi = 0;
  newTask->regs.edi = 0;
  newTask->regs.eflags = flags;
  newTask->regs.eip = (uint32_t) main;
  newTask->regs.cr3 = (uint32_t) pagedir;
  newTask->regs.esp = kmalloc(0x1000);
  newTask->priority = PRIORITY_MEDIUM;
  newTask->state = STATE_CREATED;
  newTask->type = TYPE_THREAD;
  newTask->next = NULL;
  newTask->prev = NULL;
  newTask->parent = runningTask;
  newTask->children = NULL;
  newTask->numChildren = 0;
  newTask->maxChildren = 0;

  //If this is the first spawn .
  if(runningTask->maxChildren == 0){
    runningTask->children = kmalloc(sizeof(task_t) * 4); //start off with 4

  }
  //If numChildren equals to maxChildren
  if(runningTask->numChildren == runningTask->maxChildren){
    //Allocate memory for new array multiplied by 2 (until i get a better idea)
    runningTask->maxChildren *=2;
    task_t ** newList = kmalloc(sizeof(task_t) * runningTask->maxChildren);
    memcpy(newList,runningTask->children,sizeof(runningTask->children));

    //TODO: FREE THE DAM CHILDREN BEFORE YOU DO THIS SHIT YOU IDIOT
    //TODO: I CANT STRESS THIS ENOUGH, WHRITE A DAMN KERNEL FREE FUNCTION

    void * garbage = &runningTask->children;
    runningTask->children = newList;
  }
  //Now the checks are over....

  runningTask->children[runningTask->numChildren] = newTask;
  newTask->numChild = runningTask->numChildren;
  runningTask->numChildren++;





  return newTask;
}



void yield() {
    task_t *last = runningTask;
    last->state = STATE_WAITING;
    //If no children
    if(runningTask->children == NULL){
      //If no Parent
      if(runningTask->parent == NULL){
          // run next;
              runningTask = runningTask->next;
              switchTask(&last->regs, &runningTask->regs);
      //if there is more then one child process
      }else if(runningTask->parent->numChildren > 1){
          //if you are done with this set of children processes
          if((runningTask->numChild+1) % runningTask->parent->numChildren == 0){

            if(runningTask->parent->next->numChildren == 0){
              // run parents next;
                  runningTask = runningTask->parent->next;
                  switchTask(&last->regs, &runningTask->regs);
            }else
            //run parent's next's children
            runningTask = runningTask->parent->next->children[0];
            switchTask(&last->regs, &runningTask->regs);
        }
          //go to the next children task of parent
            runningTask = runningTask->parent->children[(runningTask->numChild+1) % runningTask->parent->numChildren];
            switchTask(&last->regs, &runningTask->regs);
      }
      //go to child
    }else{

    runningTask = runningTask->children[0];
    switchTask(&last->regs, &runningTask->regs);
  }
  runningTask->state = STATE_RUNNING;
}

#endif
