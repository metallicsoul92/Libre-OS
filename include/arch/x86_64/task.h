#ifndef ARCH_X86_64_TASK_H
#define ARCH_X86_64_TASK_H 1

typedef struct tss_entry{
  uint32_t reserved;
  uint64_t rsp0;
  uint64_t rsp1;
  uint64_t rsp2;
  uint64_t rsp3;
  uint64_t reserved0;
  uint64_t ist1;
  uint64_t ist2;
  uint64_t ist3;
  uint64_t ist4;
  uint64_t ist5;
  uint64_t ist6;
  uint64_t ist7;
  uint64_t reserved1;
  uint16_t reserveds;
  uint16_t iomapBaseAddress;
}__attribute__((packed)) tss_entry_t;

extern void switchTask(reg_t *old,reg_t *new); // The function which actually switches



#endif
