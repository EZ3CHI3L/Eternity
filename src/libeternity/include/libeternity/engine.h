#ifndef ENGINE_H
#define ENGINE_H
#include <GLFW/glfw3.h>
typedef struct et_image_struct et_image;
int et_engine_init(GLFWwindow**, et_image*);
int et_engine_run(GLFWwindow*, et_image*);
#endif /* ENGINE_H */
