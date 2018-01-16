#ifndef ARGS_H
#define ARGS_H
#include <argp.h>
struct args
{
    int count, silent, verbose, file_count, error;
    char *output_file;
    char **file_list;
};
error_t parse_opt(int, char*, struct argp_state*);
struct args et_args_parse(int, char**);
#endif /* ARGS_H */
