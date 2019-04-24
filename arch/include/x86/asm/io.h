#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /** @brief Read a byte from an IO port
 *
 * @param _port The port you want to read from
 * @return The value which reads out from this port
 */
    inline static unsigned char inportb(unsigned short _port)
    {
        unsigned char rv;
        asm volatile("inb %1, %0"
                     : "=a"(rv)
                     : "dN"(_port));
        return rv;
    }

#ifdef __cplusplus
}
#endif