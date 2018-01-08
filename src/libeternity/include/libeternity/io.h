#ifndef IO_H
#define IO_H
#include <GLFW/glfw3.h>
typedef struct et_image_struct
{
    unsigned char *data;
    int width, height, bpp;
} et_image;
int et_image_load(et_image*, const char*);
void glfw_key_callback(GLFWwindow*, int, int, int, int);
#endif /* IO_H */
