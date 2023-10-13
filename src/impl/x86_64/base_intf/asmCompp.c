#include "asmCompp.h"

void popa(){

    asm("pop rax");
    asm("pop rbx");
    asm("pop rcx");
    asm("pop rdx");
    asm("pop rbp");
    asm("pop rsp");
    asm("pop rsi");
    asm("pop rdi");

    asm("pop r8");
    asm("pop r9");
    asm("pop r10");
    asm("pop r11");
    asm("pop r12");
    asm("pop r13");
    asm("pop r14");
    asm("pop r15");

}

void pusha(){

    asm("push rax");
    asm("push rbx");
    asm("push rcx");
    asm("push rdx");
    asm("push rbp");
    asm("push rsp");
    asm("push rsi");
    asm("push rdi");

    asm("push r8");
    asm("push r9");
    asm("push r10");
    asm("push r11");
    asm("push r12");
    asm("push r13");
    asm("push r14");
    asm("push r15");

}