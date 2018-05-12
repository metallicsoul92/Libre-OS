#include "../include/tty.h"
#include "../include/inlineAssembly.h"
#include "../libc/include/string.h"
#include "../libc/include/stdarg.h"
#include "../libc/include/stdio.h"
#include "../libc/include/stdbool.h"
#include "../libc/include/limits.h"


/* The I/O ports */
#define TTY_COMMAND_PORT         0x3D4
#define TTY_DATA_PORT            0x3D5

/* The I/O port commands */
#define TTY_HIGH_BYTE_COMMAND    14
#define TTY_LOW_BYTE_COMMAND     15


_videoInfo videoInfo;
_terminalInfo terminalInfo;


_terminalInfo *getTerminalInfo(){
  return &terminalInfo;
}

_videoInfo *getVideoInfo(){
  return &videoInfo;
}

static uint16_t s_buffer[80*1024];

_terminalColor getColor(uint8_t color){
  _terminalColor out;
    out.foreground =  color & 0xFF;
    out.background = color >> 4;

    return out;
}

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

char * kitoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     return s;
 }

 char * klltoa(long long n, char s[])
  {
      long long i, sign;

      if ((sign = n) < 0)  /* record sign */
          n = -n;          /* make n positive */
      i = 0;
      do {       /* generate digits in reverse order */
          s[i++] = n % 10 + '0';   /* get next digit */
      } while ((n /= 10) > 0);     /* delete it */
      if (sign < 0)
          s[i++] = '-';
      s[i] = '\0';
      reverse(s);
      return s;
  }

  char * kulltoa(unsigned long long n, char s[])
   {
       long long i, sign;

       if ((sign = n) < 0)  /* record sign */
           n = -n;          /* make n positive */
       i = 0;
       do {       /* generate digits in reverse order */
           s[i++] = n % 10 + '0';   /* get next digit */
       } while ((n /= 10) > 0);     /* delete it */
       if (sign < 0)
           s[i++] = '-';
       s[i] = '\0';
       reverse(s);
       return s;
   }

   char * kulltoab(unsigned long long n, char s[],unsigned int base)
    {
        long long i, sign;

        if ((sign = n) < 0)  /* record sign */
            n = -n;          /* make n positive */
        i = 0;
        do {       /* generate digits in reverse order */
          s[i++] =  "0123456789ABCDEF"[n % base];   /* get next digit */
        } while ((n /= 10) > 0);     /* delete it */
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
        return s;
    }

 char * kitoab(int n, char s[],unsigned int base)
  {
      int i, sign;

      if ((sign = n) < 0)  /* record sign */
          n = -n;          /* make n positive */
      i = 0;
      do {       /* generate digits in reverse order */
          s[i++] =  "0123456789ABCDEF"[n % base];   /* get next digit */
      } while ((n /= base) > 0);     /* delete it */
      if (sign < 0)
          s[i++] = '-';
      s[i] = '\0';
      reverse(s);
      return s;
  }
  char * kuitoa(int n, char s[])
   {
       int i;

       i = 0;
       do {       /* generate digits in reverse order */
           s[i++] = n % 10 + '0';   /* get next digit */
       } while ((n /= 10) > 0);     /* delete it */

       s[i] = '\0';
       reverse(s);
       return s;
   }

   char * kuitoab(int n, char s[],unsigned int base)
    {
        int i, sign;

        i = 0;
        do {       /* generate digits in reverse order */
            s[i++] =  "0123456789ABCDEF"[n % base];   /* get next digit */
        } while ((n /= base) > 0);     /* delete it */

        s[i] = '\0';
        reverse(s);
        return s;
    }



uint8_t colorTouint8(_terminalColor color){
    return vga_entry_color(color.foreground,color.background);
}

void initializeTerminal(){
  videoInfo.videoMemory = (uint16_t*)0xB8000;
  videoInfo.videoWidth = 80;
  videoInfo.videoHeight = 25;

  terminalInfo.x = 0;
  terminalInfo.y = 0;
  terminalInfo.row = 0;
  terminalInfo.position =0;
  terminalInfo.color = getColor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminalInfo.buffer = videoInfo.videoMemory;
  terminalClear();
  terminalUpdateCursor();

}

