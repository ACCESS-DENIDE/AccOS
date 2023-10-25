#pragma once
#include "CustomDataTypes.h"

#define HEAP_SIZE_KB 4
#define MAX_ALL_BLOCKS 256


void* MemAll(int size);
void* MemReal(void* ptr, int new_size, bool keep);
void  Free(void* ptr);
void  InitAll();
int   BlocSize(void* ptr);