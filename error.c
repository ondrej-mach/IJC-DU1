// error.c
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *format, ...) {
    va_list args;
    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);
}

void error_exit(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}
