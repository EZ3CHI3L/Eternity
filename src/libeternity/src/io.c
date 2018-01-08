#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <libeternity/io.h>
#define STB_IMAGE_IMPLEMENTATION
#include <libeternity/stb_image.h>

void glfw_key_callback(GLFWwindow* window,
        int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
            && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int et_image_load(et_image *image, const char *filename)
{
    image->data = stbi_load(filename, &image->width,
            &image->height, &image->bpp, STBI_rgb_alpha);

    if (!image->data)
    {
        fprintf(stderr, "[ STBI ] Could not load image %s\n", filename);
        return 0;
    }

    printf("[ STBI ] loaded %s\n", filename);

    return 1;
}
