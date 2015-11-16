#ifndef ERROR_H
#define ERROR_H
#define DIE(format, ...) die("File: '%s', line: %d\n" format, __FILE__, __LINE__, __VA_ARGS__)
void die(const char*, ...);
void check_error(void);
#endif /* ERROR_H */
