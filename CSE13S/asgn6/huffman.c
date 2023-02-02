
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for huffman.c
//
// source: Omar's section and psudo code

#include "huffman.h"
#include "node.h"
#include "stack.h"
#include "defines.h"
#include "io.h"
#include "pq.h"

#include <stdio.h>

// builds the tree and returns a root node
Node *build_tree(uint64_t hist[static ALPHABET]) {
    // creates a priority queue to store the stuff given by the histo gram
    PriorityQueue *pq = pq_create(ALPHABET);

    // nodes for computation
    Node *left;
    Node *right;
    Node *root;

    // This iterates through the entire ALPHABET and checks to see if the chars
    // are represented in the histogram
    for (int i = 0; i < (int) ALPHABET; i += 1) {
        // adds to queue only if it exists
        if (hist[i] != 0) {
            enqueue(pq, node_create(i, hist[i]));
        }
    }

    while (1 < pq_size(pq)) {
        // joining the node and building the tree
        dequeue(pq, &left);
        dequeue(pq, &right);
        enqueue(pq, node_join(left, right));
    }

    // getting the root node from the queue
    dequeue(pq, &root);
    pq_delete(&pq);
    return root;
}

// psudo code from Omar's section
void build_codes(Node *root, Code table[static ALPHABET]) {
    // needs a state code to build to
    static Code c = { 0, { 0 } };
    uint8_t temp = 0;

    // if the node does not exist don't do anything
    if (root == NULL) {
        return;
        // if this is a leaf node
    } else if (root->right == NULL && root->left == NULL) {
        // breaks from the recursion
        table[root->symbol] = c;
        return;
    } else {
        // recursive call and change root
        code_push_bit(&c, 0);
        build_codes(root->left, table);
        code_pop_bit(&c, &temp);
        code_push_bit(&c, 1);
        build_codes(root->right, table);
        code_pop_bit(&c, &temp);
        return;
    }
}

// This was from psudo code from Omar's section
// This is to keep track of the amount of bytes dumped
int bytes_dumped = 0;
uint8_t buffer[60];
// This dumps the tree and with post-traversal
void dump_tree(int outfile, Node *root) {
    // checks witch node is available
    // if the nodes exist
    if (root->left != NULL) {
        dump_tree(outfile, root->left);
    }
    if (root->right != NULL) {
        dump_tree(outfile, root->right);
    }

    // this is the leaf node
    if (root->left == NULL && root->right == NULL) {
        buffer[bytes_dumped] = 'L';
        // this accounts for the next index for the symbol
        bytes_dumped += 1;
        buffer[bytes_dumped] = root->symbol;

        // this is the final bytes for this root that will be written
        bytes_dumped += 1;
        write_bytes(outfile, buffer, bytes_dumped);
        return;
    } else {
        // this is if not leaf
        buffer[bytes_dumped] = 'I';
        bytes_dumped += 1;
        write_bytes(outfile, buffer, bytes_dumped);
        return;
    }
}

// rebuilds the tree gives a post order tree dump
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

    // createing stack to store the nodes
    Stack *s = stack_create(nbytes);
    Node *final;
    Node *n;
    Node *left;
    Node *right;
    Node *join;

    int bit_index = 0;

    // iterates through nbytes
    while (bit_index < nbytes) {
        // tree for unique symbol
        if (tree[bit_index] == 'L') {
            // this creates the node for the unique symbol
            n = node_create(tree[bit_index + 1], 1);
            stack_push(s, n);

            // not unique so need to join the nodes
        } else if (tree[bit_index] == 'I') {
            // getting the left and right node from the stack
            stack_pop(s, &right);
            stack_pop(s, &left);
            // this is the joined node
            join = node_join(left, right);
            // push the joined node to the stack
            stack_push(s, join);
        }
    }
    // gets the final push and pops than returns
    stack_pop(s, &final);
    return final;
}

void delete_tree(Node **root) {
    // needs post order traversal to delete
    //
    if ((*root)->left == NULL && (*root)->right == NULL) {
        node_delete(root);
    } else {
        delete_tree(&((*root)->right));
        delete_tree(&((*root)->left));
        node_delete(root);
    }
    return;
}
