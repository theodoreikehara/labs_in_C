

// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for code.c
//

#include "defines.h"
#include "code.h"

#include <stdio.h>
#include <stdlib.h>

// This function initializes the code for the code table
Code code_init(void) {
    // creates a code var
    Code code;

    // sets the top to zero similar to a stack
    code.top = 0;

    // inits the code sets all default to 0
    for (int i = 0; i < (int) MAX_CODE_SIZE; i += 1) {
        code.bits[i] = 0;
    }

    // returns the code here
    return code;
}

// checks the size of code
uint32_t code_size(Code *c) {
    // top keeps track of the size of the code
    return c->top;
}

// checks to see if the code is empty
bool code_empty(Code *c) {
    // 0 = false so if not zero than not empty
    if (c->top) {
        return false;
    }
    return true;
}

// checks to see if the code is empty
bool code_full(Code *c) {
    // if top is equal to max code than it is full
    if (c->top == MAX_CODE_SIZE) {
        return true;
    }
    return false;
}

// This takes an index i and sets the bit to 1
bool code_set_bit(Code *c, uint32_t i) {
    // this checks to see if the bits are empty first
    if (code_empty(c)) {
        return false;
    }
    // this checks if the position exists
    if (c->bits[i]) {
        c->bits[i] = 0;
        return true;
    }
    return false;
}

// This takes an index i and sets to 0
bool code_clr_bit(Code *c, uint32_t i) {
    // this checks to see if the bits is empty first
    if (code_empty(c)) {
        return false;
    }
    // this checks if the position exists
    if (c->bits[i]) {
        c->bits[i] = 0;
        return true;
    }
    return false;
}

bool code_get_bit(Code *c, uint32_t i) {
    // this checks to see if the bits is empty first
    if (code_empty(c)) {
        return false;
    }
    // this checks if the position exists
    if (c->bits[i] == 1) {
        return true;
    }
    return false;
}

// pushes the bit into the code
bool code_push_bit(Code *c, uint8_t bit) {
    // checks if code is full before proceding
    if (code_full(c)) {
        false;
    }
    // inserts bit at top of code
    c->bits[c->top] = bit;
    // need to increse the top
    c->top += 1;
    // if success return true
    return true;
}

// code pops bit out of the codes
bool code_pop_bit(Code *c, uint8_t *bit) {
    // checks if the code is empty
    if (code_empty(c)) {
        return false;
    }
    // decriments top to get the posision that we need to pop
    c->top -= 1;
    // pops bit here
    *bit = (c->bits[c->top]);
    // returns true when success
    return true;
}
