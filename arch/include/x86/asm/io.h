#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Read a byte from an IO port
 *
 * @param _port The port you want to read from
 * @return The value which reads out from this port
 */
inline static unsigned char inportb(unsigned short _port) {
    unsigned char rv;
    asm volatile("inb %1, %0" : "=a"(rv) : "dN"(_port));
    return rv;
}

/** @brief Read a word (2 byte) from an IO port
 *
 * @param _port The port you want to read from
 * @return The value which reads out from this port
 */
inline static unsigned short inportw(unsigned short _port) {
    unsigned short rv;
    asm volatile("inw %1, %0" : "=a"(rv) : "dN"(_port));
    return rv;
}

/** @brief Read a double word (4 byte) from an IO port
 *
 * @param _port The port you want to read from
 * @return The value which reads out from this port
 */
inline static unsigned int inportl(unsigned short _port) {
    unsigned int rv;
    asm volatile("inl %1, %0" : "=a"(rv) : "dN"(_port));
    return rv;
}

/** @brief Write a byte to an IO port
 *
 * @param _port The port you want to write to
 * @param _data the 1 byte value you want to write
 */
inline static void outportb(unsigned short _port, unsigned char _data) {
    asm volatile("outb %1, %0" ::"dN"(_port), "a"(_data));
}

/** @brief Write a word (2 bytes) to an IO port
 *
 * @param _port The port you want to write to
 * @param _data the 2 byte value you want to write
 */
inline static void outportw(unsigned short _port, unsigned short _data) {
    asm volatile("outw %1, %0" ::"dN"(_port), "a"(_data));
}

/** @brief Write a double word (4 bytes) to an IO port
 *
 * @param _port The port you want to write to
 * @param _data the 4 byte value you want to write
 */
inline static void outportl(unsigned short _port, unsigned int _data) {
    asm volatile("outl %1, %0" ::"dN"(_port), "a"(_data));
}

#ifdef __cplusplus
}
#endif