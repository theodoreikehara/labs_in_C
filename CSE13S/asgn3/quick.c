//
// Theodore Ikehara
// Assignment 3
// Jan 24 2022
//
// About: implementation of quick sort
//

#include "quick.h"

#include <stdio.h>
#include <stdlib.h>

// This is a partition function called in the sorter function
uint32_t partition(uint32_t *A, int lo, int hi, Stats *stats) {

    uint32_t i = lo - 1;

    for (int j = lo; j < hi; j++) {
        cmp(stats, j, hi);
        // compares here
        if ((A[j - 1] < A[hi - 1]) && cmp(stats, A[j - 1], A[hi - 1])) {
            i++;

            // swaps here
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }

    // swaps here
    swap(stats, &A[i], &A[hi - 1]);

    return i + 1;
}

// This is the recursion function that is called in the main function of this
// algorithm
void quick_sorter(uint32_t *A, int lo, int hi, Stats *stats) {
    // compares but not of the array
    if (lo < hi) {
        // This is the recursion portion of the program
        uint32_t p = partition(A, lo, hi, stats);
        quick_sorter(A, lo, p - 1, stats);
        quick_sorter(A, p + 1, hi, stats);
    }
}

// This is the main function of this program
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(A, 1, n, stats);
}
