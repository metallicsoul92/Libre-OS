#ifndef LIBC_TERMIOS_H_
#define LIBC_TERMIOS_H_

#include "sys/cdefs.h"

/**
Posix-compliant Terminal IO System
*//


typedef uint8_t cc_t;
typedef uint32_t speed_t;
typedef uint32_t tcflag_t;

/* input flags */
#define	IGNBRK	(1 << 0)	/* Ignore break condition.  */
#define	BRKINT	(1 << 1)	/* Signal interrupt on break.  */
#define	IGNPAR	(1 << 2)	/* Ignore characters with parity errors.  */
#define	PARMRK	(1 << 3)	/* Mark parity and framing errors.  */
#define	INPCK	(1 << 4)	/* Enable input parity check.  */
#define	ISTRIP	(1 << 5)	/* Strip 8th bit off characters.  */
#define	INLCR	(1 << 6)	/* Map NL to CR on input.  */
#define	IGNCR	(1 << 7)	/* Ignore CR.  */
#define	ICRNL	(1 << 8)	/* Map CR to NL on input.  */
#define	IXON	(1 << 9)	/* Enable start/stop output control.  */
#define	IXOFF	(1 << 10)	/* Enable start/stop input control.  */

/* output flags */
#define OPOST (1 <<0 ) /*Perform Output Processing*/
#define ONCLR (1 <<1 ) /*Map NL to CR-NL OUTPUT*/
#define OCRNL (1 <<4 ) /*Map CR to NL on output*/
#define ONOCR (1 <<5 ) /*No CR output at column 0 */
#define ONLRET	(1 << 6)	/* Move to column 0 on NL.  */
#define NLDLY	(3 << 8)	/* NL delay.  */
#define NL0	(0 << 8)	/* NL type 0.  */
#define NL1	(1 << 8)	/* NL type 1.  */
#define TABDLY	(3 << 10)	/* TAB delay.  */
#define TAB0	(0 << 10)	/* TAB delay type 0.  */
#define TAB1	(1 << 10)	/* TAB delay type 1.  */
#define TAB2	(2 << 10)	/* TAB delay type 2.  */
#define TAB3	(1 << 2)	/* Expand tabs to spaces.  */
#define CRDLY	(3 << 12)	/* CR delay.  */
#define CR0	(0 << 12)	/* CR delay type 0.  */
#define CR1	(1 << 12)	/* CR delay type 1.  */
#define CR2	(2 << 12)	/* CR delay type 2.  */
#define CR3	(3 << 12)	/* CR delay type 3.  */
#define FFDLY	(1 << 14)	/* FF delay.  */
#define FF0	(0 << 14)	/* FF delay type 0.  */
#define FF1	(1 << 14)	/* FF delay type 1.  */
#define BSDLY	(1 << 15)	/* BS delay.  */
#define BS0	(0 << 15)	/* BS delay type 0.  */
#define BS1	(1 << 15)	/* BS delay type 1.  */
#define VTDLY	(1 << 16)	/* VT delay.  */
#define VT0	(0 << 16)	/* VT delay type 0.  */
#define VT1	(1 << 16)	/* VT delay type 1.  */
#define OLCUC	(1 << 17)	/* Translate lower case output to upper case */
#define OFILL	(1 << 18)	/* Send fill characters for delays */

/* Control flags */
#define CS5 0 /* 5 bits per byte */
#define CS6 (1 << 8) /* 6 bits per byte */
#define CS7 (1 << 9) /* 7 bits per byte */
#define CS8 (CS6|CS7 )/* 8 bits per byte */
#define CSIZE (CS5|CS6|CS7|CS8) /* Number of bits transmitted or recieved per byte */
#define CSTOPB (1 << 10) /* Two stop bits instead of one */
#define CREAD (1 << 11) /* Enable Reciever */
#define PARENB ( 1 << 12) /*Parity enabled */
#define PAROOD (1 << 13) /* Odd Parity, else even */
#define HUPCL (1 << 14) /*Hang up on last close */
#define CLOCAL (1<< 15) /* Ignore Modem Status Lines */

/* Local flags */
#define ECHO   (1 << 0) /* Enable Echo */
#define ECHOE  (1 << 1) /* Echo erase character as error correcting backspace */
#define ECHOK  (1 <<2) /* Echo KILL */
#define ECHONL (1 << 3) /* Echo NL */
#define ICANON (1 << 4) /* Cannonical Input (erase and kill processing) */
#define IEXTEN (1 << 5) /* Enable Extended input character processing */
#define ISIG   (1 << 6) /* Enable Signals */
#define NOFLSH (1 << 7) /* Disable flush after interrupt or quit */
#define TOSTOP (1 << 8) /* Send SIGTTOU for background output */

/* Control Characters */
#define VEOF 0 /* End of file character */
#define VEOL 1 /* End of line character */
#define VERASE 2 /* Erase Character */
#define VINTR 3 /* INTR Character */
#define VKILL 4 /* KILL Character */
#define VMIN 5 /*MIN Value */
#define VQUIT 6 /* QUIT Character */
#define VSTART 7 /*START Character */
#define VSTOP 8 /* STOP Character */
#define VSUS 9 /* SUSP Character */
#define VTIME 10 /* Time Value */

/* speed_t Baud values */
#define	B0	0		/* Hang up.  */
#define	B50	50		/* 50 baud.  */
#define	B75	75		/* 75 baud.  */
#define	B110	110		/* 110 baud.  */
#define	B134	134		/* 134.5 baud.  */
#define	B150	150		/* 150 baud.  */
#define	B200	200		/* 200 baud.  */
#define	B300	300		/* 300 baud.  */
#define	B600	600		/* 600 baud.  */
#define	B1200	1200		/* 1200 baud.  */
#define	B1800	1800		/* 1800 baud.  */
#define	B2400	2400		/* 2400 baud.  */
#define	B4800	4800		/* 4800 baud.  */
#define	B9600	9600		/* 9600 baud.  */
#define	B7200	7200		/* 7200 baud.  */
#define	B14400	14400		/* 14400 baud.  */
#define	B19200	19200		/* 19200 baud.  */
#define	B28800	28800		/* 28800 baud.  */
#define	B38400	38400		/* 38400 baud.  */

struct _termios{
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  #define NCCS 20 //Following GLIBC's implementation, which is taken from GNU HURD
  cc_t c_cc[NCCS];
  speed_t __ispeed;
  speed_t __ospeed;
};

typedef struct _termios termios_t;

#endif
