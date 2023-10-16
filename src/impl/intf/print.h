#pragma once

enum ConsoleColor{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARK_GRAY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_PINK = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15,

};

void ClearPrint();
void SetPrintColor(char foreground, char background);
char GetPrintColor();
void SwitchPrintColor(char newcol);
void PrintChar(char ch);
void PrintString(char* string);
void PrintInt(int inp);
void ClearRow(int row_clear);
void PrintNewLine();