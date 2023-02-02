//
// Theodore Ikehara
// Assignment 3
// Jan 24 2022
//
// About: implementation of insert sort
//

#include "insert.h"

#include <stdint.h>
#include <stdio.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {

    for (uint32_t i = 1; i < n; i++) {
        // This is keeping the index of the array of the current index
        uint32_t j = i;
        uint32_t temp = A[move(stats, i)];

        // compares here +2
        //
        while (j > 0 && temp < A[j - 1] && cmp(stats, temp, A[j - 1])) {

            // Switches here
            //
            A[move(stats, j)] = A[j - 1];
            j--;
        }

        // Puts back the other value
        //
        A[move(stats, j)] = temp;
    }
}
