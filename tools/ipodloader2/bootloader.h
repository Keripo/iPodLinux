#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef   signed int    int32;
typedef   signed short  int16;
typedef   signed char   int8;

#define inl(a) (*(volatile unsigned long *) (a))
#define outl(a,b) (*(volatile unsigned long *) (b) = (a))
#define inb(a) (*(volatile unsigned char *) (a))
#define outb(a,b) (*(volatile unsigned char *) (b) = (a))

#endif