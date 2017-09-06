#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <errno.h>
#include <libeternity/args.h>
#include <config.h>

/* argp requires these to be global */
const char *argp_program_version = PACKAGE_VERSION;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct args *args = state->input;

    switch (key)
    {
        case 'q': case 's':
            args->silent = 1;
            break;

        case 'v':
            args->verbose = 1;
            break;

        case 'o':
            args->output_file = arg;
            break;

        case ARGP_KEY_ARG:
            if (args->count-- < 0)
                break;
            break;

        case ARGP_KEY_END:
            if (state->arg_num < 1)
            {
                argp_usage(state);
                return 0;
            }
            break;

        default:
            return ARGP_ERR_UNKNOWN;
            break;
    }
    return 0;
}

int parse_args(int argc, char **argv)
{
    int rv;
    const char* doc = "Eternity - your window to the good";
    char args_doc[] = "file1.jpg file2.png file3.bmp ...";

    struct argp_option options[] = {
        {"verbose",'v', 0, 0, "Produce verbose output", 0},
        {"quiet",  'q', 0, 0, "Don't produce any output", 0},
        {"silent", 's', 0, OPTION_ALIAS, NULL, 0},
        {"output", 'o', "FILE", 0, "Output to FILE instead of std output", 0},
        {0}
    };

    struct argp argp = {options, parse_opt, args_doc, doc, NULL, 0, NULL};
    struct args args;
    args.count = argc;
    args.silent = args.verbose = 0;
    args.output_file = "-";

    rv = argp_parse(&argp, argc, argv, ARGP_NO_EXIT, NULL, &args);

    if (rv > 0)
    {
        errno = rv;
        perror("argp_parse");
        return -1;
    }

    if (rv < 0)
        return -1;

    return 0;
}
