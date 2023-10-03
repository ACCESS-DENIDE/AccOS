section .multiboot_header
header_start:
    ; flag_numb
    dd 0xe85250d6

    dd 0

    dd header_start-header_end

    dd 0x100000000-(0xe85250d6+0+(header_start-header_end))

    dw 0
    dw 0
    dd 8
header_end: