#include <eduos/mmu.h>
#include <eduos/stddef.h>
#include <eduos/stdio.h>
#include <eduos/string.h>

/**
 * @brief
 * 4 MB page
 */
#define PD_NUM 1024
#define PT_NUM 1024

uint32_t kernel_page_directory[PD_NUM];
uint32_t kernel_page_table[PT_NUM];

long page_init(multiboot_info_t* mb_info) {
    memset(kernel_page_directory, 0, PD_NUM * 4);
    memset(kernel_page_table, 0, PT_NUM * 4);

    if (mb_info) {
        uint32_t map_index;
        multiboot_memory_map_t* mmap_entry_p;
        uint32_t map_slots =
                mb_info->mmap_length / sizeof(multiboot_memory_map_t);
        printk("slots = %d\n", map_slots);
        for (map_index = 0; map_index < map_slots; map_index++) {
            mmap_entry_p = reinterpret_cast<multiboot_memory_map_t*>(
                                   mb_info->mmap_addr) +
                           map_index;
            printk("mmap addr = %x | len = %x | type = %d\n",
                   (uint32_t)(mmap_entry_p->addr & 0xffffffff),
                   (uint32_t)(mmap_entry_p->len & 0xffffffff),
                   (uint32_t)mmap_entry_p->type);
        }
    }

    return 0;
}