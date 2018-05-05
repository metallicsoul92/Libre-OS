#ifndef KBD_H
#define KBD_H

#include "../libc/include/sys/cdefs.h"
#include "../libc/include/string.h"
#include "tty.h"



unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char shift_keyboard_map[128]=
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\'', '~',   0,		/* Left shift */
 '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define STATE_NONE 0
#define STATE_SHIFT  1
#define STATE_CTRL 2
#define STATE_ALT 4
#define STATE_CAPS 8
#define STATE_SHIFT_CAPS 9

unsigned int g_kbdstate = STATE_NONE;
uint8_t capsOn = 0;

 void keyboard_handler_main(void) {
	unsigned char status;
  unsigned char keycode;
  unsigned char kmap[128];

	/* write EOI */
	outb(0x20, 0x20);

	status = inb(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = inb(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

// Check for CTRL ALT SHIFT state changes
#ifdef CONFIG_VERBOSE_KERNEL
#ifdef CONFIG_VERBOSE_KEYBOARD
 printk("Keycode 0x%x",keycode);
#endif //CONFIG_VERBOSE_KEYBOARD
#endif //CONFIG_VERBOSE_KERNEL

      if(keycode == 0x2A || keycode == 0x36){//left and right shift key press
        g_kbdstate += STATE_SHIFT;
        return;
      }
       if(keycode == 0xAA || keycode == 0xB6){// left and right shift key release
        g_kbdstate -= STATE_SHIFT;
        return;
      }

      if(keycode ==0x3A){// press of caps lock
        if(g_kbdstate == STATE_SHIFT){
          g_kbdstate = STATE_SHIFT_CAPS;
        }else if(g_kbdstate == STATE_CAPS){
          g_kbdstate = STATE_NONE;
        }else if(g_kbdstate == STATE_SHIFT_CAPS){
          g_kbdstate = STATE_SHIFT;
        }else if(g_kbdstate == STATE_NONE){
          g_kbdstate = STATE_CAPS;
        }
        return;
      }
      if(keycode ==0xBA){ //release of caps lock
        return;
      }

      if(capsOn==1){
        g_kbdstate += STATE_CAPS;
      }else if(capsOn == 0){

      }

      if(keycode & 0x80){
        return;
      }

      if(keycode == 0x48){
        terminalInfo.y--;
        terminalUpdateCursor();
        return;
      }
      if(keycode == 0x4B){
        if(terminalInfo.x == 0){
          terminalInfo.x = videoInfo.videoWidth;
          terminalInfo.y--;
        }else{
          terminalInfo.x--;
        }
        terminalUpdateCursor();
        return;
      }
      if(keycode == 0x4D){
        if(terminalInfo.x == videoInfo.videoWidth){
          terminalInfo.x = 0;
          terminalInfo.y++;
        }else{
          terminalInfo.x++;
        }
        terminalUpdateCursor();
        return;
      }
      if(keycode == 0x50){
        if(terminalInfo.y == videoInfo.videoHeight){
          terminalScroll();
        }else{
          terminalInfo.y++;
        }
        terminalUpdateCursor();
        return;
      }
//Here we will determine which map to use
    switch(g_kbdstate){
      case STATE_NONE:
      memcpy(kmap,&keyboard_map,sizeof(keyboard_map));
      break;
      case STATE_SHIFT:
      memcpy(kmap,&shift_keyboard_map,sizeof(shift_keyboard_map));
      break;
      case STATE_CAPS:
      memcpy(kmap,&shift_keyboard_map,sizeof(shift_keyboard_map));
      break;
      case STATE_SHIFT_CAPS:
      memcpy(kmap,&keyboard_map,sizeof(keyboard_map));
      break;
      default:
      printk("Invalid Keyboard State.");
      memcpy(kmap,&keyboard_map,sizeof(keyboard_map));
      break;
    }

      if(kmap[keycode]  =='\n'){
        _terminalInfo t = getTerminalInfo();
        _videoInfo v = getVideoInfo();

        if((t.y+1) == v.videoHeight){
          terminalScroll();
        }else{
      terminalWriteLine("");
    }
      terminalUpdateCursor();
}
      /*write_line deals with column and row  */
      else if(kmap[keycode]  =='\t')
      {
        printk("     ");
      terminalInfo.x +=5;
      terminalUpdateCursor();
    }
      else if(kmap[keycode] =='\b')
      {
        terminalPutEntryAt(' ',colorTouint8(terminalInfo.color),terminalInfo.x--,terminalInfo.y);
      terminalUpdateCursor();
    }else
      printk("%c",kmap[keycode]);

    //  terminal_putentryat(keyboard_map[keycode],terminal_color,terminal_column++,terminal_row);
//    terminal_buffer[currentPos++] = keyboard_map[keycode];
//		terminal_buffer[currentPos++] = 0x07;
	}
}

#endif //ARCH_I386_KBD_H_
