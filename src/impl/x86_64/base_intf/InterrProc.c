#include "InterrProc.h"


struct idt_entry_t g_idt[256]; // Реальная таблица IDT
struct idtr_t g_idtp; // Описатель таблицы для команды lidt


INTERRUPT_HANDLER DefaultIntrHandlr(struct interrupt_frame* frame) {
    

    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Called Exsception handler... processor holded.");
    SwitchPrintColor(mem);
    HaltCPU();

}

void IntrReg(int num, uint_16 segm_sel, uint_16 flags, intr_handler hndlr)
{
    uint_64 HndlrAdr=(uint_64)hndlr;

    g_idt[num].base_low=(uint_64)(HndlrAdr & 0xFFFF);
    g_idt[num].kernel_cs=0x08;
    g_idt[num].ist=0;
    g_idt[num].attributes=flags;
    g_idt[num].base_mid=(uint_64)((HndlrAdr >> 16) & 0xFFFF);
    g_idt[num].base_high= (uint_64)((HndlrAdr >> 32) & 0xFFFFFFFF);

}

void IntrFill()
{
    int i;
    int idt_count = sizeof(g_idt) / sizeof(g_idt[0]);
    for(i = 0; i < idt_count; i++){
        IntrReg(i, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, DefaultIntrHandlr); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    }
    
    
   
}

void SetIDT()
{
    int idt_count = sizeof(g_idt) / sizeof(g_idt[0]);
    g_idtp.base = (unsigned int) (&g_idt[0]);
    g_idtp.limit = (sizeof (struct idt_entry_t) * idt_count) - 1;


    asm volatile ("lidt %0" : : "m"(g_idtp)); // load the new IDT

}

void IntrEnable()
{
    PrintString("Interrupts enabled");
    PrintNewLine();
     asm volatile ("sti"); // set the interrupt flag
}

void IntrDisable()
{
    PrintString("Interrupts disabled");
    PrintNewLine();
    asm volatile ("cli"); // set the interrupt flag
}
