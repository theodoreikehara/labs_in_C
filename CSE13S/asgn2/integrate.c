

// Theodore Ikehara
// CSE13s Assignment 2 Numerical Lab
// integrate.c includes the main function and testing functions

#include "functions.h"
#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "abcdefghijn:p:q:H"

int main(int argc, char **argv) {

    // These are for the integration function
    double lower;
    double upper;
    double n = 100;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'a': integrate(a, lower, upper, n); break;
        case 'b': integrate(b, lower, upper, n); break;
        case 'c': integrate(c, lower, upper, n); break;
        case 'd': integrate(d, lower, upper, n); break;
        case 'e': integrate(e, lower, upper, n); break;
        case 'f': integrate(f, lower, upper, n); break;
        case 'g': integrate(g, lower, upper, n); break;
        case 'h': integrate(h, lower, upper, n); break;
        case 'i': integrate(i, lower, upper, n); break;
        case 'j': integrate(j, lower, upper, n); break;
        case 'n': n = atoi(optarg); break;
        case 'p': lower = atoi(optarg); break;
        case 'q': upper = atoi(optarg); break;
        case 'H':
            printf("-a:     Sets the function to a\n");
            printf("-b:     Sets the function to b\n");
            printf("-c:     Sets the function to c\n");
            printf("-d:     Sets the function to d\n");
            printf("-e:     Sets the function to e\n");
            printf("-f:     Sets the function to f\n");
            printf("-g:     Sets the function to g\n");
            printf("-h:     Sets the function to h\n");
            printf("-i:     Sets the function to i\n");
            printf("-j:     Sets the function to j\n");
            printf("-n:     Sets the partition\n");
            printf("-p:     Sets the lower end of the integral\n");
            printf("-q:     Sets the upper end of the integral\n");
            printf("-H:     For Help!\n");
            break;
        }
    }

    return 0;
}
