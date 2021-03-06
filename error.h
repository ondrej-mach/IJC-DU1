// error.h
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#ifndef _ERROR_H
#define _ERROR_H

void warning_msg(const char *format, ...);

void error_exit(const char *format, ...);

#endif
