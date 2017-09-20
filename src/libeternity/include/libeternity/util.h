#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include "args.h"
void *safe_malloc(size_t);
void et_freep(void**);
void et_cleanup(struct args*);
#endif /* UTIL_H */
