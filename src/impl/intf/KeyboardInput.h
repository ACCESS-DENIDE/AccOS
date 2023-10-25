#pragma once

#include "DevicePortManager.h"
#include "print.h"
#include "MemoryManager.h"

#define PIC1_PORT (0x20)


void KeyboardInit();

void OnKeyEvent(uint_8 event_code);



char GetKey();
char ReadKey();
char* ReadLine();

uint_8 InterpritateCode(uint_8 code, char* symb);