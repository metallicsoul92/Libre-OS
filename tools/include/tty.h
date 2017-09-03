#ifndef TTY_H_
#define TTY_H_

#include "vga.h"

extern _videoInfo videoInfo;

struct __terminalColor{
  uint8_t foreground:4; //top4
  uint8_t background:4; //bottom4
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

int printk(const char *fmt, ...);

//for the kitoa family:
void reverse(char s[]);

//kitoa family:
char * kitoa(int n, char s[]);
char * kitoab(int n, char s[],unsigned int base);
char * kuitoa(int n, char s[]);
char * kuitoab(int n, char s[],unsigned int base);


#endif //TTY.h
