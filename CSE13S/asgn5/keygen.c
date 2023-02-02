

// Theodore Ikehara
// CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// keygen.c
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>
#include <time.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "b:i:n:d:s:vh"

void help() {
    printf("SYNOPSIS\n");
    printf("   Generates an RSA public/private key pair.\n\n");
    printf("USAGE\n");
    printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -b bits         Minimum bits needed for public key n.\n");
    printf("   -c confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    printf("   -d pvfile       Private key file (default: rsa.priv).\n");
    printf("   -s seed         Random seed for testing.\n\n");
}

int main(int argc, char **argv) {

    // vars for running the program
    // printf("program start here\n");

    mpz_t s, p, q, n, e, d, user, temp;
    mpz_inits(s, p, q, n, e, d, user, temp, NULL);

    // defaults as given in the doc
    uint64_t min_bits = 256;
    uint64_t iters = 50;
    uint64_t seed = time(NULL);
    uint64_t priv = 0;

    FILE *pbfile = NULL;
    FILE *pvfile = NULL;

    // default names for the files
    char *pb = "rsa.pub";
    char *pv = "rsa.priv";
    char *username = getenv("USER");

    // these are for the getopt functions
    bool ver = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': min_bits = atoi(optarg); break;
        case 'i': iters = atoi(optarg); break;
        case 'n': pb = optarg; break;
        case 'd': pv = optarg; break;
        case 's': seed = atoi(optarg); break;
        case 'v': ver = true; break;
        case 'h':
            help();
            mpz_clears(s, p, q, n, e, d, user, temp, NULL);
            return 0;
            break;
        default:
            help();
            mpz_clears(s, p, q, n, e, d, user, temp, NULL);
            return 0;
            break;
        }
    }

    // initializing the random seed
    randstate_init(seed);

    // printf("Reached main part of program\n");

    // fopens to write pub and priv files
    pbfile = fopen(pb, "w");
    if (pbfile == NULL) {
        printf("error: could not write to rsa.pub.\n");
        mpz_clears(s, p, q, n, e, d, user, NULL);
        return 1;
    }

    pvfile = fopen(pv, "w");
    if (pvfile == NULL) {
        printf("error: could not write to rsa.priv.\n");
        mpz_clears(s, p, q, n, e, d, user, NULL);
        return 1;
    }

    // This is setting the file permissions to 0600 as in the doc
    priv = fileno(pvfile);
    fchmod(priv, 0600);

    // this is generating the private and public key pair
    rsa_make_pub(p, q, n, e, min_bits, iters);
    rsa_make_priv(d, e, p, q);
    // gmp_printf("d = %Zd\n", d);

    // signing the rsa with user name as in the doc with base 62
    mpz_set_str(user, username, 62);
    rsa_sign(s, user, d, n);
    // gmp_printf("d = %Zd\n", d);

    // write rsa public and private
    rsa_write_pub(n, e, s, username, pbfile);
    rsa_write_priv(n, d, pvfile);

    // prints out the size of bits and the value of the parts
    if (ver) {
        printf("user = %s\n", username);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    // garbage disposal
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(s, p, q, n, e, d, user, temp, NULL);

    return 0;
}
