#pragma once

#include "CustomDataTypes.h"
#define IDT_MAX_DESCRIPTORS 256
#define GDT_OFFSET_KERNEL_CODE (0x01 * 0x08) //!!!! just to test

extern uint_64 isr_stub_table[];


typedef struct {
    uint_16 isr_low;   // The lower 16 bits of the ISR's address
    uint_16 kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint_8 ist; // The IST in the TSS that the CPU will load into RSP; set to zero for now
    uint_8 attributes; // Type and attributes; see the IDT page
    uint_16 isr_mid;   // The higher 16 bits of the lower 32 bits of the ISR's address
    uint_32 isr_high;  // The higher 32 bits of the ISR's address
    uint_32 reserved;  // Set to zero
} __attribute__((packed)) idt_desc_t;



typedef struct {
    uint_16 limit;
    uint_64 base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;
void idt_reload(idtr_t* idtr);
void idt_set_descriptor(uint_8 vector, uint isr, uint_8 flags, uint_8 ist);



void idt_init(void);



static int vectors[IDT_MAX_DESCRIPTORS];