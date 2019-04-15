#ifndef LIBC_WCHAR_H_
#define LIBC_WCHAR_H_

#ifndef HAS_WCHAR_T
typedef int wchar_t;
#define HAS_WCHAR_T 1
#endif

#ifndef HAS_WINT_T
typedef unsigned int wint_t;
#define HAS_WINT_T 1
#endif

#ifndef HAS_WCTYPE_T
typedef unsigned long int wctype_t;
#define HAS_WCTYPE_T 1
#endif

#ifndef HAS_SIZE_T
typedef long unsigned int size_t;
#define HAS_SIZE_T 1
#endif

#ifndef HAS_VARG
typedef unsigned char * va_list;
#define HAS_VARG 1
#endif

#ifndef LIBC_ENDIAN_H_
#define REVERSE_LONG(n) ((unsigned long) (((n & 0xFF) << 24) | \
                                          ((n & 0xFF00) << 8) | \
                                          ((n & 0xFF0000) >> 8) | \
                                          ((n & 0xFF000000) >> 24)))
#else
#include <endian.h>
#endif

#ifndef HAS_IOLOCK
typedef void _IO_lock_t;
#define HAS_IOLOCK 1
#endif


#ifndef HAS_FILE
struct __IO_FILE{
    int _flags;
    //Read
    char* _read_ptr;	/* Current read pointer */
    char* _read_end;	/* End of get area. */
    char* _read_base;	/* Start of putback+get area. */
    //Write
    char* _write_base;	/* Start of put area. */
    char* _write_ptr;	/* Current put pointer. */
    char* _write_end;	/* End of put area. */
   //Buffer
    char* _buf_base;	/* Start of reserve area. */
    char* _buf_end;	/* End of reserve area. */
    /* Base */
    char *_save_base; /* Pointer to start of non-current get area. */
    char *_backup_base;  /* Pointer to first valid character of backup area */
    char *_save_end; /* Pointer to end of non-current get area. */
    struct _IO_marker *_markers;

    struct _IO_FILE *_chain;

    int _fileno;  //file descriptor
  #if 0
    int _blksize;
  #else
    int _flags2;
  #endif
    off_t _old_offset; /* This used to be _offset but it's too small.  */

  #define __HAS_COLUMN /* temporary */
    /* 1+column number of pbase(); 0 is unknown. */
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];

    /*  char* _save_gptr;  char* _save_egptr; */

    _IO_lock_t *_lock;
};


typedef struct  __IO_FILE __FILE;
typedef __FILE FILE;
#define HAS_FILE 1
#endif

#ifndef HAS_NULL
#define NULL ((void*)0)
#define HAS_NULL 1
#endif

#ifndef HAS_MBSTATE_T
struct _mbstate{
  int _count;
  union{
    wint_t _wch;
    char _wchb[4];
  }__value;
};

typedef struct _mbstate mbstate_t;
#define HAS_MBSTATE_T 1
#endif


enum {
  __wcUpper = 0, // Uppercase
  __wcLower = 1, // Lowercase
  __wcAlpha = 2, //Alphabetic
  __wcDigit = 3, //Digit
  __wcHexDigit =4, //Hex Digit
  __wcSpace = 5, //Space
  __wcPrint = 6, //Printing
  __wcGraph = 7, //Graphcial
  __wcBlack = 8, //Black
  __wcControl = 9, //Control
  __wcPunctuation = 10, //Punctuation
  __wcAlpaNumeric = 11, //Alpha Numeric

  __wcRUpper = REVERSE_LONG(__wcUpper),
  __wcRLower = REVERSE_LONG(__wcLower),
  __wcRAplha = REVERSE_LONG(__wcAlpha),
  __wcRDigit = REVERSE_LONG(__wcDigit),
  __wcRHexDigit = REVERSE_LONG(__wcHexDigit),
  __wcRSpace = REVERSE_LONG(__wcSpace),
  __wcRPrint = REVERSE_LONG(__wcPrint),
  __wcRGraph = REVERSE_LONG(__wcGraph),
  __wcRBlack = REVERSE_LONG(__wcBlack),
  __wcRControl = REVERSE_LONG(__wcControl),
  __wcRPunctuation = REVERSE_LONG(__wcPunctuation),
  __wcRAlpaNumeric = REVERSE_LONG(__wcAlpaNumeric)
}




