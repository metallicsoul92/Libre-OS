LIBS:=$(LIBS) -nostdlib -lk -lgcc
CFLAGS:=$(CFLAGS) -mno-red-zone

BINDIR=../../bin/kernel/asm

.PHONY: all clean
.SUFFIXES: .S .o

ASMOBJS=\
boot.o\
crti.o\
crtn.o\
tss.o\
gdt.o\
idt.o\
irq.o\
isr.o\
switch.o\




all : $(ASMOBJS)
.S.o:
	${CC} -c $< -o $(BINDIR)/$@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f ${BINDIR}/${ASMOBJS} *.o */*.o
