#include "print.h"
#include "InterrProc.h"
#include "KeyboardInput.h"

void kernel_main_c(){
    clear_print();
    intr_init();
    keyb_init();
    intr_start();
    intr_enable();

   
    set_color(COLOR_GREEN, COLOR_BLACK);
    print_str("HELLO WORLD");
    print_newline();
    do
    {
        /* code */
    } while (1);
    
    //int g= 12/0;
    
}