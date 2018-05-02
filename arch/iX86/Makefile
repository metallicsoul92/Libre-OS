CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -g -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

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
paging.o


all : $(ASMOBJS)
.S.o:
	${CC} -c $< -o $(BINDIR)/$@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f ${BINDIR}/${ASMOBJS} *.o */*.o
