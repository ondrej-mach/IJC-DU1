#include "ppm.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IMAGE_SIZE 8000

bool isWhitespace(char c) {
    return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}

struct ppm *ppm_read(const char *filename) {

    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        warning_msg("Nelze otevřít soubor %s\n", filename);
        return NULL;
    }

    char magic[3];
    unsigned maxValue;
    unsigned xsize;
    unsigned ysize;

    unsigned numRead;
    numRead = fscanf(f, "%2s %u %u %u", magic, &xsize, &ysize, &maxValue);

    if (!isWhitespace(fgetc(f)) || (numRead != 4) ||
        strcmp(magic, "P6") || (maxValue != 255)) {
        warning_msg("Obrázek není v kompatibilním formátu\n");
        fclose(f);
        return NULL;
    }

    if ((xsize > MAX_IMAGE_SIZE) || (ysize > MAX_IMAGE_SIZE)) {
        warning_msg("Maximální velikost obrázku je %d*%d\n", MAX_IMAGE_SIZE, MAX_IMAGE_SIZE);
        fclose(f);
        return NULL;
    }

    size_t numBytes = xsize * ysize * 3;

    // allocate for struct and flexible array member
    struct ppm *img = malloc(sizeof(struct ppm) + numBytes);
    img->xsize = xsize;
    img->ysize = ysize;

    // read bytes from file
    size_t actualRead = fread(img->data, sizeof(char), numBytes, f);

    bool end = (fgetc(f) == EOF);
    fclose(f);

    // if file hasnt yet ended or it was shorter than expected
    if (!end || (actualRead < numBytes)) {
        warning_msg("Neočekávaná délka vstupního souboru\n");
        free(img);
        return NULL;
    }

    return img;
}

void ppm_free(struct ppm *img) {
    free(img);
}
