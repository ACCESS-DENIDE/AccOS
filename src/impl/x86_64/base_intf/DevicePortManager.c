#include "DevicePortManager.h"

uint_8 ReadDataFromPort (uint_16 port) // Чтение из порта
{
    uint_8 data;
    asm volatile ("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}


void SetDataToPort (uint_16 port, uint_8 data) // Запись
{
    asm volatile ("outb %b0, %w1" : : "a" (data), "Nd" (port));
}