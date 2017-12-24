#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <libeternity/io.h>
#include <libeternity/error.h>

int et_engine_init(GLFWwindow **window)
{
    int rv, width = 640, height = 480, major, minor, revision;
    GLFWerrorfun callback = glfwSetErrorCallback(glfw_error_callback);

    rv = glfwInit();
    if (rv == GLFW_FALSE)
    {
        ERR_LOG("%s\n", "Could not initialize glfw");
        return 0;
    }

    glfwGetVersion(&major, &minor, &revision);

    printf("Compiled against GLFW %i.%i.%i\n",
            GLFW_VERSION_MAJOR,
            GLFW_VERSION_MINOR,
            GLFW_VERSION_REVISION);

    printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    *window = glfwCreateWindow(width, height, "Eternity", NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        ERR_LOG("%s\n", "Could not create window");
        return 0;
    }

    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, glfw_key_callback);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        glfwTerminate();
        fprintf(stderr, "GLEW [ %s ]\n", glewGetErrorString(err));
        ERR_LOG("%s\n", "Could not load OpenGL extensions");
        return 0;
    }

    et_err_check();

    return 1;
}

int et_engine_run(GLFWwindow *window)
{
    int rv;

    const char *gl_version = glGetString(GL_VERSION);
    const char *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("OpenGL %s\nGLSL %s\n", gl_version, glsl_version);

    GLshort vcoords[] = {
        -1, 1, 0,
        1, 1, 0,
        -1, -1, 0,
        1, -1, 0
    };

    GLfloat model[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat view[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat projection[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat transform[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    return 1;
}
