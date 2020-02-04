#This will set up and load our ID
.global idt_load

idt_load:
    mov 8(%rsp), %rax
    lidt (%rax)
    ret
