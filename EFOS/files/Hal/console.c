#include <system.h>

UPoint ConsoleCursor = {0, 0};
UPoint ConsoleSize = {ConsoleWidth, ConsoleHeight};

uint8* VideoRam = (uint8*)0xb8000;

void Console_Clear()
{
    uint32 i;
    for (i = 0; i < ConsoleSize.X * ConsoleSize.Y * 2; i++)
        VideoRam[i] = 0;
}

void Console_Write_Char(char c)
{
    Console_Write_Char_Colored(c, ConsoleDefaultColor);
}

void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = ConsoleCursor.Y * 80 + ConsoleCursor.X;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void Console_Write_Char_Colored (char c, uint8 color)
{

    if(c == '\n')
    {
        ConsoleCursor.X = 0;
        ConsoleCursor.Y ++;
    }
    else
    {
        uint32 location = ConsoleCursor.X + ConsoleCursor.Y * ConsoleSize.X;
    
        VideoRam[2*location] = c;
        VideoRam[2*location + 1] = color;
            
          ConsoleCursor.X++;
    
        if (ConsoleCursor.X >= ConsoleSize.X) {
            ConsoleCursor.X = 0;
            ConsoleCursor.Y ++;
        }
    }
    move_csr();
}

void Console_Write_String (string s)
{
    Console_Write_String_Colored (s, ConsoleDefaultColor);
}

void Console_Write_String_Colored (string s, uint8 color)
{
    while (*s != 0)
    {
        Console_Write_Char_Colored (*s, color);
        s = s + 1;
    }
}
