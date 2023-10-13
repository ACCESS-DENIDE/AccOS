#include "KeyboardInput.h"

void keyb_init()
{
    GetDataFromPort(PIC1_PORT); 
    intr_reg_handler(0x09, GDT_CS, 0x80 | IDT_TYPE_INTR, keyb_handler);
    SetDataToPort(PIC1_PORT + 1, 0xFF ^ 0x02);
}

void keyb_handler()
{
    pusha();
    print_str("KeyboardInterrupt");
    print_newline();

    SetDataToPort(PIC1_PORT, 0x20);

    popa();
}