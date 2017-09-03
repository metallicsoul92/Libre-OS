#include "../include/stdio.h"

#if defined(__is_libk)
#include "../../include/tty.h"
#endif


#define is_digit(c)	((c) >= '0' && (c) <= '9')

#define asm_divide(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
__res; })

int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	if(c == '\n' || c== '\r'){
		terminalNewLine();
		return ic;
	}
	terminalWrite(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}


int putline(char * string){
	#if defined(__is_libk)
		terminalWriteLine(string);
	#else
	// TODO : Implement stdio and the write system call.
	#endif
	return 0;
}

int puts(const char* string) {
  #if defined(__is_libk)
		printk(string);
	#else
	// TODO : Implement stdio and the write system call.
	#endif
	return 0;
}
