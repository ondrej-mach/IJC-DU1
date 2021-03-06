#include "bitset.h"

//#ifdef USE_INLINE

extern bitset_index_t bitset_size(bitset_t name);

extern void bitset_setbit(bitset_t name, bitset_index_t index, bool value);

extern bool bitset_getbit(bitset_t name, bitset_index_t index);

//#endif