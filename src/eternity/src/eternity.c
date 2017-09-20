#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libeternity/args.h>
#include <libeternity/util.h>

int main(int argc, char **argv)
{
    int file_list_size = argc * sizeof(char*);
    struct args args;
    args.count = argc;
    args.silent = args.verbose = 0;
    args.output_file = "-";
    args.file_count = 0;
    args.file_list = safe_malloc(file_list_size);
    memset(args.file_list, 0, file_list_size);

    int rv;
    rv = parse_args(argc, argv, &args);

    if (rv == -1)
    {
        et_cleanup(&args);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < args.file_count; ++i)
        printf("%s\n", args.file_list[i]);

    et_cleanup(&args);
    return EXIT_SUCCESS;
}
