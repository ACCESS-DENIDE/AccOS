;start_is_global
global start 
extern long_mode_start

;boot_sector_flag
section .text 
;processor_word_length
bits 32
start:
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    call setup_paging
    call enable_paiging_longmode

    cli

    lgdt [GDT64.Pointer]
    jmp GDT64.Code:long_mode_start

    ;print_OK_32_bit
    mov dword [0xb8000], 0x2f4b2f4f
    hlt

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret
.no_multiboot:
    mov al, "M"
    jmp error_print

check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1<<21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "C"
    jmp error_print

check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1<<29
    jz .no_long_mode

    ret

.no_long_mode
    mov al, "L"
    jmp error_print



error_print:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt


setup_paging:
    mov eax, page_tab_l3
    or eax, 0b11
    mov [page_tab_l4], eax

    mov eax, page_tab_l2
    or eax, 0b11
    mov [page_tab_l3], eax

    mov ecx, 0

.loop:

    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [page_tab_l2+ecx*8], eax

    inc ecx
    cmp ecx, 512
    jne .loop

    ret

enable_paiging_longmode:
    mov ebx, cr0
    or ebx, ~(1<<31)
    mov cr0, ebx

    mov edx, cr4
    or edx, (1<<5)
    mov cr4, edx

    mov ecx, 0xC0000080
    rdmsr
    or eax, (1<<8)
    wrmsr

    mov eax, page_tab_l4
    mov cr3, eax

    or ebx, (1 << 31) | (1 << 0)
    mov cr0, ebx

    ret
    

section .bss

align 4096
page_tab_l4:
    resb 4096
page_tab_l3:
    resb 4096
page_tab_l2:
    resb 4096


stack_bottom:
    resb 4096*4
stack_top:

section .rodata
; Access bits
PRESENT        equ 1 << 7
NOT_SYS        equ 1 << 4
EXEC           equ 1 << 3
DC             equ 1 << 2
RW             equ 1 << 1
ACCESSED       equ 1 << 0
 
; Flags bits
GRAN_4K       equ 1 << 7
SZ_32         equ 1 << 6
LONG_MODE     equ 1 << 5
 
GDT64:
    .Null: equ $ - GDT64
        dq 0
    .Code: equ $ - GDT64
        dd 0xFFFF                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | EXEC | RW            ; Access
        db GRAN_4K | LONG_MODE | 0xF                ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .Data: equ $ - GDT64
        dd 0xFFFF                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | RW                   ; Access
        db GRAN_4K | SZ_32 | 0xF                    ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .TSS: equ $ - GDT64
        dd 0x00000068
        dd 0x00CF8900
    .Pointer:
        dw $ - GDT64 - 1
        dq GDT64