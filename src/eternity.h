#ifndef ETERNITY_H
#define ETERNITY_H
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <argp.h>
void setup_vbo(GLuint*, GLshort*, GLuint);
void setup_vao(GLuint*);
void setup_shaders(GLuint*);
void glfw_error_callback(int, const char*);
void glfw_key_callback(GLFWwindow*, int, int, int, int);
void eternity_cleanup(GLFWwindow*);
static int parse_opt(int, char*, struct argp_state*);
uint8_t initialize_glfw(void);
#endif /* ETERNITY_H */
