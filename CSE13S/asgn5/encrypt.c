

// Theodore Ikehara
// CSE13s winter 2022
// Assignment 5 Public Key Cryptography
// encrypt.c
//

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:n:vh"

void help() {
    printf("SYNOPSIS\n");
    printf("   Encrypts data using RSA encryption.\n");
    printf("   Encrypted data is decrypted by the decrypt program.\n");
    printf("USAGE\n");
    printf("   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
    printf("   -o outfile      Outfile for encrypted data (default: stdout\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n\n");
}

int main(int argc, char **argv) {

    // vars for running the program
    FILE *input = stdin;
    FILE *output = stdout;
    FILE *pbfile = stdin;

    char username[256] = { 0 };
    char *pubfile = "rsa.pub";
    char *infile = NULL;
    char *outfile = NULL;

    // This is all for the getopt
    bool ver = false;
    bool in = false;
    bool out = false;
    //bool pb = false;

    mpz_t n, e, s, val;
    mpz_inits(n, e, s, val, NULL);

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
            pubfile = optarg;
            // pb = true;
            break;
        case 'v': ver = true; break;
        case 'h':
            help();
            mpz_clears(n, e, s, val, NULL);
            return 0;
            break;
        default:
            help();
            mpz_clears(n, e, s, val, NULL);
            return 0;
            break;
        }
    }

    // opens the public key file getting the input file if specified in getopt
    if (in) {
        input = fopen(infile, "r");
        if (input == NULL) {
            printf("error: could not open the public key to read.\n");
            mpz_clears(n, e, s, val, NULL);
            return 1;
        }
    }
    if (out) {
        output = fopen(outfile, "w");
        if (output == NULL) {
            printf("error: could not open the public key to write.\n");
            mpz_clears(n, e, s, val, NULL);
            return 1;
        }
    }

    pbfile = fopen(pubfile, "r");
    if (pbfile == NULL) {
        printf("error: could not open the public key file.\n");
        mpz_clears(n, e, s, val, NULL);
        return 1;
    }

    // END OPENING FILES

    // read the public key file
    rsa_read_pub(n, e, s, username, pbfile);

    if (ver) {
        printf("user = %s\n", username);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    // verify the rsa key
    rsa_verify(val, s, e, n);

    // This does the actuall encryption writes input to output
    rsa_encrypt_file(input, output, n, e);

    // closing and clearing all the trash that this program generated
    fclose(input);
    fclose(output);
    fclose(pbfile);
    mpz_clears(n, e, s, val, NULL);

    return 0;
}
