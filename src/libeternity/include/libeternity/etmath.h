#ifndef MATH_H
#define MATH_H
#include <GLFW/glfw3.h>
typedef struct et_matrix
{
    int nrow, ncol, size, error;
    GLfloat *data;
} et_mat;

typedef struct et_matrix_stack
{
    int error;
    et_mat model, view, proj;
} et_m_stack;
et_m_stack et_m_stack_init(void);
#endif /* MATH_H */
