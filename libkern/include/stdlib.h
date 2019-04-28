#pragma once

#include <eduos/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief General page allocator function
 *
 * This function allocates and maps whole pages.
 * To avoid fragmentation you should use kmalloc() and kfree()!
 *
 * @param sz Desired size of the new memory
 * @param flags Flags to for map_region(), vma_add()
 *
 * @return Pointer to the new memory range
 */
void* palloc(size_t sz, uint32_t flags);

/** @brief Free general kernel memory
 *
 * The pmalloc() doesn't track how much memory was allocated for which pointer,
 * so you have to specify how much memory shall be freed.
 *
 * @param sz The size which should freed
 */
void pfree(void* addr, size_t sz);

/** @brief The memory allocator function
 *
 * This allocator uses a buddy system to manage free memory.
 *
 * @return Pointer to the new memory range
 */
void* kmalloc(size_t sz);

/** @brief The memory free function
 *
 * Releases memory allocated by malloc()
 *
 * @param addr The address to the memory block allocated by malloc()
 */
void kfree(void* addr);

/** @brief String to long
 *
 * @return Long value of the parsed numerical string
 */
long strtol(const char* str, char** endptr, int base);

/** @brief String to unsigned long
 *
 * @return Unsigned long value of the parsed numerical string
 */
unsigned long strtoul(const char* nptr, char** endptr, int base);

/** @brief ASCII to integer
 *
 * Convenience function using strtol().
 *
 * @return Integer value of the parsed numerical string
 */
static inline int atoi(const char* str) {
    return (int)strtol(str, (char**)0, 10);
}

#ifdef __cplusplus
}
#endif