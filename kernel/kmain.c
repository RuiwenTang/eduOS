#include <eduos/config.h>
#include <eduos/fs.h>
#include <eduos/memory.h>
#include <eduos/processor.h>
#include <eduos/stddef.h>
#include <eduos/stdio.h>
#include <eduos/string.h>
#include <eduos/tasks.h>
#include <eduos/time.h>

#include <v86/v86.h>

#include <multiboot/multiboot.h>

#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/vga.h>

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

multiboot_info_t* mb_info = NULL;
extern const void kernel_start;
extern const void kernel_end;
extern atomic_int32_t total_pages;
extern atomic_int32_t total_allocated_pages;
extern atomic_int32_t total_available_pages;

extern void* _int32;
extern void* int32_end;

int detect_v86();

static void eduos_kernel_init() {
    gdt_install();
    vga_init();
    cpu_detection();
    idt_install();
    irq_init();

    timer_init();
    multitasking_init();
    memory_init();

    fs_init();
}

static int foo(void* arg) {
    int i;

    for (i = 0; i < 2; i++) {
        kprintf("hello from %s\n", (char*)arg);
    }
    return 0;
}

void kmain(multiboot_info_t* boot_info) {
    if (boot_info == NULL) {
        abort();
    } else {
        mb_info = boot_info;
        eduos_kernel_init();
        system_calibration();  // enables also interrupts
    }

    kprintf("Kernel starts at %p and ends at %p\n", &kernel_start, &kernel_end);
    kprintf("Processor frequency: %u MHz\n", get_cpu_frequency());
    kprintf("Current allocated memory: %lu KiB\n",
            atomic_int32_read(&total_allocated_pages) * PAGE_SIZE / 1024);
    kprintf("Current available memory: %lu KiB\n",
            atomic_int32_read(&total_available_pages) * PAGE_SIZE / 1024);

    list_fs(fs_root, 1);

    create_kernel_task(NULL, foo, "foo", NORMAL_PRIO);
}