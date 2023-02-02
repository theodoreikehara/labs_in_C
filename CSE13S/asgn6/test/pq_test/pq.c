
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for pq.c
// source: Eugene's sections

#include "pq.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// struct definition
// this is the definition of the pq ADT
struct PriorityQueue {
    // this is the node for the that will be going into the queue
    Node **inside;

    // this is the capacity of the queue
    uint32_t capacity;

    // this keeps track of the head and and keeps track of where the end of the
    // queue is
    uint32_t head;
};

// This creates a priority queue, constructor function for pq
PriorityQueue *pq_create(uint32_t capacity) {
    // This allocates the space for the pq and node that will be used as this is
    // a pq of nodes
    //
    // all the zeros just to initialize
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    Node *node = node_create(0, 0);

    // allocating space for the queue for nodes with size capacity
    q->inside = malloc(capacity * sizeof(Node *));

    // assignes default values to the vars
    // this value is the parameter that was passed into the create function
    q->capacity = capacity;
    // this is all assigning to empty pq
    q->head = 0;

    return q;
}

// this deletes the pq deallocates and frees the memory
void pq_delete(PriorityQueue **q) {
    free((*q)->inside);
    free(*q);
}

// this checks to see if the queue is empty
bool pq_empty(PriorityQueue *q) {
    if (!(q->head)) {
        return true;
    }
    return false;
}

// this checks to see if the queue reached its capacity
bool pq_full(PriorityQueue *q) {
    if (q->capacity == q->head) {
        return true;
    }
    return false;
}

// returns the size of the queue
uint32_t pq_size(PriorityQueue *q) {
    return q->head;
}

// this enqueues the node and gets sorted to correct posision
bool enqueue(PriorityQueue *q, Node *n) {
    // checks if the queue is full before proceding
    if (pq_full(q)) {
        return false;
    }

    // Whenever we input something to the queue the pointer to the top needs to
    // be incremented
    // places the n node to the top of the queue
    q->inside[0] = n;
    q->head += 1;

    // the total is the capacity of the pq and this needs to change as the
    uint32_t total = q->capacity;

    // This uses the insertion sort algorithm
    for (int i = 1; i <= q->head - 1; i += 1) {
        for (int j = i; j > 0; j -= 1) {
            if (q->inside[j - 1] > q->inside[j]) {
                // This swaps the two nodes and puts in order
                Node *temp = q->inside[j];
                q->inside[j] = q->inside[j - 1];
                q->inside[j - 1] = temp;
            }
        }
    }

    return true;
}

// this function dequeues the nodes and loads into n
bool dequeue(PriorityQueue *q, Node **n) {
    // checks if the queue is empty before proceding
    if (pq_empty(q)) {
        return false;
    }

    // loads top head is pointing to this top node to n
    *n = q->inside[q->head];
    // updates the size and top pointer
    q->head -= 1;
    return true;
}

// This is a printing function for debugging
void pq_print(PriorityQueue *q) {
    for (int i = (int) (q->capacity - q->head); i < (int) (q->capacity); i += 1) {
        if (q->inside[i] != NULL) {
            node_print(q->inside[i]);
        }
    }
    return;
}