void terminalClear(){
  for (size_t y = 0; y < videoInfo.videoHeight; y++) {
		for (size_t x = 0; x < videoInfo.videoWidth; x++) {
			const size_t index = y * videoInfo.videoWidth + x;
			terminalInfo.buffer[index] = vga_entry(' ', colorTouint8(terminalInfo.color));
		}
	}
}
void terminalUpdateCursor(){
   terminalInfo.position = terminalInfo.y * 80 + terminalInfo.x;
   outb(TTY_COMMAND_PORT, TTY_HIGH_BYTE_COMMAND);
        outb(TTY_DATA_PORT,    ((terminalInfo.position >> 8) & 0x00FF));
        outb(TTY_COMMAND_PORT, TTY_LOW_BYTE_COMMAND);
        outb(TTY_DATA_PORT,    terminalInfo.position & 0x00FF);
  }

void terminalPutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * videoInfo.videoWidth + x;
	terminalInfo.buffer[index] = vga_entry(c, color);
  s_buffer[index] = vga_entry(c,color);
}


void terminalPutChar(char c){
	unsigned char uc = c;
  //if the max with has been reached
	if (++terminalInfo.x == videoInfo.videoWidth) {
    //set terminal x to 0
		terminalInfo.x = 0;
    //if max length has been reached
    if((terminalInfo.y +1) == videoInfo.videoHeight){
      terminalScroll();
    }else
    terminalInfo.y++;
    terminalInfo.row++;
  }

  terminalPutEntryAt(uc, colorTouint8(terminalInfo.color), terminalInfo.x, terminalInfo.y);
  terminalUpdateCursor();
}


void terminalWrite(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminalPutChar(data[i]);
}

void terminalWriteString(const char* data) {
	terminalWrite(data, strlen(data));
}

void terminalWriteLine(const char * data){
	terminalWriteString(data);
	terminalInfo.y++;
  terminalInfo.row++;
	terminalInfo.x =0;
}

void terminalChangeColor(_terminalColor color){
  terminalInfo.color = color;
}
void terminalChangeColorUint8(uint8_t color){
  terminalInfo.color = getColor(color);
}

void terminalNewLine(){
  terminalInfo.x= 0;
  if((terminalInfo.y+1)==videoInfo.videoHeight){
    terminalScroll();
  }else{
    terminalInfo.y++;
    terminalInfo.row++;
  }
  terminalUpdateCursor();
}

void terminalScroll(){
  for(unsigned int i = 0 ; i < videoInfo.videoHeight; i++){
    for(unsigned int j =0; j < videoInfo.videoWidth; j++){
      terminalInfo.buffer[i * videoInfo.videoWidth + j] =
      terminalInfo.buffer[(i+1) * videoInfo.videoWidth + j];
    }
  }
}


static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printk(const char *fmt, ...){
  va_list parameters;
  va_start(parameters,fmt);

int written = 0;
  while (*fmt != '\0') {
		size_t maxrem = INT_MAX - written;

		if (fmt[0] != '%' || fmt[1] == '%') {
			if (fmt[0] == '%')
				fmt++;
			size_t amount = 1;
			while (fmt[amount] && fmt[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(fmt, amount))
				return -1;
			fmt += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = fmt++;

    static char buffer[16];
    memset(&buffer,0,sizeof(buffer));
		if (*fmt == 'c') {
			fmt++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*fmt == 's') {
			fmt++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}else if (*fmt == 'd') {
			fmt++;
      int i = (int) va_arg(parameters,int );
			char *c = kitoa(i,&buffer);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}else if (*fmt == 'u') {
			fmt++;
      unsigned int i = (unsigned int) va_arg(parameters,unsigned int );
			char *c = kuitoa(i,&buffer);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}else if (*fmt == 'U') {
			fmt++;
      unsigned long long i = (unsigned long long) va_arg(parameters,unsigned long long );
			char *c = kulltoa(i,&buffer);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}else if (*fmt == 'l') {
			fmt++;
      long long i = (long long) va_arg(parameters,long long);
			char *c = klltoa(i,&buffer);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}else if (*fmt == 'x') {
			fmt++;
      unsigned int i = (unsigned int) va_arg(parameters,unsigned int );
			char *c = kuitoab(i,&buffer,16);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}else if (*fmt == 'X') {
			fmt++;
      unsigned long long i = (unsigned long long) va_arg(parameters,unsigned long long );
			char *c = kulltoab(i,&buffer,16);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(c, sizeof(c)))
				return -1;
			written++;
		}

    else {
			fmt = format_begun_at;
			size_t len = strlen(fmt);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(fmt, len))
				return -1;
			written += len;
			fmt += len;
		}
	}

	va_end(parameters);
	return written;
}


void sprintk( char * buffer,const char *fmt,...){
  char *output = buffer;


}
