#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <libeternity/args.h>
#include <libeternity/engine.h>
#include <libeternity/io.h>
#include <libeternity/etmath.h>
#include <libeternity/util.h>
#include <libeternity/error.h>

static void set_viewport(et_image *image, int width, int height)
{
    const double aw = (double) width / (double) image->width;
    const double ah = (double) height / (double) image->height;
    const double a = aw > ah ? ah : aw;
    unsigned int nw = image->width * a, nh = image->height * a;
    nw = nw < (GLuint) image->width ? nw : (GLuint) image->width;
    nh = nh < (GLuint) image->height ? nh : (GLuint) image->height;
    glViewport((width - nw) / 2, (height - nh) / 2, nw, nh);
}

void glfw_framebuffer_size_callback(GLFWwindow *window,
        int width, int height)
{
    et_image *image = glfwGetWindowUserPointer(window);

    if (!window)
        ERR_LOG("Could not get UserPointer");

    set_viewport(image, width, height);
}

int et_engine_init(GLFWwindow **window, et_image *image)
{
    int rv, width = image->width, height = image->height, major, minor, rev;
    glfwSetErrorCallback(glfw_error_callback);

    rv = glfwInit();
    if (rv == GLFW_FALSE)
    {
        ERR_LOG("Could not initialize glfw");
        return 0;
    }

    const char *version_string = glfwGetVersionString();
    glfwGetVersion(&major, &minor, &rev);
    puts(version_string);
    printf("Compiled against GLFW %i.%i.%i\nRunning against GLFW %i.%i.%i\n",
            GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION,
            major, minor, rev);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    *window = glfwCreateWindow(width, height, "Eternity", NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        ERR_LOG("Could not create window");
        return 0;
    }

    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, glfw_key_callback);
    glfwSetFramebufferSizeCallback(*window, glfw_framebuffer_size_callback);
    glfwSwapInterval(0);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        glfwTerminate();
        fprintf(stderr, "GLEW [ %s ]\n", glewGetErrorString(err));
        ERR_LOG("Could not load OpenGL extensions");
        return 0;
    }

    glfwSetWindowUserPointer(*window, image);

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
        "in vec4 vcoords;"
        "in vec2 tcoords;"
        "out vec2 uvcoords;"
        "uniform mat4 model, view, projection;"
        "void main() { gl_Position = vcoords * model * view * projection;"
        "uvcoords = tcoords; }";

    const GLchar *f_shader_source =
        "#version 330 core\n"
        "in vec2 uvcoords;"
        "out vec4 color;"
        "uniform sampler2D sampler;"
        "void main() { color = texture(sampler, uvcoords); }";

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
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint et_vao_new()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

GLuint et_buffer_new(GLenum target, GLfloat *data, size_t size)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(target, vbo);
    glBufferData(target, size, data, GL_STATIC_DRAW);

    return vbo;
}

GLuint et_texture_new(et_image *image)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);

    return texture;
}

int et_engine_run(GLFWwindow *window, et_image *image)
{
    const unsigned char *gl_ver = glGetString(GL_VERSION);
    const unsigned char *glsl_ver = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("OpenGL %s\nGLSL %s\n", gl_ver, glsl_ver);

    et_vao_new();

    GLfloat vc[] = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    GLfloat tc[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    GLuint vc_buffer = et_buffer_new(GL_ARRAY_BUFFER, vc, sizeof(vc));
    GLuint tc_buffer = et_buffer_new(GL_ARRAY_BUFFER, tc, sizeof(tc));

    GLuint shader = et_shader_load();

    if (!shader)
    {
        ERR_LOG("Could not load shaders");
        et_err_check();
        return 0;
    }

    et_m_stack m_stack = et_m_stack_init();

    if (m_stack.error)
        return 0;

    glUseProgram(shader);
    GLint model, view, proj;

    model = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(model, 1, GL_FALSE, m_stack.model.data);

    view = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(view, 1, GL_FALSE, m_stack.view.data);

    proj = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(proj, 1, GL_FALSE, m_stack.proj.data);

    GLuint vc_index = glGetAttribLocation(shader, "vcoords");
    glEnableVertexAttribArray(vc_index);
    glBindBuffer(GL_ARRAY_BUFFER, vc_buffer);
    glVertexAttribPointer(vc_index, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint tc_index = glGetAttribLocation(shader, "tcoords");
    glEnableVertexAttribArray(tc_index);
    glBindBuffer(GL_ARRAY_BUFFER, tc_buffer);
    glVertexAttribPointer(tc_index, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    et_texture_new(image);
    et_image_free(image);

    et_err_check();
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    et_m_stack_free(&m_stack);
    glDeleteProgram(shader);
    return 1;
}
