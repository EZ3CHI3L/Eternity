#ifndef MATH_H
#define MATH_H
#include <GLFW/glfw3.h>
typedef struct et_matrix
{
    int nrow, ncol, size;
    GLfloat *data;
} et_mat;

typedef struct et_matrix_stack
{
    et_mat model, view, proj;
} et_m_stack;
int et_m_stack_init(et_m_stack*);
#endif /* MATH_H */
