#include "print.h"
#include "DefaultInterManager.h"
#include "MemoryManager.h"
#include "asmCompp.h"

void kernel_main_c(){
    ClearPrint();
    IntrFill();
    RegisterDefaultIDT();
    KeyboardInit();
    SetIDT();
    IntrEnable();
    InitAll();

   
    SetPrintColor(COLOR_GREEN, COLOR_BLACK);
    PrintString("HELLO WORLD");
    PrintNewLine();
 
    SetPrintColor(COLOR_LIGHT_GRAY, COLOR_BLACK);
   
   int_64 cou=0;
   char* str=NULL;

    str = (char*)MemAll(2);

    /*do
    {
        str[cou]=ReadKey();
        cou++;
        str[cou]='\0';
        str=(char*)MemReal(str, cou+2, 1);
        PrintString(str);
        PrintNewLine();
    } while (1);*/
    
    do
    {
        PrintString(ReadLine());
    } while (1);
    
    
    

    
   /* do
    {   
        char swtch='0';
        swtch=GetKey();
        if(swtch=='g'){
            SetPrintColor(COLOR_LIGHT_GREEN, COLOR_BLACK);
        }
        else{
            SetPrintColor(COLOR_LIGHT_GRAY, COLOR_BLACK);
        }
        cou++;
        PrintInt(cou);
        PrintNewLine();
    } while (1);*/
    
    
    
}