#ifndef ERROR_H
#define ERROR_H
#define DIE(format, ...) die("ERROR [ %s:%d in %s() ]\n" format, \
        __FILE__, __LINE__, __func__, __VA_ARGS__)
void die(const char*, ...);
void check_error(void);
#endif /* ERROR_H */
