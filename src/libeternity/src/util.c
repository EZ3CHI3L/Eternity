#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <GLFW/glfw3.h>
#include <libeternity/args.h>
#include <libeternity/io.h>
#include <libeternity/engine.h>
#include <libeternity/etmath.h>
#include <libeternity/stb_image.h>
#include <libeternity/error.h>

#ifdef __GNUC__
__attribute__((malloc))
#endif
void *et_malloc(size_t n)
{
    errno = 0;
    void *p = malloc(n);

    if (!p)
    {
        perror(NULL);
        ERR_LOG("Could not allocate %zu bytes", n);
        return NULL;
    }

    return p;
}

void *et_calloc(size_t nmemb, size_t n)
{
    errno = 0;
    void *p = calloc(nmemb, n);

    if (!p)
    {
        perror(NULL);
        ERR_LOG("Could not allocate %zu bytes", nmemb * n);
        return NULL;
    }

    return p;
}

void et_freep(void **p)
{
    if (p && *p)
    {
        free(*p);
        *p = NULL;
    }
}

void et_args_free(struct args *args)
{
    et_freep((void**)&args->file_list);
}

void et_mat_free(et_mat *mat)
{
    et_freep((void**)&mat->data);
}

void et_m_stack_free(et_m_stack *stack)
{
    et_mat_free(&stack->model);
    et_mat_free(&stack->view);
    et_mat_free(&stack->proj);
}

void et_image_free(et_image *image)
{
    stbi_image_free(image->data);
}

void et_cleanup(struct args *args)
{
    et_args_free(args);
    glfwTerminate();
}

/*
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
*/
