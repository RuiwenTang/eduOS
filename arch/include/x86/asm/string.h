#pragma once

#include <asm/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Copy a byte range from source to dest
 *
 * @param dest Destination address
 * @param src Source address
 * @param count Range of the byte field in bytes
 */
inline static void* memcpy(void* dest, const void* src, size_t count) {
    size_t i, j, k;

    asm volatile(
            "cld; rep movsl\n\t"
            "movl %4, %%ecx\n\t"
            "andl $3, %%ecx\n\t"
            "rep movsb\n\t"
            : "=&c"(i), "=&D"(j), "=&S"(k)
            : "0"(count / 4), "g"(count), "1"(dest), "2"(src)
            : "memory", "cc");

    return dest;
}

/** @brief Repeated write of a value to a whole range of bytes
 *
 * @param dest Destination address
 * @param val Value to flood the range with
 * @param count Size of target range in bytes
 */
inline static void* memset(void* dest, int val, size_t count) {
    size_t i, j;

    if (BUILTIN_EXPECT(!dest, 0)) return dest;

    asm volatile("cld; rep stosb"
                 : "=&c"(i), "=&D"(j)
                 : "a"(val), "1"(dest), "0"(count)
                 : "memory", "cc");

    return dest;
}

/** @brief Standard string length
 *
 * This function computed the length of the given null terminated string
 * just like the strlen functions you are used to.
 *
 * @return
 * - The length of the string
 * - 0 if str is a NULL pointer
 */
inline static size_t strlen(const char* str) {
    size_t len = 0;
    size_t i, j;

    if (BUILTIN_EXPECT(!str, 0)) return len;

    asm volatile("not %%ecx; cld; repne scasb; not %%ecx; dec %%ecx"
                 : "=&c"(len), "=&D"(i), "=&a"(j)
                 : "2"(0), "1"(str), "0"(len)
                 : "memory", "cc");
    return len;
}

#ifdef __cplusplus
}
#endif