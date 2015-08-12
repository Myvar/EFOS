#ifndef __SYSTEM_H__
#define __SYSTEM_H__


#include <types.h>

#define ConsoleWidth 80
#define ConsoleHeight 25
#define ConsoleDefaultColor 0xF

enum Colors {
    ColorBlack          =   0x0,
    ColorBlue           =   0x1,
    ColorGreen          =   0x2,
    ColorCyan           =   0x3,
    ColorRed            =   0x4,
    ColorMagenta        =   0x5,
    ColorBrown          =   0x6,
    ColorLightGray      =   0x7,
    ColorDarkGray       =   0x8,
    ColorLightBlue      =   0x9,
    ColorLightGreen     =   0xA,
    ColorLightCyan      =   0xB,
    ColorLightRed       =   0xC,
    ColorLightMagenta         = 0xD,
    ColorYellow         =   0xE,
    ColorWhite          =   0xF
};

extern void Console_Clear();
extern void Console_Write_Char(char c);
extern void Console_Write_Char_Colored (char c, uint8 color);
extern void Console_Write_String (string s);
extern void Console_Write_String_Colored (string s, uint8 color);
extern void Console_Read_Line();

typedef int size_t;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern int compare_strings(char a[], char b[]);


/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int waitms);
extern void timer_install();

/* KEYBOARD.C */
extern void keyboard_install();

/* Paging */
extern void setup_paging();
extern void *maptable(unsigned long n);
#endif
