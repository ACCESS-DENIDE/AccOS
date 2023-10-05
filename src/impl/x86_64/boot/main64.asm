global long_mode_start
extern kernel_main_c

section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov dword [0xb8000], 0x2f4b2f4f
    call kernel_main_c

    hlt