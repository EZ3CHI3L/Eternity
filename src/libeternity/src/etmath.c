#include <string.h>
#include <GLFW/glfw3.h>
#include <libeternity/engine.h>
#include <libeternity/etmath.h>
#include <libeternity/util.h>
#include <libeternity/error.h>

int et_mat_identity(et_mat *mat)
{
    int stride = 5;

    for (int i = 0; i < mat->size; i += stride)
        mat->data[i] = 1.0f;

    return 1;
}

int et_mat_init(et_mat *mat, unsigned short int nrow, unsigned short int ncol)
{
    mat->size = nrow * ncol;
    mat->nrow = nrow;
    mat->ncol = ncol;
    mat->data = et_calloc(mat->size, sizeof(GLfloat));

    if (!mat->data)
        return 0;

    et_mat_identity(mat);

    return 1;
}

int et_m_stack_init(et_m_stack *stack)
{
    int rv;
    unsigned short nrow = 4, ncol = 4;

    rv = et_mat_init(&stack->model, nrow, ncol);
    if (!rv)
    {
        ERR_LOG("Could not initialize matrix");
        return 0;
    }

    rv = et_mat_init(&stack->view, nrow, ncol);
    if (!rv)
    {
        ERR_LOG("Could not initialize matrix");
        return 0;
    }

    rv = et_mat_init(&stack->proj, nrow, ncol);
    if (!rv)
    {
        ERR_LOG("Could not initialize matrix");
        return 0;
    }

    return 1;
}
