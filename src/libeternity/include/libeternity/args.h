#ifndef ARGS_H
#define ARGS_H
#include <argp.h>
struct args
{
    int count, silent, verbose;
    char *output_file;
};
error_t parse_opt(int, char*, struct argp_state*);
int parse_args(int, char**);
#endif /* ARGS_H */
