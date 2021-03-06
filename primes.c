// primes.c
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0
// definice N a PRINT_LAST_N lze zmenit

#include <time.h>
#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"

// calculate primes from 0 to N-1 (N is not included)
#define N 200000000UL
// how many primes from the end sohould be printed
#define PRINT_LAST_N 10

void printLast(bitset_t array, int toPrint, bitset_index_t start) {
    if (toPrint == 0) {
        return;
    }

    do {
        start -= 1;
        if (start == 0) {
            return;
        }
    } while (bitset_getbit(array, start) == 1);

    printLast(array, toPrint-1, start);
    printf("%lu\n", start);
}

int main() {
    clock_t start = clock();
    bitset_create(array, N);
    Eratosthenes(array);
    printLast(array, PRINT_LAST_N, N);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
