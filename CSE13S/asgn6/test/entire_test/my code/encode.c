
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for encode.c
// source: Omar's Section and psudo code given by doc
// this encode.c follows the logic and order of the asgn doc
//
#include "io.h"
#include "code.h"
#include "huffman.h"
#include "node.h"
#include "defines.h"
#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// define the input options
#define OPTIONS "hi:o:v"

// This function prints out the sequence
void help() {
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Compresses a file using the Huffman coding algorithm.\n\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to compress.\n");
    printf("  -o outfile     Output of compressed data.\n");
}

int main(int argc, char **argv) {

    // These are the function variables
    // This is the in and out files we will be encoding too
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    // keeps track of the unique symbols
    int unique = 0;
    // for incrementing stuff
    int count = 0;
    // This is to enable verbose
    bool v = false;

    // This is in charge of the command line options
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(); return 0;
        case 'v': v = true; break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT); break;
        default: help(); return 0;
        }
    }
    // This detects if the file that it is reading is valid or not
    if (infile == -1) {
        printf("ERROR, cannot read file!");
        return 1;
    }

    // computing and building the histogram
    // This is where the histogram is stored
    uint64_t hist[ALPHABET] = { 0 };
    // the buffer is stored here
    uint8_t buffer;

    // This setys the bytes to the histogram
    // counts edge cases
    // this makes sure there is always atleast 2 elements
    hist[0] += 1;
    hist[ALPHABET - 1] += 1;
    while (read_bytes(infile, &buffer, 1) > 0) {
        hist[buffer] += 1;
    }
    // counts the unique symbols here
    while (count < ALPHABET) {
        if (hist[count] > 0) {
            unique += 1;
        }
        count += 1;
    }
    // creates the node with the histogram
    // and the codes
    Node *huff_tree = build_tree(hist);
    Code *huff_table = (Code *) malloc(ALPHABET * sizeof(Code));

    // actually builds here
    build_codes(huff_tree, huff_table);

    // opbtain data about permissions and size
    // and set to header
    // creates stat to use fstat
    struct stat stat;
    fstat(infile, &stat);
    uint16_t perm = stat.st_mode;
    uint64_t file_si = stat.st_size;
    // creates the header
    // step 6
    Header header = { 0 };
    // using fstat to find these values with the formula that is given in the
    // doc
    (&header)->magic = MAGIC;
    (&header)->permissions = perm;
    (&header)->file_size = file_si;
    (&header)->tree_size = (3 * unique) - 1;
    // writes the header to out file
    write_bytes(outfile, (uint8_t *) &header, sizeof(Header));

    // part of step 5 in psudo code to use fchmod
    fchmod(outfile, perm);
    // perform tree dump
    // step 7
    dump_tree(outfile, huff_tree);

    // step 8 write the codes
    // reads from buffer by 1 byte
    while (read_bytes(infile, &buffer, 1) > 0) {
        // write the code with the huff table until finished with the infile
        write_code(outfile, &huff_table[buffer]);
    }
    // part 2 of step 8 we need to flush the code
    flush_codes(outfile);

    if (v) {

        printf("verbose out here");
    }

    // closing and freeing all the files
    close(outfile);
    close(infile);
    // delete_tree(&huff_tree);
    free(huff_table);
    return 0;
}
