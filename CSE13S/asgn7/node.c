//
// Assignment 7: Author Identification
// Theodore Ikehara
//
// node.c
//

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creates nodes
Node *node_create(char *word) {

    // creates note
    Node *n = (Node *) malloc(sizeof(Node));

    if (n != NULL) {
        if (word != NULL) {
            n->word = strdup(word);
        }

        // increments count
        n->count = 1;
    }

    return n;
}

// deletes nodes
void node_delete(Node **n) {
    // checks if location exists
    if (*n != NULL) {
        // frees word that was allocated with strdup
        free((*n)->word);
        // frees the node
        free(*n);
    }
    return;
}

// prints nodes for debugging
void node_print(Node *n) {
    if (n != NULL) {
        printf("word: %s, count: %d\n", n->word, n->count);
    } else {
        printf("null\n");
    }
}
