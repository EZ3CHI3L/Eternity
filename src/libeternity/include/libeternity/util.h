#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
struct args;
typedef struct et_matrix_stack et_m_stack;
typedef struct et_image_struct et_image;
void *et_malloc(size_t);
void *et_calloc(size_t, size_t);
void et_freep(void**);
void et_cleanup(struct args*);
void et_args_free(struct args*);
void et_m_stack_free(et_m_stack*);
void et_image_free(et_image*);
#endif /* UTIL_H */
