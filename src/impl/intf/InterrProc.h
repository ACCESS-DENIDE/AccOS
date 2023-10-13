#pragma once
#include "CustomDataTypes.h"
#include "print.h"

#define IDT_TYPE_INTR (0xE)
#define IDT_TYPE_TRAP (0xF)
//#define IDT_TYPE_TASK (0x5)

#define IDT_FLAG_RING_0 (0<<5)
#define IDT_FLAG_RING_1 (1<<5)
#define IDT_FLAG_RING_2 (2<<5)
#define IDT_FLAG_RING_3 (3<<5)
#define IDT_FLAG_RING_PRESENT (0x80)

#define GDT_CS (0x8)

struct idt_entry_t {
	uint_16     base_low;      // The lower 16 bits of the ISR's address
	uint_16     kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint_8	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint_8      attributes;   // Type and attributes; see the IDT page
	uint_16     base_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint_32     base_high;     // The higher 32 bits of the ISR's address
	uint_32     reserved;     // Set to zero
} __attribute__((packed)) ;


 struct idtr_t {
	uint_16	    limit;
	uint_64	    base;
} __attribute__((packed)) ;


typedef void (*intr_handler)();

__attribute__((noreturn))
void exception_handler();
void intr_reg_handler(int num, uint_16 segm_sel, uint_16 flags, intr_handler hndlr);
void intr_init();
void intr_start();
void intr_enable();
void intr_disable();