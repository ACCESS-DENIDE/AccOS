section .multiboot_header ;boot_sector_flag
header_start:
    ; bootloader_start_flag
    dd 0xe85250d6

    ;secure_mode_flag
    dd 0

    ;size_flag
    dd header_start-header_end

    ;check_summ
    dd 0x100000000-(0xe85250d6+0+(header_start-header_end))

    ;end_flag
    dw 0
    dw 0
    dd 8
header_end: