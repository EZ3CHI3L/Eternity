#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GLFW/glfw3.h>
#include <libeternity/error.h>

#ifdef __GNUC__
__attribute__ ((format(__printf__, 1, 2)))
#endif
void et_err_log(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    va_end(vargs);
}

void glfw_error_callback(int error, const char* description)
{
    puts(description);
}

void et_err_check(void)
{
    GLenum error_code;
    while ((error_code = glGetError() != GL_NO_ERROR))
    {
        switch (error_code)
        {
            case GL_NO_ERROR:
                ERR_LOG("OpenGL: %s\n", "GL_NO_ERROR");
                break;

            case GL_INVALID_ENUM:
                ERR_LOG("OpenGL: %s\n", "GL_INVALID_ENUM");
                break;

            case GL_INVALID_VALUE:
                ERR_LOG("OpenGL: %s\n", "OpenGL: GL_INVALID_VALUE");
                break;

            case GL_INVALID_OPERATION:
                ERR_LOG("OpenGL: %s\n", "GL_INVALID_OPERATION");
                break;

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                ERR_LOG("OpenGL: %s\n", "GL_INVALID_FRAMEBUFFER_OPERATION");
                break;

            case GL_OUT_OF_MEMORY:
                ERR_LOG("OpenGL: %s\n", "GL_OUT_OF_MEMORY");
                break;

            case GL_STACK_UNDERFLOW:
                ERR_LOG("OpenGL: %s\n", "GL_STACK_UNDERFLOW");
                break;

            case GL_STACK_OVERFLOW:
                ERR_LOG("OpenGL: %s\n", "GL_STACK_OVERFLOW");
                break;
        }
    }
}
