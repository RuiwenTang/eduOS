#include <eduos/config.h>
#include <eduos/stddef.h>

#include <multiboot/multiboot.h>

#include <asm/io.h>

int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

void kmain(multiboot_info_t* boot_info) {
    if (boot_info == NULL) {

    }
}