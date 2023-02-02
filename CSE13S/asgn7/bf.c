//
// Assignment 7: Author Identification
// Theodore Ikehara
// bf.c
//
// bloom filter
//
// source: Eugene's and Omar's sections

#include "bf.h"
#include "salts.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// creating bloomfilter here
BloomFilter *bf_create(uint32_t size) {

    // allocates the space for the bloom filter here
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));

    if (bf != NULL) {
        // setting primary bloomfilter
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;

        // setting secondary bloomfilter
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;

        // setting tertiary bloomfilter
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;

        bf->filter = bv_create(size);
    }

    // returns the bloom filter
    return bf;
}

void bf_delete(BloomFilter **bf) {

    // deletes the bit vector that is inside first
    bv_delete(&(*bf)->filter);

    // deletes the bloom filter
    free(*bf);
}

// returns the length of the bitvector
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// inserts the word into bloom filter
void bf_insert(BloomFilter *bf, char *word) {

    // this is the length of the bv
    uint32_t len = bv_length(bf->filter);

    // insert with primary
    bv_set_bit(bf->filter, hash(bf->primary, word) % len);
    // insert with secondary
    bv_set_bit(bf->filter, hash(bf->secondary, word) % len);
    // insert with tertiary
    bv_set_bit(bf->filter, hash(bf->tertiary, word) % len);

    return;
}

// probes the bloom filter checks if word is in bloom filter
bool bf_probe(BloomFilter *bf, char *word) {

    // this is the length of the bv
    uint32_t len = bv_length(bf->filter);

    // get with primary
    bool pri = bv_get_bit(bf->filter, hash(bf->primary, word) % len);
    // get with secondary
    bool sec = bv_get_bit(bf->filter, hash(bf->secondary, word) % len);
    // get with tertiary
    bool tri = bv_get_bit(bf->filter, hash(bf->tertiary, word) % len);

    return pri && sec && tri;
}

// prints the bf (bitvector)
void bf_print(BloomFilter *bf) {
    // prints the bit vector

    bv_print(bf->filter);
}
