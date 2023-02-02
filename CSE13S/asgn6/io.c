
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for io.c
//

#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

// This is the static buffer of bytes with size block used in read bit and write
// code
static uint8_t buffer[BLOCK];
// this is the index of buffer
static int index;
// this will be used in the read_bit
static int last;

// extern vars in header file
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

// This function is used to read the bytes given a file
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    // These are vars that keeps the total and the bytes that are read
    int bytes = 0;
    int total = 0;

    // this loops through all the bytes until end and totals the bytes
    while (total != nbytes || 0 < bytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
        if (bytes == 0) {
            break;
        }
    }

    // This returns the total and count into the global vars
    bytes_read += total;
    return total;
}

// This function will be used to write the bytes to an outfile very similar to
// the read_bytes
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    // These are vars that keeps the total and the bytes that will be written
    int bytes = 0;
    int total = 0;

    // this loops through all the bytes until end and totals the bytes
    while (total != nbytes || 0 < bytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }

    // This returns the total and count to global var
    bytes_written += total;
    return total;
}

// This function reads the bits
// psudo code from Eugene's section
bool read_bit(int infile, uint8_t *bit) {

    // This calculates the current bit
    uint8_t size = 0;
    // This counts the total bits read
    int total_bits = 0;

    // This accounts for when the buffer is indexed at 0
    if (index == 0) {
        total_bits = read_bytes(infile, buffer, BLOCK);
        if (total_bits < BLOCK) {
            last = total_bits * 8 + 1;
        }
    }

    // finds the size of the bit to read
    size = ((1 << (index % 8)) & buffer[index / 8]);
    *bit = (size >> (index % 8));

    // increments index
    index += 1;

    // This will set the index to 0 because was not valid index size
    if (index == 8 * BLOCK) {
        index = 0;
    }

    // this is incase not success
    if (index == last) {
        if (last != 0) {
            return false;
        }
    }

    // this is incase of success
    return true;
}

// This section writes the code
// using psudo code from Eugene's section
void write_code(int outfile, Code *c) {

    // this iterates the loop
    uint32_t count = 0;
    // This is the bit shift computation
    uint8_t bit_shift = 1 << (index % 8);

    // loops through the code bits
    while (count < code_size(c)) {

        // this clears the bit
        if ((c->bits[count] >> (count % 8) & 1) != 1) {
            buffer[index / 8] &= bit_shift;
            // This sets the bit
        } else {
            buffer[index / 8] |= ~bit_shift;
        }

        // if the block is valid write the block to outfile
        if (index == 8 * BLOCK) {
            write_bytes(outfile, buffer, BLOCK);
            index = 0;
        }
        count += 1;
    }

    return;
}

// This flushes all the code
// psudo code from Eugene's section
void flush_codes(int outfile) {

    // if the index is not on zero
    if (index > 0) {

        uint32_t bytes;
        if (index % 8 == 0) {
            bytes = index / 8 + 1;
        } else {
            bytes = index / 8 + 1;
            for (uint32_t i = index; i < bytes * 8; i += 1) {
                buffer[i / 8] &= ~(1 << (i % 8));
            }
        }

        write_bytes(outfile, buffer, bytes);
        // flush the code here
        index = 0;
    }

    return;
}
