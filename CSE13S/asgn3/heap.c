//
// Theodore Ikehara
// Assignment 3
// Jan 24 2022
//
// About: implementation of heap sort
//

#include "heap.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// part of the heap maintainence creating the parent child node relation
uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last, Stats *stats) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // compares
    if ((right <= last) && (A[right - 1] > A[left - 1]) && cmp(stats, A[right - 1], A[left - 1])) {
        return right;
    }

    return left;
}

void fix_heap(uint32_t *A, uint32_t first, uint32_t last, Stats *stats) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(A, mother, last, stats);

    // compares here
    while ((mother <= floor(last / 2)) && !(found)) {
        if ((A[mother - 1] < A[great - 1]) && cmp(stats, A[mother - 1], A[great - 1])) {

            // swaps
            // uint32_t temp = A[mother - 1];
            // A[mother - 1] = A[great - 1];
            // A[great - 1] = temp;
            swap(stats, &A[mother - 1], &A[great - 1]);

            mother = great;
            great = max_child(A, mother, last, stats);
        } else {
            found = true;
        }
    }
}

// builds the heap
void build_heap(uint32_t *A, uint32_t first, uint32_t last, Stats *stats) {
    for (uint32_t father = floor(last / 2); father > first - 1; father--) {
        fix_heap(A, father, last, stats);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);

    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last, stats);

    for (uint32_t leaf = last; leaf > first; leaf--) {
        // Swaps here
        swap(stats, &A[first - 1], &A[leaf - 1]);
        // uint32_t temp = A[first - 1];
        // A[first - 1] = A[leaf - 1];
        // A[leaf - 1] = temp;

        fix_heap(A, first, leaf - 1, stats);
    }
}
