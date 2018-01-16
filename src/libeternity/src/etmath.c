#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <libeternity/engine.h>
#include <libeternity/etmath.h>
#include <libeternity/util.h>
#include <libeternity/error.h>

et_mat et_mat_init(unsigned short int nrow, unsigned short int ncol)
{
    et_mat mat;
    mat.error = 0;
    mat.size = nrow * ncol;
    mat.nrow = nrow;
    mat.ncol = ncol;
    mat.data = et_calloc(mat.size, sizeof(GLfloat));

    if (!mat.data)
    {
        mat.error = 1;
        return mat;
    }

    int stride = 5;
    for (int i = 0; i < mat.size; i += stride)
        mat.data[i] = 1.0f;

    return mat;
}

et_m_stack et_m_stack_init()
{
    unsigned short nrow = 4, ncol = 4;
    et_m_stack stack;
    stack.error = 0;

    stack.model = et_mat_init(nrow, ncol);
    if (stack.model.error)
    {
        stack.error = 1;
        ERR_LOG("Could not initialize matrix");
        return stack;
    }

    stack.view = et_mat_init(nrow, ncol);
    if (stack.view.error)
    {
        stack.error = 1;
        ERR_LOG("Could not initialize matrix");
        return stack;
    }

    stack.proj = et_mat_init(nrow, ncol);
    if (stack.proj.error)
    {
        stack.error = 1;
        ERR_LOG("Could not initialize matrix");
        return stack;
    }

    return stack;
}
