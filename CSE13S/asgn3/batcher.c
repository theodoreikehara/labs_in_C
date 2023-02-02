//
// Theodore Ikehara
// Assignment 3
// Jan 24 2022
//
// About: implementation of batcher sort
#include "batcher.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t bit_length(uint32_t b) {
    // this is counting the amount of bits
    uint32_t c = 0;

    while (b) {
        b >>= 1;
        c++;
    }
    return c;
}

void comparator(uint32_t *A, uint32_t x, uint32_t y, Stats *stats) {
    // compares here
    if ((A[x] > A[y]) && cmp(stats, A[x], A[y])) {
        // Swaps here
        swap(stats, &A[x], &A[y]);
        // uint32_t temp = A[x];
        // A[x] = A[y];
        // A[y] = temp;
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {

    if (n == 0) {
        return;
    }

    uint32_t t = bit_length(n);
    uint32_t p = 1 << (t - 1);

    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(A, i, i + d, stats);
                }
            }

            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
