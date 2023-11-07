#pragma once
#include "CustomDataTypes.h"

void AlignText(char* text);
int TextToInt(const char* text, int *outp,  int from);
int Split(const char* text, char* outp,  char spliter, int from);
void SplitIterration(const char* text, char* outp, char spliter, int iter);
int CompareStrings(const char* a, const char* b);
int IntToStr(int inp, char* str);
int Find(const char* str, char ch, int from);
void MinusCollapse(char* str);