
// Theodore Ikehara Jan 21, 2022 CSE13s Assignment 3 Sorting: Putting your affairs in order
//
// contains the main function and performs the sorting meathods
//
// Citing: Eugene's Section and lab man

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// These are the sorting routines
#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
//
// These are the data headers
#include "set.h"
#include "stats.h"

#define OPTIONS "ahbiqr:n:p:H"

typedef enum { INSERT, BATCHER, HEAP, QUICK } set;

void help() {
    printf("SYNOPSIS\n\t");
    printf("A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n\t");
    printf("./sorting [-Haibhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -H              Display program help and usage.\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -i              Enables Insertion Sort.\n");
    printf("   -b              Enables Batcher Sort.\n");
    printf("   -h              Enables Heap Sort.\n");
    printf("   -q              Enables Quick Sort\n");
    printf("   -n length       Specify number of array elements (default: 100).\n");
    printf("   -p elements     Specify number of elements to print (default: 100).\n");
    printf("   -r seed         Specify random seed (default: 13371453).\n");
}

int main(int argc, char **argv) {

    Stats stat = { 0, 0 };
    Set s = empty_set();

    // Default values of variables that users can set
    // The length of the array
    int length = 100;
    // The amount of elements that will be printed
    int elements = 100;
    // The random seed in that will be used
    int seed = 13371453;
    int opt = 0;

    // Start of the getopt loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            s = insert_set(HEAP, s);
            s = insert_set(BATCHER, s);
            s = insert_set(INSERT, s);
            s = insert_set(QUICK, s);
            break; // -a enables all sorting
        case 'h': s = insert_set(HEAP, s); break; // -h enables heap sort
        case 'b': s = insert_set(BATCHER, s); break; // -b anables batcher sort
        case 'i': s = insert_set(INSERT, s); break; // -i enables insert sort
        case 'q': s = insert_set(QUICK, s); break; // -q enables quick sort
        case 'r': seed = atoi(optarg); break; // -r random seed
        case 'n': length = atoi(optarg); break; // -n length of array
        case 'p': elements = atoi(optarg); break; // -p amound to print
        default: help(); return 0;
        }
    }

    // random seed set here
    srandom(seed);
    // Standard array this is not supposed to be changed
    uint32_t *arr = (uint32_t *) malloc(length * sizeof(uint32_t));
    for (int i = 0; i < length; i++) {
        arr[i] = random() & ~(3 << 30);
    }
    // This is the duplicate array that will be reset each time after the
    // sorting routine is finished
    uint32_t *dupe = (uint32_t *) malloc(length * sizeof(uint32_t));
    for (int i = 0; i < length; i++) {
        dupe[i] = arr[i];
    }
    //
    // Starts the main part of the code
    // Starts see whitch sets were enabled
    bool counter = true;
    for (int i = 0; i < 4; i++) {
        if (length < 100) {
            elements = length;
        }
        if (member_set(i, s)) {
            counter = false;

            switch (i) {
                // This does the heap sort //

            case HEAP:
                // This is where heap sort is ran
                heap_sort(&stat, dupe, length);

                // This is introing the sort and showing the results
                printf("Heap Sort, ");
                printf("%d elements, ", length);
                printf("%lu moves, ", stat.moves);
                printf("%lu compares", stat.compares);

                for (int i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, dupe[i]);
                }

                printf("\n");

                // resets everything
                for (int i = 0; i < length; i++) {
                    dupe[i] = arr[i];
                }
                reset(&stat);
                break;
            case BATCHER:
                // This is where insert sort is ran
                batcher_sort(&stat, dupe, length);

                // This is introing the sort and showing the results
                printf("Batcher Sort, ");
                printf("%d elements, ", length);
                printf("%lu moves, ", stat.moves);
                printf("%lu compares", stat.compares);

                for (int i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, dupe[i]);
                }
                printf("\n");
                // resets everything
                for (int i = 0; i < length; i++) {
                    dupe[i] = arr[i];
                }
                reset(&stat);

                break;
            case INSERT:
                // This is where insert sort is ran
                insertion_sort(&stat, dupe, length);

                // This is introing the sort and showing the results
                printf("Insertion Sort, ");
                printf("%d elements, ", length);
                printf("%lu moves, ", stat.moves);
                printf("%lu compares", stat.compares);

                for (int i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, dupe[i]);
                }
                printf("\n");
                // resets everything
                for (int i = 0; i < length; i++) {
                    dupe[i] = arr[i];
                }
                reset(&stat);

                break;
            case QUICK:
                // This is where quick sort is ran
                quick_sort(&stat, dupe, length);

                // This is introing the sort and showing the results
                printf("Quick Sort, ");
                printf("%d elements, ", length);
                printf("%lu moves, ", stat.moves);
                printf("%lu compares", stat.compares);

                for (int i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, dupe[i]);
                }
                printf("\n");
                // resets everything
                for (int i = 0; i < length; i++) {
                    dupe[i] = arr[i];
                }
                reset(&stat);
                break;
            }
        }
    }

    // this is freeing all the memory space for no leaks
    free(dupe);
    free(arr);
    // the help commands for no inputs
    if (counter) {
        help();
        return 0;
    }
    return 0;
}
