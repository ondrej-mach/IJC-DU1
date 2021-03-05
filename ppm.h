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
