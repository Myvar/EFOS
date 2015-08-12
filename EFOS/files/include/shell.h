#ifndef __SHELL_H__
#define __SHELL_H__


#define MAX_COMMANDS 100
extern char * Readline;
extern int ReadLineIndex;
extern int inreadline;
extern void help_command();
extern void empty_command();

typedef struct
{
    char *name;
    char *description;
    void *function;
} command_table_t;

#endif