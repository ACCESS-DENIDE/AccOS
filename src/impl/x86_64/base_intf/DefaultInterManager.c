#include "DefaultInterManager.h"

void RegisterDefaultIDT()
{
    IntrReg(0, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, DivErr); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(1, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_TRAP, DivErr); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(2, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, UnknownInter); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(3, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_TRAP, Breakpoint); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(4, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_TRAP, Overflow); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(5, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, BoundCheck); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(6, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, InvalidOpcode); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(7, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, CoprocessorAvailib); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(8, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, DoubleFault); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(9, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_TRAP, KeyboardInter); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(10, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, InvalidTSS); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(11, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, SegmentNotPresent); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(12, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, StackException); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(13, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, GeneralProtection); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(14, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, PageFault); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(15, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, Reserved); // segm_sel=0x8, P=1, DPL=0, Type=Intr
    IntrReg(16, GDT_CS, IDT_FLAG_RING_PRESENT | IDT_TYPE_INTR, CoprocessorError); // segm_sel=0x8, P=1, DPL=0, Type=Intr
}

INTERRUPT_HANDLER DivErr(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Division Error.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER Debugpoint(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Debug Breakpoint.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER UnknownInter(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Unknown Interrupt.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER Breakpoint(struct interrupt_frame* frame, int_64 instruction)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Breakpoint.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER Overflow(struct interrupt_frame* frame, int_64 instruction)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Overflow Error.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER BoundCheck(struct interrupt_frame* frame, int_64 instruction)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Bound Check error.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER InvalidOpcode(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Invalid Operation Code.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER CoprocessorAvailib(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Coprocessor not found.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER DoubleFault(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Double fault.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER KeyboardInter(struct interrupt_frame* frame)
{
     
    //PrintNewLine();
    //char mem=GetPrintColor();
    //SetPrintColor(COLOR_RED, COLOR_BLACK);
    //PrintString("Keyboard Input.");
    //PrintNewLine();
    //SwitchPrintColor(mem);
    if (ReadDataFromPort(0x64) & 0x01)
    {
        uint_8 scan_code;
        uint_8 state;
        scan_code = ReadDataFromPort(0x60); // Считывание символа с PS/2 клавиатуры
        OnKeyEvent(scan_code);
    }
    


    SetDataToPort(PIC1_PORT, 0x20);
     
}

INTERRUPT_HANDLER InvalidTSS(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Invalid TSS.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER SegmentNotPresent(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Segment Not ptesent.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER StackException(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Stack exc.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER GeneralProtection(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("General Protection Fault.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER PageFault(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("PageFault.");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER Reserved(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Reserved?");
    SwitchPrintColor(mem);
     
}

INTERRUPT_HANDLER CoprocessorError(struct interrupt_frame* frame)
{
     
    PrintNewLine();
    char mem=GetPrintColor();
    SetPrintColor(COLOR_RED, COLOR_BLACK);
    PrintString("Soprocessor failature");
    SwitchPrintColor(mem);
     
}
