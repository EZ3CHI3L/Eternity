#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <argp.h>
#include <libeternity/args.h>

int __wrap_argp_parse(const struct argp *argp,
        int argc, char **argv, unsigned flags,
        int *arg_index, void *input)
{
    check_expected(argc);
    check_expected(argv);
    return mock_type(int);
}

void __wrap_argp_usage(struct argp_state *state)
{
    assert_non_null(state);
}

void parseArgs_argpSucceeds_returnNonNull(void **state)
{
    int rv, argc = 2;
    char *argv[argc];
    argv[0] = "eternity";
    argv[1] = "--help";
    struct args *args;

    expect_value(__wrap_argp_parse, argc, 2);
    expect_memory(__wrap_argp_parse, argv, &argv, sizeof(argv));
    will_return(__wrap_argp_parse, 0);

    args = et_args_parse(argc, argv);

    assert_non_null(args);
}

void parseArgs_argpFails_returnNull(void **state)
{
    int rv, argc = 2;
    char *argv[argc];
    argv[0] = "eternity";
    argv[1] = "--help";
    struct args *args;

    expect_value(__wrap_argp_parse, argc, 2);
    expect_memory(__wrap_argp_parse, argv, &argv, sizeof(argv));
    will_return(__wrap_argp_parse, -1);

    args = et_args_parse(argc, argv);

    assert_null(args);
}

void parseOpt_qEncountered_setSilentFlag(void **state)
{
    int rv;
    struct argp_state argp_state;
    struct args args;
    args.silent = 0;
    struct args *argsp = &args;
    argp_state.input = (void *) argsp;

    rv = parse_opt((int) 'q', 0, &argp_state);
    argsp = (struct args*) argp_state.input;

    assert_int_equal(argsp->silent, 1);
    assert_int_equal(rv, 0);
}

void parseOpt_sEncountered_setSilentFlag(void **state)
{
    int rv;
    struct argp_state argp_state;
    struct args args;
    args.silent = 0;
    struct args *argsp = &args;
    argp_state.input = (void *) argsp;

    rv = parse_opt((int) 's', 0, &argp_state);
    argsp = (struct args*) argp_state.input;

    assert_int_equal(argsp->silent, 1);
    assert_int_equal(rv, 0);
}

void parseOpt_vEncountered_setVerboseFlag(void **state)
{
    int rv;
    struct argp_state argp_state;
    struct args args;
    args.verbose = 0;
    struct args *argsp = &args;
    argp_state.input = (void *) argsp;

    rv = parse_opt((int) 'v', 0, &argp_state);
    argsp = (struct args*) argp_state.input;

    assert_int_equal(argsp->verbose, 1);
    assert_int_equal(rv, 0);
}

void parseOpt_oEncountered_setOutputFile(void **state)
{
    int rv;
    struct argp_state argp_state;
    struct args args;
    args.output_file = NULL;
    struct args *argsp = &args;
    argp_state.input = (void *) argsp;

    rv = parse_opt((int) 'o', "/tmp/libeternity.out", &argp_state);
    argsp = (struct args*) argp_state.input;

    assert_non_null(argsp->output_file);
    assert_int_equal(rv, 0);
}

void parseOpt_noArguments_printUsage(void **state)
{
    int rv;
    struct argp_state argp_state;
    argp_state.arg_num = 0;
    struct args args;
    struct args *argsp = &args;
    argp_state.input = (void *) argsp;

    rv = parse_opt((int) ARGP_KEY_END, 0, &argp_state);
    argsp = (struct args*) argp_state.input;

    assert_int_equal(argp_state.arg_num, 0);
    assert_int_equal(rv, 0);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(parseArgs_argpSucceeds_returnNonNull),
        cmocka_unit_test(parseArgs_argpFails_returnNull),
        cmocka_unit_test(parseOpt_qEncountered_setSilentFlag),
        cmocka_unit_test(parseOpt_sEncountered_setSilentFlag),
        cmocka_unit_test(parseOpt_vEncountered_setVerboseFlag),
        cmocka_unit_test(parseOpt_oEncountered_setOutputFile),
        cmocka_unit_test(parseOpt_noArguments_printUsage),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
