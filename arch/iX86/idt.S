#This will set up and load our ID
.global idt_load

idt_load:
    mov 4(%esp), %eax
    lidt (%eax)
    ret
