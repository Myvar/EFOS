#include <system.h>

unsigned long *page_directory = (unsigned long *) 0x9C000;
unsigned long *page_table = (unsigned long *) 0x9D000; // the page table comes right after the page directory

void setup_paging()
{
unsigned long address=0; // holds the physical address of where a page is
unsigned int i;

extern write_cr3(unsigned long *);
extern write_cr0(unsigned long *);
// map the first 4MB of memory
for(i=0; i<1024; i++)
{
page_table[i] = address | 3; 
address = address + 4096; // 4096 = 4kb
};

page_directory[0] = page_table; 
page_directory[0] = page_directory[0] | 3;

// write_cr3, read_cr3, write_cr0, and read_cr0 all come from the assembly functions
write_cr3(page_directory); // put that page directory address into CR3
write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1



}

void *maptable(unsigned long n)
{
    return page_table[n];
}

//void *malloc(unsigned long n)
//{
//    return page_table[n]; // this is fake
//} */