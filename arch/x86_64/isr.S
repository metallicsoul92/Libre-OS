.global isr0
isr0:
cli #disable interrupts
push $0
push $0
jmp isr_common_stub

.macro ISR_NOERRCODE c=1
.global isr/c
isr/c:
cli
pushb $c
jmp isr_common_stub
.endm

.macro ISR_ERRCODE c=1
.global isr/c
cli
pushb /c
jmp isr_common_stub
.endm

isr_common_stub:
pusha

mov %ds,%ax #
push %eax

call isr_handler

pop %eax
mov %ax,%ds
mov %ax,%es
mov %ax,%fs
mov %ax,%gs
popa
add 8,%esp
sti
iret
