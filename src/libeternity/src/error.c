#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef __GNUC__
__attribute__ ((format(__printf__, 1, 2)))
#endif
_Noreturn void die(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    va_end(vargs);
    exit(EXIT_FAILURE);
}
