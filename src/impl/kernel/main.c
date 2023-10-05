#include "print.h"
#include "InterrProc.h"

void kernel_main_c(){
    clear_print();
    intr_init();
    intr_start();
    intr_enable();

   
    set_color(COLOR_GREEN, COLOR_BLACK);
    print_str("HELLO WORLD");
    //int g= 12/0;
    
}