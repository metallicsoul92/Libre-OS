# 1 "kernel/kmem.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "kernel/kmem.c"
# 1 "kernel/../include/kmem.h" 1



# 1 "kernel/../include/../libc/include/sys/cdefs.h" 1






typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef unsigned long uintptr_t;



typedef long ssize_t;
# 52 "kernel/../include/../libc/include/sys/cdefs.h"
typedef short dev_t;
typedef char gid_t;
typedef unsigned long ino_t;
typedef unsigned short mode_t;
typedef short nlink_t;
typedef unsigned long off_t;
typedef int pid_t;
typedef short uid_t;
typedef unsigned long zone_t;
typedef unsigned long block_t;
typedef unsigned long bit_t;
typedef unsigned short zone1_t;
typedef unsigned short bitchunk_t;
# 5 "kernel/../include/kmem.h" 2
# 16 "kernel/../include/kmem.h"
uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
# 2 "kernel/kmem.c" 2
# 1 "kernel/../include/config.h" 1
# 3 "kernel/kmem.c" 2
# 1 "kernel/../libc/include/string.h" 1




# 1 "kernel/../libc/include/sys/cdefs.h" 1
# 6 "kernel/../libc/include/string.h" 2

# 1 "kernel/../libc/include/stddef.h" 1
# 10 "kernel/../libc/include/stddef.h"
typedef long unsigned int size_t;
# 20 "kernel/../libc/include/stddef.h"
typedef long int ptrdiff_t;




typedef int wchar_t;
# 8 "kernel/../libc/include/string.h" 2





int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
int strcmp(const char *str1, const char *str2);
char * strcat(const char *source,char * destination);
# 4 "kernel/kmem.c" 2
# 1 "kernel/../include/tty.h" 1



# 1 "kernel/../include/vga.h" 1



# 1 "kernel/../include/../libc/include/stddef.h" 1
# 5 "kernel/../include/vga.h" 2


enum vga_color {
 VGA_COLOR_BLACK = 0,
 VGA_COLOR_BLUE = 1,
 VGA_COLOR_GREEN = 2,
 VGA_COLOR_CYAN = 3,
 VGA_COLOR_RED = 4,
 VGA_COLOR_MAGENTA = 5,
 VGA_COLOR_BROWN = 6,
 VGA_COLOR_LIGHT_GREY = 7,
 VGA_COLOR_DARK_GREY = 8,
 VGA_COLOR_LIGHT_BLUE = 9,
 VGA_COLOR_LIGHT_GREEN = 10,
 VGA_COLOR_LIGHT_CYAN = 11,
 VGA_COLOR_LIGHT_RED = 12,
 VGA_COLOR_LIGHT_MAGENTA = 13,
 VGA_COLOR_LIGHT_BROWN = 14,
 VGA_COLOR_WHITE = 15,
};



static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
 return fg | bg << 4;
}
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
 return (uint16_t) uc | (uint16_t) color << 8;
}

struct __videoInfo{
 uint16_t* videoMemory;
  size_t videoWidth;
   size_t videoHeight;
};

typedef struct __videoInfo _videoInfo;
# 5 "kernel/../include/tty.h" 2

extern _videoInfo videoInfo;

struct __terminalColor{
  uint8_t foreground:4;
  uint8_t background:4;
};

typedef struct __terminalColor _terminalColor;

_terminalColor getColor(uint8_t color);
uint8_t colorTouint8(_terminalColor color);

struct __terminalInfo{
  uint16_t x;
  uint16_t y;
  uint16_t row;
  _terminalColor color;
  uint16_t position;
  uint16_t *buffer;
};

typedef struct __terminalInfo _terminalInfo;

_terminalInfo getTerminalInfo();
_videoInfo getVideoInfo();
extern _terminalInfo terminalInfo;

void initializeTerminal();
void terminalClear();
void terminalUpdateCursor();
void terminalPutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y);
void terminalPutChar(char c);
void terminalWrite(const char* data, size_t size);
void terminalWriteString(const char* data);
void terminalWriteLine(const char * data);
void terminalChangeColor(_terminalColor color);
void terminalChangeColorUint8(uint8_t color);
void terminalNewLine();
void terminalScroll();
int printk(const char *fmt, ...);


void reverse(char s[]);


char * kitoa(int n, char s[]);
char * kitoab(int n, char s[],unsigned int base);
char * kuitoa(int n, char s[]);
char * kuitoab(int n, char s[],unsigned int base);

void sprintk( char * buffer,const char *fmt,...);
# 5 "kernel/kmem.c" 2


# 1 "kernel/../arch/iX86/mm.h" 1




# 1 "kernel/../arch/iX86/../../libc/include/sys/cdefs.h" 1
# 6 "kernel/../arch/iX86/mm.h" 2
# 1 "kernel/../arch/iX86/../../include/config.h" 1
# 7 "kernel/../arch/iX86/mm.h" 2

struct __vmmu_{

  uint32_t kmem_end;
  uint32_t heap_begin;
  uint32_t kheap_mem;
  uint32_t kheap_mem_end;
  uint32_t heap_end;
  uint8_t *pageDesc;
};

typedef struct __vmmu_ _vmmu;

void initMem(_vmmu * vmmu);
# 8 "kernel/kmem.c" 2
_vmmu kvmmu;




extern uint32_t kernel_end;
uint32_t placement_address = (uint32_t)&kernel_end;

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys)
{




    if (align == 1 && (placement_address & 0xFFFFF000) )
    {

        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc_a(uint32_t sz)
{
    return kmalloc_int(sz, 1, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, 0, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, 1, phys);
}

uint32_t kmalloc(uint32_t sz)
{
    return kmalloc_int(sz, 0, 0);
}


void initMem(_vmmu * vmmu ){
                vmmu->kmem_end = (uint32_t)&kernel_end;
                vmmu->heap_begin = vmmu->kmem_end + 0x1000;
                vmmu->kheap_mem_end = 0x400000;
                vmmu->kheap_mem = vmmu->kheap_mem_end - (32 *4096);
                vmmu->heap_end = vmmu->kheap_mem;
                memset((char *)vmmu->heap_begin,0,(vmmu->heap_end - vmmu->heap_begin));
                vmmu->pageDesc = (uint8_t *)kmalloc(32);
                printk("Kernel heap starts at: 0x%x\n",vmmu->heap_begin);
              }
