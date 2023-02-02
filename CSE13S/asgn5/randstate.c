

// Theodore Ikehara
// CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// randstate.c
//

#include "randstate.h"

void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void randstate_clear(void) {
    gmp_randclear(state);
}
