// primes.c
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Ondřej Mach, FIT
// Přeloženo: gcc 9.3.0
// definice N a PRINT_LAST_N lze zmenit

#include <time.h>
#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"

// calculate primes from 0 to N (N is not included)
#define N 200000000UL
// how many primes from the end should be printed
#define PRINT_LAST_N 10

// prints last N primes from bitset, where 0s are primes.
// toPrint parameter says, how many numbers are still left to print
void printLast(bitset_t array, int toPrint, bitset_index_t start) {
    // if there is nothing left to print, end recursion
    if ((toPrint == 0) || (start == 0)) {
        return;
    }

    // search until you find a prime
    while (bitset_getbit(array, start) != 0) {
        start--;
        // if you are at the beginning of the bitset, return without recursion
        if (start == 0) {
            return;
        }
    }
    // recursive call
    printLast(array, toPrint-1, start-1);
    printf("%lu\n", start);
}

int main(void) {
    clock_t start = clock();
    // define and initialize the bitset
    bitset_create(array, N);
    // find the primes
    Eratosthenes(array);
    printLast(array, PRINT_LAST_N, N-1);
    // print the time in specified format
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
