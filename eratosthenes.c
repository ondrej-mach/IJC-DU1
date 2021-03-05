#include "eratosthenes.h"

#include <math.h>
#include "bitset.h"

void Eratosthenes(bitset_t array) {
    bitset_index_t N = bitset_size(array);

    // 0 and 1 are not primes
    bitset_setbit(array, 0, 1);
    bitset_setbit(array, 1, 1);

    const bitset_index_t max = floor(sqrtf(N));
    for (bitset_index_t i=2; i<max; i++) {
        // if current number is prime
        if (bitset_getbit(array, i) == 0) {
            // delete all of is multiples from the array of potential primes
            for (bitset_index_t j = i*i; j<N; j+=i) {
                bitset_setbit(array, j, 1);
            }
        }
    }
}