//Functions
wint_t        btowc(int);
wint_t        fgetwc(FILE*);
wchar_t      *fgetws(wchar_t * restrict, int, FILE *restrict);
wint_t        fputwc(wchar_t,FILE *);
int           fputws(const wchar_t *restrict, FILE *restrict);
int           fwide(FILE*, int);
int           fwprintf(FILE*restrict, const wchar_t *restrict, ...);
int           fwscanf(FILE*restrict, const wchar_t *restrict, ...);
wint_t        getwc(FILE*);
wint_t        getwchar(void);
int           iswalnum(wint_t);
int           iswalpha(wint_t);
int           iswcntrl(wint_t);
int           iswctype(wint_t,wctype_t);
int           iswdigit(wint_t);
int           iswgraph(wint_t);
int           iswlower(wint_t);
int           iswprint(wint_t);
int           iswpunct(wint_t);
int           iswspace(wint_t);
int           iswupper(wint_t);
int           iswxdigit(wint_t);
size_t        mbrlen(const char *restrict, size_t, mbstate_t *restrict);
size_t        mbrtowc(wchar_t * restrict, const char *restrict, size_t,mbstate_t *restrict);
int           mbsinit(const mbstate_t *);
size_t        mbsnrtowcs(wchar_t * restrict, const char **restrict, size_t, size_t, mbstate_t *restrict);
size_t        mbsrtowcs(wchar_t * restrict, const char **restrict, size_t,mbstate_t *restrict);
FILE         *open_wmemstream(wchar_t**, size_t *);
wint_t        putwc(wchar_t,FILE *);
wint_t        putwchar(wchar_t);
int           swprintf(wchar_t * restrict, size_t,const wchar_t *restrict, ...);
int           swscanf(const wchar_t *restrict,const wchar_t *restrict, ...);
wint_t        towlower(wint_t);
wint_t        towupper(wint_t);
wint_t        ungetwc(wint_t,FILE *);
int           vfwprintf(FILE*restrict, const wchar_t *restrict, va_list);
int           vfwscanf(FILE*restrict, const wchar_t *restrict, va_list);
int           vwprintf(const wchar_t *restrict, va_list);
int           vswprintf(wchar_t * restrict, size_t,const wchar_t *restrict, va_list);
int           vswscanf(const wchar_t *restrict, const wchar_t *restrict,va_list);
int           vwscanf(const wchar_t *restrict, va_list);
wchar_t      *wcpcpy(wchar_t restrict*, const wchar_t *restrict);
wchar_t      *wcpncpy(wchar_t restrict *, const wchar_t *restrict, size_t);
size_t        wcrtomb(char * restrict, wchar_t, mbstate_t *restrict);
int           wcscasecmp(const wchar_t *, const wchar_t *);
int           wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);
wchar_t      *wcscat(wchar_t * restrict, const wchar_t *restrict);
wchar_t      *wcschr(const wchar_t *, wchar_t);
int           wcscmp(const wchar_t *, const wchar_t *);
int           wcscoll(const wchar_t *, const wchar_t *);
int           wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
wchar_t      *wcscpy(wchar_t* restrict, const wchar_t *restrict);
size_t        wcscspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsdup(const wchar_t *);
size_t        wcsftime(wchar_t * restrict, size_t,const wchar_t *restrict, const struct tm *restrict);
size_t        wcslen(const wchar_t *);
int           wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
int           wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t,locale_t);
wchar_t      *wcsncat(wchar_t * restrict, const wchar_t *restrict, size_t);
int           wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wcsncpy(wchar_t * restrict, const wchar_t *restrict, size_t);
size_t        wcsnlen(const wchar_t *, size_t);
size_t        wcsnrtombs(char*, const wchar_t **, size_t, size_t,mbstate_t *);
wchar_t      *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t      *wcsrchr(const wchar_t *, wchar_t);
size_t        wcsrtombs(char * restrict, const wchar_t **restrict,size_t, mbstate_t *restrict);
size_t        wcsspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsstr(const wchar_t *restrict, const wchar_t *restrict);
double        wcstod(const wchar_t *restrict, wchar_t **restrict);
float         wcstof(const wchar_t *restrict, wchar_t **restrict);
wchar_t      *wcstok(wchar_t * restrict, const wchar_t *restrict,wchar_t **restrict);
long          wcstol(const wchar_t *restrict, wchar_t **restrict, int);
long double   wcstold(const wchar_t *restrict, wchar_t **restrict);
long long     wcstoll(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long wcstoul(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long longwcstoull(const wchar_t *restrict, wchar_t **restrict, int);
int           wcswidth(const wchar_t *, size_t);
size_t        wcsxfrm(wchar_t * restrict, const wchar_t *restrict, size_t);
size_t        wcsxfrm_l(wchar_t * restrict, const wchar_t *restrict,size_t, locale_t);
int           wctob(wint_t);
wctype_t      wctype(const char *);
int           wcwidth(wchar_t);
wchar_t      *wmemchr(const wchar_t *, wchar_t, size_t);
int           wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemcpy(wchar_t * restrict, const wchar_t *restrict, size_t);
wchar_t      *wmemmove(wchar_t*, const wchar_t *, size_t);
wchar_t      *wmemset(wchar_t*, wchar_t, size_t);
int           wprintf(const wchar_t *restrict, ...);
int           wscanf(const wchar_t *restrict, ...);


#endif
