
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for node.c
//

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// This function is the initializer of node, this creates a node object that we
// can use by calling this constructer
Node *node_create(uint8_t symbol, uint64_t frequency){
    Node *node = (Node *) malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->symbol = symbol;
    node->frequency = frequency;
    return node;
}

// This function deletes the dynamically allocated node
void node_delete(Node **n){
    free(*n);
    return;
}

// This functions joins the nodes together the parent nodes symbol will be '$'
// 0x24 represents $ in uint8_t
Node *node_join(Node *left, Node *right){
    Node *node = node_create(0x24, left->frequency+right->frequency);
    node->left = left;
    node->right = right;
    return node;
}

// This is a printing function for testing
// This count of the index needs to be outside because the function is recursive
uint64_t count = 0;
void node_print(Node *n){
    // This prints out the symbol and the frequency of the current node
    printf("symbol %c\n", n->symbol);
    printf("frequency %d\n", n->frequency);

    // this print the left and right node recursively until no more nodes
    if(n->right != NULL){
        printf("%d\n", count);
        node_print(n->right);
        count += 1;
    }
    if(n->left != NULL){
        printf("%d\n", count);
        node_print(n->left);
        count += 1;
    }
    return;
}
