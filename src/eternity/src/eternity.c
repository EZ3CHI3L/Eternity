#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <libeternity/args.h>
#include <libeternity/engine.h>
#include <libeternity/io.h>
#include <libeternity/util.h>
#include <libeternity/error.h>

int main(int argc, char **argv)
{
    int rv;

    struct args *args = et_args_parse(argc, argv);

    if (args == NULL || args->file_list[0] == NULL)
        return EXIT_FAILURE;

    et_image image;
    rv = et_image_load(&image, args->file_list[0]);
    if(!rv)
    {
        et_args_free(args);
        return EXIT_FAILURE;
    }

    GLFWwindow *window;
    rv = et_engine_init(&window, &image);
    if (!rv)
    {
        et_image_free(&image);
        et_args_free(args);
        return EXIT_FAILURE;
    }

    rv = et_engine_run(window, &image);
    if (!rv)
    {
        et_cleanup(args);
        return EXIT_FAILURE;
    }

    et_cleanup(args);
    return EXIT_SUCCESS;
}
