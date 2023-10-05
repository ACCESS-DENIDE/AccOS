#include "InterrProc.h"



struct idt_entry_t g_idt[256]; // Реальная таблица IDT
struct idtr_t g_idtp; // Описатель таблицы для команды lidt


void exception_handler() {
    print_newline();
    char mem=get_color();
    set_color(COLOR_RED, COLOR_BLACK);
    print_str("Called Exsception handler... processor holded.");
    switch_color(mem);
    __asm__ volatile ("cli");
    __asm__ volatile ("hlt"); // Completely hangs the computer
}

void intr_reg_handler(int num, uint_16 segm_sel, uint_16 flags, intr_handler hndlr)
{
    g_idt[num].base_low=(uint_64)hndlr & 0xFFFF;
    g_idt[num].kernel_cs=0x08;
    g_idt[num].ist=0;
    g_idt[num].attributes=flags;
    g_idt[num].base_mid=((uint_64)hndlr >> 16) & 0xFFFF;
    g_idt[num].base_high= ((uint_64)hndlr >> 32) & 0xFFFFFFFF;

}

void intr_init()
{
    int i;
    int idt_count = sizeof(g_idt) / sizeof(g_idt[0]);
    for(i = 0; i < idt_count; i++){
        intr_reg_handler(i, GDT_CS, 0x80 | IDT_TYPE_INTR, exception_handler); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    }
    
    
   
}

void intr_start()
{
    int idt_count = sizeof(g_idt) / sizeof(g_idt[0]);
    g_idtp.base = (unsigned int) (&g_idt[0]);
    g_idtp.limit = (sizeof (struct idt_entry_t) * idt_count) - 1;

    g_idtp.base = (unsigned int *)&g_idt[0];
    g_idtp.limit = (uint_16)sizeof (struct idt_entry_t) * 256 - 1;
    print_int(g_idtp.base);
    print_newline();
    print_int(g_idtp.limit);

    asm volatile ("lidt %0" : : "m"(g_idt)); // load the new IDT

}

void intr_enable()
{
    print_str("Interrupts enabled");
     asm volatile ("sti"); // set the interrupt flag
}

void intr_disable()
{
    print_str("Interrupts disabled");
    asm volatile ("cli"); // set the interrupt flag
}
