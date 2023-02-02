

// Theodore Ikehara
// CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// numtheory.c
//
//

// #include "randstate.h"
#include "numtheory.h"
#include "randstate.h"

// declaring this global var
gmp_randstate_t state;

// finds the greatest common denomentor
void gcd(mpz_t d, mpz_t a, mpz_t b) {

    // setting temp mpz for swapping
    mpz_t temp, tempa, tempb;
    mpz_inits(temp, tempa, tempb, NULL); // temp = NULL

    mpz_set(tempa, a);
    mpz_set(tempb, b);

    while (mpz_cmp_ui(tempb, 0) != 0) { // b != 0
        mpz_set(temp, tempb); // temp = b
        mpz_mod(tempb, tempa, tempb); // b = a % b
        mpz_set(tempa, temp); // a = temp
    }

    mpz_set(d, tempa); // d = a return d

    // clears the mpz vars
    mpz_clears(temp, tempa, tempb, NULL);
}

// Does modular multiplicative inverse
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

    mpz_t temp, temp2, r, r_prime, t, t_prime, q;
    mpz_inits(temp, temp2, r, r_prime, t, t_prime, q, NULL); // declaring and initialzing mpz

    // seting the values
    mpz_set(r, n);
    mpz_set(r_prime, a);
    // t = 0
    mpz_set_ui(t_prime, 1);

    while (mpz_cmp_ui(r_prime, 0) != 0) {
        // floor division q = r // r_prime
        mpz_fdiv_q(q, r, r_prime);

        mpz_set(temp, r_prime); // temp = r_prime

        mpz_mul(temp2, q, r_prime); // r_prime = r - q * r_prime
        mpz_sub(r_prime, r, temp2); // needs second temp to keep integrady of the order
        mpz_set(r, temp); // r = temp

        mpz_set(temp, t_prime); // temp = t_prime
        mpz_mul(temp2, q, t_prime); // t_prime = t - q * t_prime
        mpz_sub(t_prime, t, temp2); // needs second temp to keep integrady of the order
        mpz_set(t, temp); // t = temp

        // gmp_printf("%Zd\n", r_prime);
    }

    // sets mpz_t i depending on conditions
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(i, 0);
        mpz_clears(temp, temp2, r, r_prime, t, t_prime, q, NULL);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    mpz_set(i, t);

    // clears th mpz vars
    mpz_clears(temp, temp2, r, r_prime, t, t_prime, q, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    // sets mpz vars
    mpz_t v, p, val, extemp;
    mpz_inits(v, p, val, extemp, NULL);

    mpz_set_ui(v, 1);
    mpz_set(p, base);
    mpz_set(extemp, exponent);

    // compares d > 0
    while (mpz_cmp_ui(extemp, 0) > 0) {

        // if d%2 != 0
        // WARNING MIGHT CAUSE A BUG HERE !!!
        mpz_mod_ui(val, extemp, 2);
        if (mpz_cmp_ui(val, 0) != 0) {

            mpz_mul(v, v, p); // v = v*p
            mpz_mod(v, v, modulus); // v = v%n
        }

        mpz_mul(p, p, p); // p = p*p
        mpz_mod(p, p, modulus); // p = p%n

        mpz_fdiv_q_ui(extemp, extemp, 2);
    }

    mpz_set(out, v); // out = v
    // clears all the var
    mpz_clears(v, p, val, extemp, NULL);
}

// the witness part of the is prime function is abstracted out
bool witness(mpz_t a, mpz_t n) {

    mpz_t u, t, x, y, val, con;
    mpz_inits(u, t, x, y, val, con, NULL);
    mpz_sub_ui(n, n, 1);
    mpz_set(u, n); // int u = n-1
    mpz_set_ui(t, 0); // int t = 0

    // setting a constant
    mpz_set_ui(con, 2);

    // MIGHT CAUSE A BUG
    // while u%2 == 0
    mpz_mod_ui(val, u, 2);

    while (mpz_cmp_ui(val, 0) == 0) {

        mpz_add_ui(t, t, 1); // t+=1
        mpz_fdiv_q_ui(u, u, 2); // u /= 2

        mpz_set(val, u);
        mpz_mod_ui(val, u, 2);
    }

    pow_mod(x, a, u, n); // pow_mod and equate to val
    for (int i = 0; 0 > mpz_cmp_ui(t, i); i += 1) {
        pow_mod(y, x, con, n); // powmod equating to y
        mpz_sub_ui(val, n, 1); // computes n - 1 and sets to val
        if (mpz_cmp_ui(y, 1) == 0 && mpz_cmp_ui(x, 1) != 0 && mpz_cmp(x, val) != 0) {
            mpz_clears(u, t, x, y, val, con, NULL);
            return true;
        }
        mpz_set(x, y); // x = y
    }
    mpz_clears(u, t, x, y, val, con, NULL);
    return mpz_cmp_ui(x, 1) != 0; // return x != 1
}

bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t a, val;
    mpz_inits(a, val, NULL);
    bool lo = true;
    // val = n % 2
    mpz_mod_ui(val, n, 2);
    // (n < 2) || (n != 2 && n % 2 == 0)
    if ((mpz_cmp_ui(n, 2) < 0) || (mpz_cmp_ui(n, 2) != 0 && mpz_cmp_ui(val, 0) == 0)) {
        mpz_clears(a, val, NULL);
        return false;
    }

    if (mpz_cmp_ui(n, 4) < 0) {
        mpz_clears(a, val, NULL);
        return true;
    }

    for (uint64_t i = 0; i < iters; i += 1) {

        while (lo) {
            mpz_urandomm(a, state, n); // Rand range(0, n-1)
            if (mpz_cmp_ui(a, 2) >= 0) {
                lo = false;
            }
        }

        if (witness(a, n)) {

            mpz_clears(a, val, NULL);
            return true;
        }
    }
    mpz_clears(a, val, NULL);
    return false;
}

// // power function to help find the min value of the prime number
// uint64_t power(uint64_t base, uint64_t exp) {
//
//     uint64_t answer = 1;
//     for (uint64_t i = 0; i < exp; i += 1) {
//         answer = answer * base;
//     }
//     return answer;
// }

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    // uint64_t min = power(2, bits);
    // builds the minbits using power
    mpz_t minbits;
    mpz_init(minbits);
    mpz_set_ui(minbits, 2);
    mpz_pow_ui(minbits, minbits, bits);

    while (true) {
        mpz_urandomb(p, state, bits);
        mpz_add(p, p, minbits);
        if (is_prime(p, iters)) {
            mpz_clear(minbits);
            return;
        }
    }
}
