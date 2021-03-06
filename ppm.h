// ppm.h
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0

#ifndef _PPM_H
#define _PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    // RGB bajty, celkem 3*xsize*ysize
    char data[];
};

struct ppm * ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif
