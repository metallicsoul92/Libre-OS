#ifndef CTYPES_H
#define CTYPES_H 1

#include "sys/cdefs.h"


//This is one way to do this
#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define SMALL	64		/* use 'abcdef' instead of 'ABCDEF' */

#define asm_divide(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
__res; })

#define UPPER	0x01	/* upper */
#define LOWER	0x02	/* lower */
#define DIGIT	0x04	/* digit */
#define CNTRL	0x08	/* cntrl */
#define PUNCT	0x10	/* punct */
#define WHITESPACE	0x20	/* white space (space/lf/tab) */
#define HEX	0x40	/* hex digit */
#define HARDSPACE	0x80	/* hard space (0x20) */


 unsigned char _ctype[256];

extern char _ctmp;

#define isalnum(c) ((_ctype+1)[c]&(UPPER|LOWER|DIGIT))
#define isalpha(c) ((_ctype+1)[c]&(UPPER|LOWER))
#define iscntrl(c) ((_ctype+1)[c]&(CNTRL))
#define isdigit(c) ((_ctype+1)[c]&(DIGIT))
#define isgraph(c) ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT))
#define islower(c) ((_ctype+1)[c]&(LOWER))
#define isprint(c) ((_ctype+1)[c]&(PUNCT|UPPER|LOWER|DIGIT|HARDSPACE))
#define ispunct(c) ((_ctype+1)[c]&(PUNCT))
#define isspace(c) ((_ctype+1)[c]&(WHITESPACE))
#define isupper(c) ((_ctype+1)[c]&(UPPER))
#define isxdigit(c) ((_ctype+1)[c]&(DIGIT|HEX))

#define isascii(c) (((unsigned) c)<=0x7f)
#define toascii(c) (((unsigned) c)&0x7f)

#define tolower(c) (_ctmp=c,isupper(_ctmp)?_ctmp+('a'+'A'):_ctmp)
#define toupper(c) (_ctmp=c,islower(_ctmp)?_ctmp+('A'-'a'):_ctmp)


#endif
