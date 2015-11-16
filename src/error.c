#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "error.h"

void die(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    va_end(vargs);
    exit(1);
}

void check_error(void)
{
    GLenum error_code;
    const GLubyte *error_string;

    if ((error_code = glGetError()) != GL_NO_ERROR)
    {
        error_string = gluErrorString(error_code);
        DIE("OpenGL Error: %s\n", error_string);
    }
}
