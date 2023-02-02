
// Theodore Ikehara CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// rsa.c
//

#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <stdlib.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    // determines how many bits go into each of p and q
    uint64_t lower = nbits / 4;
    uint64_t upper = (3 * nbits) / 4;
    uint64_t p_ranbits = (rand() % (upper - lower + 1)) + lower;
    uint64_t q_ranbits = nbits - p_ranbits;

    // these vars are created to use for lambda
    mpz_t lambda, a, b, temp;
    mpz_inits(lambda, a, b, temp, NULL);

    // makes two random prime numbers of nbits length and with iters amount of
    // iterations
    make_prime(p, p_ranbits, iters);
    make_prime(q, q_ranbits, iters);
    // compute n
    mpz_mul(n, p, q); // n = p * q

    // for computing lambda using gcd
    mpz_sub_ui(a, p, 1); // a = p - 1
    mpz_sub_ui(b, q, 1); // b = q - 1
    mpz_mul(temp, a, b); // temp = a * b
    mpz_abs(temp, temp); // temp = |temp|
    gcd(a, a, b); // sets a to gcd of a,b
    mpz_fdiv_q(temp, temp, a);
    mpz_set(lambda, temp);

    // finds a suitable e
    while (true) {
        //make_prime(e, nbits, iters);
        mpz_urandomb(e, state, nbits);

        //gmp_printf("%Zd\n", e);
        gcd(temp, e, lambda);
        if (mpz_cmp_ui(temp, 1) == 0) {
            mpz_clears(lambda, a, b, temp, NULL);
            return;
        }
    }
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // writes n, e, s as hex
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
    return;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {

    // reads n, e, s as hex
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);

    return;
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    // these vars are created to use for lambda
    mpz_t lambda, a, b, temp;
    mpz_inits(lambda, a, b, temp, NULL);
    // for computing lambda using gcd
    mpz_sub_ui(a, p, 1); // a = p - 1
    mpz_sub_ui(b, q, 1); // b = q - 1
    mpz_mul(temp, a, b); // temp = a * b
    mpz_abs(temp, temp); // temp = |temp|
    gcd(a, a, b); // sets a to gcd of a,b
    mpz_fdiv_q(temp, temp, a);
    mpz_set(lambda, temp);
    // mpz_invert

    // gmp_printf("lambda = %Zd\n", lambda);
    // gmp_printf("e = %Zd\n", e);

    mod_inverse(d, e, lambda);

    mpz_clears(lambda, a, b, temp, NULL);
    return;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
    return;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
    return;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
    return;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t k, kmin1, temp, temp2;
    mpz_inits(k, kmin1, temp, temp2, NULL);

    // this is for reading the file
    uint64_t read = 0;

    // this is for determining the size of k
    size_t k_val = mpz_sizeinbase(n, 2) - 1;
    mpz_set_ui(k, k_val);
    mpz_fdiv_q_ui(k, k, 8);

    // allocates block size
    uint8_t *block = (uint8_t *) calloc(1, mpz_get_ui(k));

    // This is set to the first block
    block[0] = 0xFF;

    mpz_sub_ui(kmin1, k, 1);

    while (!feof(infile)) {

        // This is used to read the buffer size
        read = fread(block + 1, 1, mpz_get_ui(kmin1), infile);

        // imports data using the gmp lib
        mpz_import(temp, read + 1, 1, sizeof(block[0]), 1, 0, block);

        // encrypts the data by block
        rsa_encrypt(temp2, temp, e, n);

        // writes to the file
        gmp_fprintf(outfile, "%Zx\n", temp);
    }

    free(block);
    mpz_clears(k, kmin1, temp, temp2, NULL);
    return;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
    return;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t k, temp, temp2;
    mpz_inits(k, temp, temp2, NULL);

    // this is for reading the file
    uint64_t read = 0;

    // this is for determining the size of k
    size_t k_val = mpz_sizeinbase(n, 2) - 1;
    mpz_set_ui(k, k_val);
    mpz_fdiv_q_ui(k, k, 8);

    // allocates block size
    uint8_t *block = (uint8_t *) calloc(1, mpz_get_ui(k));

    block[0] = 0xFF;

    while (gmp_fscanf(infile, "%Zx\n", temp2) != EOF) {
        // decrypts the file
        rsa_decrypt(temp, temp2, d, n);
        // uses the export from the gmp library
        mpz_export(block, &read, 1, sizeof(block[0]), 1, 0, temp);
        // writes the block to the text
        fwrite(block + 1, 1, read - 1, outfile);
    }

    free(block);
    mpz_clears(k, temp, temp2, NULL);
    return;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
    return;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t auth;
    mpz_init(auth);

    pow_mod(auth, s, e, n);

    if (mpz_cmp(auth, m) == 0) {
        mpz_clear(auth);
        return true;
    } else {
        mpz_clear(auth);
        return false;
    }
}
