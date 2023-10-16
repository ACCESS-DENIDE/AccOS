#pragma once
#include "CustomDataTypes.h"
#include "InterrProc.h"
#include "DevicePortManager.h"
#include "KeyboardInput.h"

#define PIC1_PORT (0x20)


void RegisterDefaultIDT();

INTERRUPT_HANDLER DivErr(struct interrupt_frame* frame);
INTERRUPT_HANDLER Debugpoint(struct interrupt_frame* frame);
INTERRUPT_HANDLER UnknownInter(struct interrupt_frame* frame);
INTERRUPT_HANDLER Breakpoint(struct interrupt_frame* frame, int_64 instruction);
INTERRUPT_HANDLER Overflow(struct interrupt_frame* frame, int_64 instruction);
INTERRUPT_HANDLER BoundCheck(struct interrupt_frame* frame, int_64 instruction);
INTERRUPT_HANDLER InvalidOpcode(struct interrupt_frame* frame);
INTERRUPT_HANDLER CoprocessorAvailib(struct interrupt_frame* frame);
INTERRUPT_HANDLER DoubleFault(struct interrupt_frame* frame);
INTERRUPT_HANDLER KeyboardInter(struct interrupt_frame* frame);
INTERRUPT_HANDLER InvalidTSS(struct interrupt_frame* frame);
INTERRUPT_HANDLER SegmentNotPresent(struct interrupt_frame* frame);
INTERRUPT_HANDLER StackException(struct interrupt_frame* frame);
INTERRUPT_HANDLER GeneralProtection(struct interrupt_frame* frame);
INTERRUPT_HANDLER PageFault(struct interrupt_frame* frame);
INTERRUPT_HANDLER Reserved(struct interrupt_frame* frame);
INTERRUPT_HANDLER CoprocessorError(struct interrupt_frame* frame);