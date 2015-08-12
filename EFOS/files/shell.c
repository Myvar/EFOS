#include <system.h>
#include <shell.h>

char * Readline  = "";
int ReadLineIndex = 0;
int NumberOfCommands;
command_table_t CommandTable[MAX_COMMANDS];

void init_shell()
{
    add_new_command("help", "Tipe: help <command>, to get help!", help_command);
    
    add_new_command("", "", empty_command);
}

void help_command()
{
    
}

void empty_command()
{
    Console_Write_String("\n Help:\n");
}


void shell()
{
    
    Console_Write_String("\nEFOS>");
    Console_Read_Line();
   // Readline = 0;
    char * buf = Readline;
    buf = 0;
    
    Console_Write_String_Colored(buf,ColorYellow);
      int i = findCommand(Readline);
     
    if(i >= 0)
    {
        void (*command_function) ();
        command_function = CommandTable[i].function;
        command_function();
    }
    else
    {
        Console_Write_String_Colored("\nCommand Not Found",ColorRed);
        //Console_Write_String_Colored(i,ColorRed);
    }
    
    
    //  void (*command_run)(void);
}

void add_new_command(char *name, char *description, void *function)
{
    if(NumberOfCommands + 1 < MAX_COMMANDS)
    {
        NumberOfCommands++;
 
        CommandTable[NumberOfCommands].name = name;
        
        CommandTable[NumberOfCommands].description = description;
        CommandTable[NumberOfCommands].function = function;
        
    }
    return;
}



int findCommand(char* command)
{
     int i;
    int ret;
 
    for(i = 0; i <= NumberOfCommands - 1; i++)
    {
        char * buf = CommandTable[NumberOfCommands - 1].name;
        char * buf1 = command;        
        Console_Write_String(buf);
        Console_Write_String(buf1);
        buf  = 0;
        buf1 = 0;
        ret  = compare_strings(command, buf);
 
        if(ret == 0)
            return i;
        else
            return -1;
        }
}