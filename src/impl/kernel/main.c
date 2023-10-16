#include "print.h"
#include "DefaultInterManager.h"

void kernel_main_c(){
    ClearPrint();
    IntrFill();
    RegisterDefaultIDT();
    KeyboardInit();
    SetIDT();
    IntrEnable();

   
    SetPrintColor(COLOR_GREEN, COLOR_BLACK);
    PrintString("HELLO WORLD");
    PrintNewLine();
 
    SetPrintColor(COLOR_LIGHT_GRAY, COLOR_BLACK);
   //int g= 12/0;
   int_64 cou=0;

   PrintString(ReadLine());
   PrintString(ReadLine());
    do
    {   
        char swtch=GetKey();
        if(swtch=='g'){
            SetPrintColor(COLOR_LIGHT_GREEN, COLOR_BLACK);
        }
        else{
            SetPrintColor(COLOR_LIGHT_GRAY, COLOR_BLACK);
        }
        cou++;
        PrintInt(cou);
        PrintNewLine();
    } while (1);
    
    
    
}