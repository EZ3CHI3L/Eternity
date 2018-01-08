#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GLFW/glfw3.h>
#include <libeternity/error.h>

#ifdef __GNUC__
__attribute__ ((format(__printf__, 1, 2)))
#endif
void et_err_log(const char *start, ...)
{
    va_list vargs;
    va_start(vargs, start);
    vfprintf(stderr, start, vargs);
    va_end(vargs);
}

void glfw_error_callback(int error, const char* description)
{
    puts(description);
}

void et_err_check(void)
{
    GLenum error_code;
    while (((error_code = glGetError()) != GL_NO_ERROR))
    {
        switch (error_code)
        {
            case GL_NO_ERROR:
                fprintf(stderr, "GL_NO_ERROR\n");
                break;

            case GL_INVALID_ENUM:
                fprintf(stderr, "GL_INVALID_ENUM\n");
                break;

            case GL_INVALID_VALUE:
                fprintf(stderr, "OpenGL: GL_INVALID_VALUE\n");
                break;

            case GL_INVALID_OPERATION:
                fprintf(stderr, "GL_INVALID_OPERATION\n");
                break;

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                fprintf(stderr, "GL_INVALID_FRAMEBUFFER_OPERATION\n");
                break;

            case GL_OUT_OF_MEMORY:
                fprintf(stderr, "GL_OUT_OF_MEMORY\n");
                break;

            case GL_STACK_UNDERFLOW:
                fprintf(stderr, "GL_STACK_UNDERFLOW\n");
                break;

            case GL_STACK_OVERFLOW:
                fprintf(stderr, "GL_STACK_OVERFLOW\n");
                break;
        }
    }
}
