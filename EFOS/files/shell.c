#include <system.h>
#include <shell.h>

char * Readline;
int ReadLineIndex = 0;
int NumberOfCommands = 0;
int inreadline = 0; 

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
    
}

char *strcpyc(char *s1, char s2)
{
    char *s1_p = s1;
    *s1++ = s2;
    return s1_p;
}

void shell()
{
    Console_Write_String("\nEFOS>");
    Console_Read_Line();
    
    while(inreadline == 1)
    {
        int x = 0;
        x++;
        if(x == 10)
        {
         x = 0;   
        }
     if(inreadline == 0 )
     {
         break;
     }
    }
    Console_Write_String_Colored("done",ColorYellow);
     int i = findCommand(Readline);
     
    if(i >= 0)
    {
        void (*command_function) ();
        command_function = CommandTable[i].function;
        command_function();
    }
    else
    {
        return;
    }
     
    return;
    void (*command_run)(void);
}

void add_new_command(char *name, char* description, void *function)
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
 
    for(i = 0; i < NumberOfCommands + 1; i++)
    {
        ret = compare_strings(command, CommandTable[i].name);
 
        if(ret == 0)
            return i;
        else
            return -1;
    }
}