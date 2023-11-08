#include "print.h"
#include "DefaultInterManager.h"
#include "MemoryManager.h"
#include "asmCompp.h"
#include "MiniMath.h"
#include "TextProcessors.h"

void kernel_main_c(){
    ClearPrint();
    IntrFill();
    RegisterDefaultIDT();
    KeyboardInit();
    SetIDT();
    IntrEnable();
    InitAll();

   
    SetPrintColor(COLOR_GREEN, COLOR_BLACK);
    PrintString("HELLO USER");
    PrintNewLine();

    char * command;
    char * buff;

    do
    {
        command=ReadLine();


        

        SplitIterration(command, buff, ' ', 0);

        AlignText(buff);
        

        if (CompareStrings(buff, "info")) {
                PrintString("Made by Rock");
                PrintNewLine();
        }
        else if (CompareStrings(buff, "expr")) {
	        int err = 0;
            

	        SplitIterration(command, buff, ' ', 1);
            int cou=0;

            do
            {
                cou++;
            } while (buff[cou]!='\0');
            

            for (int i = cou-1; i >-1; i--)
            {
                buff[i+1]=buff[i];
            }
            buff[0]='(';
            buff[cou+1]=')';
            buff[cou+2]='\0';
	        err= ProcessString(buff);
	        if (err < 0) {
                switch (err)
                {
                case(-1):
                     PrintString("Err. Zero division");
                    PrintNewLine();
                    break;
                case(-2):
                    PrintString("Err. Int overflow");
                     PrintNewLine();
                    break;
                default:
                    break;
                }
		
	        }
	        else {
		         PrintString(buff);
                PrintNewLine();
            }
        }
        else if (CompareStrings(buff, "shutdown")) {
            break;
        }
        else if (CompareStrings(buff, "sysyphus")) {
            
        }
        else {
             PrintString("Command not found? go wash your balls");
                PrintNewLine();
        }

    } while (1);
    
 
    SetPrintColor(COLOR_LIGHT_GRAY, COLOR_BLACK);
    
    
}