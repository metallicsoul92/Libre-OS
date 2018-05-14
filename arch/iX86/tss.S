#And this sets up the task segment selector if im not mistaken
.global tss_flush

tss_flush:
    mov $0x2B, %ax
    ltr %ax
    ret
