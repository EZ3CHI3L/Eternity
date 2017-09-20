#ifndef ARGS_H
#define ARGS_H
#include <argp.h>
struct args
{
    int count, silent, verbose, file_count;
    char *output_file;
    char **file_list;
};
error_t parse_opt(int, char*, struct argp_state*);
int parse_args(int, char**, struct args*);
#endif /* ARGS_H */
