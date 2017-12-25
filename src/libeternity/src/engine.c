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
    printf("Compiled against GLFW %i.%i.%i\nRunning against GLFW %i.%i.%i\n",
            GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION,
            major, minor, revision);

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
    glfwSwapInterval(0);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        glfwTerminate();
        fprintf(stderr, "GLEW [ %s ]\n", glewGetErrorString(err));
        ERR_LOG("%s\n", "Could not load OpenGL extensions");
        return 0;
    }

    return 1;
}

int et_shader_compile(GLenum shader_type, const GLchar *source)
{
    GLint compile_ok = GL_FALSE;
    GLsizei logsize = 0;

    GLuint shader = glCreateShader(shader_type);
    if (!shader)
    {
        fprintf(stderr, "Could not create shader program\n");
        return 0;
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        GLchar log[logsize];
        glGetShaderInfoLog(shader, logsize, 0, log);
        glDeleteShader(shader);
        fprintf(stderr, "[ SHADER ] %s", log);
        return 0;
    }
    return shader;
}

GLuint et_shader_load(void)
{
    const GLchar *v_shader_source =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vpos;"
        "void main() { gl_Position.xyz = vpos; }";

    const GLchar *f_shader_source =
        "#version 330 core\n"
        "out vec4 color;"
        "void main() { color = vec4(1.0, 1.0, 1.0, 1.0); }";

    GLuint vs = et_shader_compile(GL_VERTEX_SHADER, v_shader_source);

    if (!vs)
        return 0;

    GLuint fs = et_shader_compile(GL_FRAGMENT_SHADER, f_shader_source);

    if (!fs)
        return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint et_vao_new(GLuint index)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    return vao;
}

GLuint et_vbo_new(GLfloat *vcoords, size_t size)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vcoords, GL_STATIC_DRAW);

    return vbo;
}

int et_engine_run(GLFWwindow *window)
{
    int rv;

    const char *gl_version = glGetString(GL_VERSION);
    const char *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("OpenGL %s\nGLSL %s\n", gl_version, glsl_version);

    GLfloat vcoords[] = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    GLuint vbo = et_vbo_new(vcoords, sizeof(vcoords));
    GLuint vao = et_vao_new(0);
    GLuint shader = et_shader_load();

    if (!shader)
    {
        ERR_LOG("%s\n", "Could not load shaders");
        et_err_check();
        return 0;
    }

    et_err_check();
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glDeleteProgram(shader);
    return 1;
}
