#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <libeternity/util.h>

void* __wrap_malloc(size_t n)
{
    check_expected(n);
    return mock_type(void*);
}

void safeMalloc_mallocFails_returnNull(void **state)
{
    void *rv;
    size_t n = 32;
    expect_value(__wrap_malloc, n, 32);
    will_return(__wrap_malloc, (void*) NULL);

    rv = safe_malloc(n);

    assert_null(rv);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(safeMalloc_mallocFails_returnNull),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
