#ifndef __EDUOS_MMU_H__
#define __EDUOS_MMU_H__

#include <multiboot/multiboot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PAGE_4K_SIZE 4096
#define PAGE_4M_SIZE 4 << 20

// ======================== Page Directory Flags

/**
 * @brief set to enable 4MB page feature
 *
 */
#define PD_SIZE_BITE (1 << 7)
/**
 * @brief CPU set this bit if this entry is read or write
 *
 */
#define PD_ACCESSED_BITE (1 << 5)
/**
 * @brief set this bit will diable page cache
 *
 */
#define PD_CACHE_DISABLE_BITE (1 << 4)
/**
 * @brief set 1 to enable write through cache,
 * set 0 to enable write back cache
 *
 */
#define PD_WRITE_THROUGH_OR_BACK_BITE (1 << 3)
/**
 * @brief set 1 to enable user application access
 *
 */
#define PD_USER_ACCESS_BITE (1 << 2)
/**
 * @brief set 1 to enable write
 *
 */
#define PD_WRITEABLE_BITE (1 << 1)

#define PD_PRESENT_BITE (1 << 0)

// ======================== Page Table Flags

/**
 * @brief
 * Page global bit, set to disable TLB to update address
 */
#define PT_GLOBAL_BIT (1 << 8)
/**
 * @brief
 * Page Table Dirty flags, set by CPU,
 * if this bit set, means this page has been written
 */
#define PT_DIRTY_BIT (1 << 6)
#define PT_ACCESS_BIT (1 << 5)
#define PT_CACHED_BIT (1 << 4)
#define PT_WRITE_THROUGH_OR_BACK_BITE (1 << 3)
#define PT_USER_ACCESS_BITE (1 << 2)
#define PT_WRITEABLE_BITE (1 << 1)
#define PT_PRESENT_BITE (1 << 0)

long page_init(multiboot_info_t* mb_info);

#ifdef __cplusplus
}
#endif

#endif  // __EDUOS_MMU_H__