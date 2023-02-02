
//
// Assignment 7: Author Identification
// Theodore Ikehara
// bv.c
//
// bit vector
//

#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// This creates the bit vector
BitVector *bv_create(uint32_t length) {

    // this dynamically allocates the space for the bit vector
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));

    if (bv != NULL) {
        bv->length = length;
        // This allocates space for the vector itself
        bv->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
    }

    // This returns the created bit vector
    return bv;
}

// This clears the allocated space
void bv_delete(BitVector **bv) {

    // frees the vector first
    free((*bv)->vector);
    // frees the entire adt
    free(*bv);

    return;
}

// this gives back the bv length
uint32_t bv_length(BitVector *bv) {
    // gets the length
    return bv->length;
}

// This sets the bits at position i
bool bv_set_bit(BitVector *bv, uint32_t i) {

    // checks to see if i is in length
    if (i >= bv->length) {
        return false;
    }

    // calculates the byte
    uint8_t byte = bv->vector[(i % bv->length) / 8];
    // calculates the location
    uint8_t count = i % 8;

    // set the bit
    bv->vector[(i % bv->length) / 8] = byte | (1 << count);

    return true;
}

// This clears the bit at position i
bool bv_clr_bit(BitVector *bv, uint32_t i) {

    // checks to see if i is in length
    if (i >= bv->length) {
        return false;
    }

    // sets the byte
    uint8_t byte = bv->vector[(i % bv->length) / 8];
    // location
    uint8_t count = i % 8;
    // bit mask
    uint8_t mask = ~(1 << count);
    // clears the bit
    bv->vector[(i % bv->length) / 8] = byte & mask;

    // returns true if success
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {

    uint8_t position = i % 8;
    uint8_t bit;

    // checks if this location is valid
    if ((i >= bv->length)) {
        return false;
    }

    // gets the bit
    bit = (bv->vector[i / 8] & (0x1 << position)) >> position;

    // this is if the bit is equal to 1
    if (bit) {
        return true;
    }
    // this is if the bit is 0
    return false;
}

// prints out the bit vector
void bv_print(BitVector *bv) {
    // iterates through bit vector and prints
    for (int i = 0; i < (int) bv->length; i += 1) {

        printf("%d", bv_get_bit(bv, i));
    }
    printf("\n");
}
