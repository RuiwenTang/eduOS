[BITS 32]
global loader                                       ; the entry symbol for ELF
MAGIC_NUMBER                    equ 0x1BADB002      ; define the magic number constant
MULTIBOOT_PAGE_ALIGN            equ 1<<0            ; page align
MULTIBOOT_MEMORY_INFO           equ 1<<1            ; need memory info
                                                    ; (magic number + checksum + flags should equal 0)
FLAGS                           equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO             ; multiboot flags
CHECKSUM                        equ -(MAGIC_NUMBER + FLAGS)   ; calculate the checksum
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

section .multiboot                 ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

section .text
extern sum_of_three
extern kmain
loader:                         ; the loader label (defined as entry point in linker script)
    cli                         ; Disable interrupts
    push ebx
    call kmain
    add esp, 4
.loop:
    jmp .loop                   ; loop forever

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
