#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
void *safe_malloc(size_t);
void et_freep(void**);
char *et_asprintf(const char*, ...);
#endif /* UTIL_H */
