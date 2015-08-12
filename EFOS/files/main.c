#include <system.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


int compare_strings(char *first, char *second)
{

   while(*first==*second)
   {
      if ( *first == '\0' || *second == '\0' )
      {
          break;
      }
      first  = first + 1;
      second = second + 1;
   }
   if( *first == '\0' && *second == '\0' )
   {
       Console_Write_Char('t');
       return 0;
   }
   else
   {
              Console_Write_Char('f');
      return -1;
  }
}

void kmain (void* MultibootStructure)
{
    Console_Clear();
    Print_Info("Starting EFOS...");
    
    gdt_install();
    Print_Info("GDT Installed Successfully");
    idt_install();
    Print_Info("IDT Installed Successfully");
    isrs_install();
    Print_Info("ISRS Installed Successfully");
    irq_install();
    Print_Info("IRQ Installed Successfully");
    setup_paging();
    Print_Info("Paging Installed Successfully");
     timer_install();
    Print_Info("Timer Installed Successfully");
    keyboard_install();
    Print_Info("Keyboard Installed Successfully");

    __asm__ __volatile__ ("sti");
    
    Print_Info("System is ready now.");
    
    init_shell();
   
    shell();
    
}

void Print_Info(string txt)
{
    Console_Write_String("[");
    Console_Write_String_Colored("Info", ColorGreen);
    Console_Write_String("]");
    Console_Write_String(txt);
    Console_Write_String("\n");
}

void Print_Error(string txt)
{
    Console_Write_String("[");
    Console_Write_String_Colored("Error", ColorRed);
    Console_Write_String("]");
    Console_Write_String(txt);
    Console_Write_String("\n");
}
