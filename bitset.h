#ifndef _BITSET_H
#define _BITSET_H

#include <limits.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "error.h"

typedef unsigned long * bitset_t;
typedef unsigned long bitset_index_t;
// size of unsigned long in bits
#define UL_SIZE_BITS ((unsigned long)(sizeof(unsigned long) * CHAR_BIT))

// create and initialize static array. It will be initialized to all zeros
#define bitset_create(name, size) \
    static_assert(size > 0, "bitset_alloc: Velikost pole musí bý větší než 0"); \
    unsigned long name[1 + (size + UL_SIZE_BITS - 1) / UL_SIZE_BITS] = {size, }

#define bitset_alloc(name, size) \
    if (size <= 0) error_exit("bitset_alloc: Chyba alokace paměti"); \
    bitset_t name = calloc(1 + (size + UL_SIZE_BITS - 1) / UL_SIZE_BITS, sizeof(unsigned long)); \
    if (name == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); \
    name[0] = size

#define bitset_free(name) free(name)


#ifndef USE_INLINE
// the size of the bitset in bits
#define bitset_size(name) name[0]

// TODO to check or not to check negatives?
#define _bitset_in_range(name, index) (index < bitset_size(name))

#define _bitset_setbit_error(name, index) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(name)-1)
// sets value one to the appropriate bit
#define _bitset_set(name, index) (name[1UL + index / UL_SIZE_BITS] |= (1UL << (index % UL_SIZE_BITS)))
// sets value zero to the appropriate bit
#define _bitset_clear(name, index) (name[1UL + index / UL_SIZE_BITS] &= ~(1UL << (index % UL_SIZE_BITS)))
// sets the bit to the value passed
#define _bitset_setbit_nocheck(name, index, value) (value ? _bitset_set(name, index) : _bitset_clear(name, index))
// checks the bounds before setting th bit
#define bitset_setbit(name, index, value) (_bitset_in_range(name,index) ? _bitset_setbit_nocheck(name, index, value) : (_bitset_setbit_error(name, index), 0))


#define _bitset_getbit_error(name, index) error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(name)-1)
// reads one bit from the array. Skip one index, which is used for size.
// then bit shift the result down to 1's place.
// Finally do bitwise AND with 1 to eliminate every other bit
#define _bitset_getbit_nocheck(name, index) ((name[1UL + index / UL_SIZE_BITS] >> (index % UL_SIZE_BITS)) & 1UL)

#define bitset_getbit(name, index) (_bitset_in_range(name,index) ? _bitset_getbit_nocheck(name, index) : (_bitset_getbit_error(name, index), 0))


#else // USE_INLINE is defined

static inline bitset_index_t bitset_size(bitset_t name) {
    return name[0];
}

static inline void bitset_setbit(bitset_t name, bitset_index_t index, bool value) {
    if (index < bitset_size(name)) {
        // exits the program
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(name)-1);
    }
    if (value) {
        name[1UL + index / UL_SIZE_BITS] |= (1UL << (index % UL_SIZE_BITS));
    } else {
        name[1UL + index / UL_SIZE_BITS] &= ~(1UL << (index % UL_SIZE_BITS));
    }
}

static inline bool bitset_getbit(bitset_t name, bitset_index_t index) {
    if (index < bitset_size(name)) {
        // exits the program
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(name)-1);
    }
    return(name[1UL + index / UL_SIZE_BITS] >> (index % UL_SIZE_BITS)) & 1UL;
}

#endif // USE_INLINE

#endif // _BITSET_H
