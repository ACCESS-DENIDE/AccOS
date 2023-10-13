#pragma once

#include "DevicePortManager.h"
#include "InterrProc.h"
#include "print.h"
#include "asmCompp.h"

#define PIC1_PORT (0x20)

void keyb_init();

void keyb_handler();