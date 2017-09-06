#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <libeternity/error.h>

#ifdef __GNUC__
__attribute__((malloc))
#endif
void *safe_malloc(size_t n)
{
    errno = 0;
    void *p = malloc(n);

    if (!p)
    {
        perror(NULL);
        fprintf(stderr, "Could not allocate %zu bytes\n", n);
        return NULL;
    }

    return p;
}

void et_freep(void **p)
{
    free(*p);
    *p = NULL;
}

#ifdef __GNUC__
__attribute__((format(__printf__, 1, 2)))
#endif
char* et_asprintf(const char *fmt, ...)
{
    char *p = NULL;
    va_list ap;
    int len;

    va_start(ap, fmt);
    len = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);

    if (len < 0)
        return NULL;

    p = safe_malloc(len + 1);

    va_start(ap, fmt);
    len = vsnprintf(p, len + 1, fmt, ap);
    va_end(ap);

    if (len < 0)
        et_freep((void**) &p);

    return p;
}
