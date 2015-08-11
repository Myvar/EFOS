#include <system.h>
#include <hal.h>

void kmain (void* MultibootStructure)
{
    Console_Clear();
    Print_Info("EFOS will now start booting");
    Gdt_Install();
    Print_Info("GDT Installed Successfully");
    Idt_Install();
    Print_Info("IDT Installed Successfully");
    Isrs_Install();
    Print_Info("Isrs Installed Successfully");
    Irq_Install();
    Print_Info("Irq Installed Successfully");
    Setup_Paging();
    Print_Info("Paging Installed Successfully");
    Keyboard_Install();
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
