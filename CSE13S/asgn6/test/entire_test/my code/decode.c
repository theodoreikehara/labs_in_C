
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for decode.c
//
// source: Omar's section and asgn6 doc
// mostly follows the order and psudo code of the doc
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

void help() {
    printf("SYNOPSIS\n");
    printf("  A Huffman decoder.\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to decompress.\n");
    printf("  -o outfile     Output of decompressed data.\n");
}

int main(int argc, char **argv) {

    // These are the function variables
    // This is the in and out files we will be encoding too
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
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

    // read in the header from infile
    Header header;
    read_bytes(infile, (uint8_t *) &header, sizeof(Header));

    // part of step 1 check if the magic align
    if ((&header)->magic != MAGIC) {
        printf("MAGIC did not match!!\n");
        return 1;
    }

    // step 2 sets the permissions
    fchmod(outfile, (&header)->permissions);

    // step 3 use the tree_size to find the size of the dumped tree
    uint8_t dumped[(&header)->tree_size];
    // this reads in the bytes into the dumped tree
    read_bytes(infile, dumped, (&header)->tree_size);
    // this reconstructs the huffman tree using the rebuild tree
    Node *huff_tree = rebuild_tree((&header)->tree_size, dumped);

    // this needs to be debugged CHANGE!!!!
    uint8_t buffer;
    uint64_t decoded = 0;
    Node *temp = huff_tree;
    while (read_bit(infile, &buffer) && temp != NULL) {
        if (buffer == 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
        if (temp != NULL) {
            if (temp->right == NULL && temp->left == NULL) {
                write_bytes(outfile, &temp->symbol, 1);
                decoded += 1;
                temp = huff_tree;
            }
        }
        if (decoded == (&header)->file_size) {
            break;
        }
    }

    if (v) {
        printf("verbose active");
    }

    // closes and deletes everything
    delete_tree(&huff_tree);
    close(infile);
    close(outfile);
    return 0;
}
