#pragma once



void* memall(int block_am);
void* memreal(int block_am, void* ptr, bool keep);
void  free(void* prt);