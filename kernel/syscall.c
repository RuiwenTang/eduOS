#include <eduos/stdarg.h>
#include <eduos/stddef.h>

ssize_t syscall_handler(uint32_t sys_nr, ...) {
    va_list vl;

    va_start(vl, sys_nr);

    va_end(vl);
    return 0;
}