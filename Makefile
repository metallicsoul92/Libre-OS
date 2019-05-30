CFLAGS= -O2 -g -ffreestanding -Wall -Wextra

PHONY+= build-ix86 build-ix86-host build-x86_64 build-arm
PHONY+= link-ix86 link-ix86-host link-x86_64 link-arm
PHONY+= clean
.PHONY= $(PHONY)



BINDIR?=bin
KERNELBINDIR?=$(BINDIR)/kernel
KERNELASMBINDIR?=$(KERNELBINDIR)/asm
DRIVERSBINDIR?=$(BINDIR)/drivers
LIBCBINDIR?=$(BINDIR)/libc
TOOLSDIR?=tools
TOOLSARCHDIR?=$(TOOLSDIR)/arch

LIBS= -nostdlib -L$(LIBCBINDIR) -lk -lgcc


ASMOBJS?=\
$(KERNELASMBINDIR)/boot.o \
$(KERNELASMBINDIR)/tss.o \
$(KERNELASMBINDIR)/gdt.o \
$(KERNELASMBINDIR)/idt.o \
$(KERNELASMBINDIR)/irq.o \
$(KERNELASMBINDIR)/isr.o \
$(KERNELASMBINDIR)/switch.o\
$(KERNELASMBINDIR)/paging.o

KERNELOBJS=\
$(ASMOBJS) \
$(KERNELBINDIR)/kmem.o\
$(KERNELBINDIR)/paging.o\
$(KERNELBINDIR)/tty.o\
$(KERNELBINDIR)/task.o\
$(KERNELBINDIR)/cmos.o \
$(KERNELBINDIR)/cpufeatures.o\
$(KERNELBINDIR)/kernel.o

DRIVERSOBJS=\
$(DRIVERSBINDIR)/ata.o\
$(DRIVERSBINDIR)/fs/vfs/vfs.o

LINK_LIST_ix86?=\
$(KERNELASMBINDIR)/crti.o \
$(TOOLSARCHDIR)/iX86/crtbegin.o \
$(KERNELOBJS) \
$(DRIVERSOBJS) \
$(LIBS) \
$(TOOLSARCHDIR)/iX86/crtend.o \
$(KERNELASMBINDIR)/crtn.o


build-ix86:
	cd libc && make all CC=i686-elf-gcc AS=i686-elf-as LD=i686-elf-ld
	cd kernel && make ix86 CC=i686-elf-gcc AS=i686-elf-as LD=i686-elf-ld
	cd drivers && make CC=i686-elf-gcc LD=i686-elf-ld

build-ix86-host:
	cd libc && make all 
	cd kernel && make ix86 
	cd drivers && make 

link-ix86:
	i686-elf-gcc -T $(TOOLSARCHDIR)/iX86/ix86.ld -o $(BINDIR)/kernel.ix86 $(CFLAGS) $(LINK_LIST_ix86)
	./scripts/confirmMB.sh

link-ix86-host:
	CC -T $(TOOLSARCHDIR)/iX86/ix86.ld -o $(BINDIR)/kernel.ix86 $(CFLAGS) $(LINK_LIST_ix86)
	./scripts/confirmMB.sh


clean:
	cd include && rm config.h
	cd libc && make clean
	cd kernel && make clean
	cd drivers && make clean
	cd bin && rm kernel.*
	rm -rf isodir
	rm LibreOS.iso
