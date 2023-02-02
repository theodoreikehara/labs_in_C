

// Theodore Ikehara
// CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// decrypt.c
//

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:n:vh"

void help() {
    printf("SYNOPSIS\n");
    printf("   Decrypts data using RSA decryption.\n");
    printf("   Encrypted data is encrypted by the encrypt program.\n\n");
    printf("USAGE\n");
    printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
    printf("   -o outfile      Outfile file decrypted data (default: stdout\n");
    printf("   -n pbfile       Private key file (default: rsa.priv).\n\n");
}

int main(int argc, char **argv) {

    // vars for running the program
    //
    mpz_t n, e;
    mpz_inits(n, e, NULL);

    FILE *input = stdin;
    FILE *output = stdout;
    FILE *pbfile = stdin;

    char *infile = NULL;
    char *outfile = NULL;
    char *privfile = "rsa.priv";

    bool ver = false;
    bool in = false;
    bool out = false;
    // bool pv = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = optarg;
            in = true;
            break;
        case 'o':
            outfile = optarg;
            out = true;
            break;
        case 'n':
            privfile = optarg;
            //pv = true;
            break;
        case 'v': ver = true; break;
        case 'h':
            help();
            mpz_clears(n, e, NULL);
            return 0;
            break;
        default:
            help();
            mpz_clears(n, e, NULL);
            return 0;
            break;
        }
    }

    // opens the public key file getting the input file if specified in getopt
    if (in) {
        input = fopen(infile, "r");
        if (input == NULL) {
            printf("error: could not open the private key to read.\n");
            mpz_clears(n, e, NULL);
            return 1;
        }
    }
    if (out) {
        output = fopen(outfile, "w");
        if (output == NULL) {
            printf("error: could not open the private key to write.\n");
            mpz_clears(n, e, NULL);
            return 1;
        }
    }

    pbfile = fopen(privfile, "r");
    if (pbfile == NULL) {
        printf("error: could not open the private key file.\n");
        mpz_clears(n, e, NULL);
        return 1;
    }

    // END OPENING FILES

    // read the private key
    rsa_read_priv(n, e, pbfile);

    // only activates if verbose is enabled
    if (ver) {
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    // this does the actual decrypting
    rsa_decrypt_file(input, output, n, e);

    // trash cleanup
    fclose(input);
    fclose(output);
    fclose(pbfile);
    mpz_clears(n, e, NULL);

    return 0;
}
