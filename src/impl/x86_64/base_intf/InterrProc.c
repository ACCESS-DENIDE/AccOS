#include "InterrProc.h"
#include "CustomDataTypes.h"
#include "print.h"
idt_desc_t idt[IDT_MAX_DESCRIPTORS]; // Create an array of IDT entries; aligned for performance

void idt_set_descriptor(uint_8 vector, uint isr, uint_8 flags, uint_8 ist) {
    idt_desc_t* descriptor = &idt[vector];

    descriptor->isr_low = isr & 0xFFFF;
    descriptor->kernel_cs = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist = ist;
    descriptor->attributes = flags;
    descriptor->isr_mid = (isr >> 16) & 0xFFFF;
    descriptor->isr_high = (isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved = 0;
}
void idt_init() {
    idtr.base = (uintp)&idt[0];
    idtr.limit = (uint_16)sizeof(idt_desc_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint_8 vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E, 1); 
        vectors[vector] = 1;
    }
    __asm__ volatile("lidt %0" : : "memory"(idtr)); // load the new IDT
    __asm__ volatile("sti");                        // set the interrupt flag

}
void exception_handler() {
    print_str("Interrupted");
     __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}
