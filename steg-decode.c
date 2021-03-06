// primes.c
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0
// definice START_BYTE lze zmenit, urcuje na kterem bajtu zacina sifra

#include "ppm.h"
#include "eratosthenes.h"
#include "bitset.h"

#include <stdio.h>
#include <limits.h>


#define START_BYTE 23


int main(int argc, char **argv) {
    if (argc != 2) {
        error_exit("Nesprávný počet argumentů\nPoužití: %s obrázek.ppm\n", argv[0]);
    }

    struct ppm *img = ppm_read(argv[1]);
    if (img == NULL) {
        error_exit("Obrázek %s nebylo možné načíst\n", argv[1]);
    }

    const unsigned long N = img->xsize * img->ysize * 3;
    bitset_alloc(mask, N);
    Eratosthenes(mask);

    char msg[1000] = {0, };
    // counts in bits
    unsigned long msgIndex = 0;
    bool terminated = false;

    for (unsigned long i=START_BYTE; i<N; i++) {
        // if byte is at the right index
        if (bitset_getbit(mask, i) == 0) {
            // take the last bit from byte
            bool bit = img->data[i] & 1;
            msg[msgIndex/CHAR_BIT] |= (char)bit << (msgIndex%CHAR_BIT);
            msgIndex++;
            // if you've just finished reading one byte
            if (msgIndex%CHAR_BIT == 0) {
                // test for terminating zero
                if (msg[msgIndex/CHAR_BIT - 1] == '\0') {
                    // end of hidden message
                    break;
                }
            }
        }
    }

    if (!terminated) {
        ppm_free(img);
        bitset_free(mask);
        error_exit("Dekódovaný řetězec není ukončen '\\0'");
    }

    printf("%s", msg);
    ppm_free(img);
    bitset_free(mask);
    return 0;
}
