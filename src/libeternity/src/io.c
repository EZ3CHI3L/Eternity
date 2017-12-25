#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <libeternity/stb_image.h>

void glfw_key_callback(GLFWwindow* window,
        int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
            && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int et_image_load(char *filename)
{
    unsigned char *image;
    int width, height, bpp;
    image = stbi_load(filename, &width, &height, &bpp, 0);

    if (!image)
    {
        fprintf(stderr, "[ STBI ] Could not load image %s\n", filename);
        return 0;
    }

    printf("[ STBI ] loaded %s\n", filename);

    stbi_image_free(image);
    return 1;
}
