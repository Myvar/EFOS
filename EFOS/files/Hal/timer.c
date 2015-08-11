 /* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Timer driver
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
volatile unsigned int timer_ticks = 0;
volatile unsigned int miliseconds = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
    miliseconds = (timer_ticks / 18.222) * 1000;
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int waitms)
{
    unsigned long ems;

    ems = miliseconds + waitms;
    while(miliseconds < ems)
    {
        __asm__ __volatile__ ("sti");
        __asm__ __volatile__ ("hlt");
        __asm__ __volatile__ ("cli");
    }
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
