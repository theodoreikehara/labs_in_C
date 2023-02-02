
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for pq.c
// source: Eugene's sections

#include "pq.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t maxcap;
    Node **nodes;
} PriorityQueue;

uint32_t next(uint32_t pos, uint32_t capacity) {
    return ((pos + 1) % capacity);
}

uint32_t prev(uint32_t pos, uint32_t capacity) {
    return ((pos + capacity - 1) % capacity);
}

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->head = 0;
        pq->tail = 0;
        pq->size = 0;
        pq->maxcap = capacity;
        pq->nodes = (Node **) calloc(capacity, sizeof(Node));
        if (!pq->nodes) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->nodes) {
        free((*q)->nodes);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    return (q->size == 0);
}

bool pq_full(PriorityQueue *q) {
    return ((q->size) == (q->maxcap));
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// // this enqueues the node and gets sorted to correct posision
// bool enqueue(PriorityQueue *q, Node *n) {
//     // checks if the queue is full before proceding
//     if (pq_full(q)) {
//         return false;
//     }
//
//     // Whenever we input something to the queue the pointer to the top needs to
//     // be incremented
//     // places the n node to the top of the queue
//     q->nodes[0] = n;
//     q->head += 1;
//
//     // This uses the insertion sort algorithm
//     for (int i = 1; i <= (int) q->head - 1; i += 1) {
//         for (int j = i; j > 0; j -= 1) {
//             if (q->nodes[j - 1] > q->nodes[j]) {
//                 // This swaps the two nodes and puts in order
//                 Node *temp = q->nodes[j];
//                 q->nodes[j] = q->nodes[j - 1];
//                 q->nodes[j - 1] = temp;
//             }
//         }
//     }
//
//     return true;
// }

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }

    uint32_t slot = q->tail;
    // while (prev(slot) node freq > slot node freq) && (slot != head)
    while ((slot != q->head) && (q->nodes[prev(slot, q->maxcap)]->frequency > n->frequency)) {
        q->nodes[slot] = q->nodes[prev(slot, q->maxcap)]; // slot node = prev(slot) node
        slot -= 1;
    }
    q->nodes[slot] = n;
    q->size += 1;
    q->tail = next(q->tail, q->maxcap);

    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }

    *n = q->nodes[q->head];
    q->head = next(q->head, q->maxcap);
    q->size -= 1;
    return true;
}

// // struct definition
// // this is the definition of the pq ADT
// typedef struct PriorityQueue {
//     // this is the node for the that will be going into the queue
//     Node **inside;
//
//     // this is the capacity of the queue
//     uint32_t capacity;
//
//     // this keeps track of the head and and keeps track of where the end of the
//     // queue is
//     uint32_t head;
//
//     // TEST vars
//     uint32_t tail;
//     Node **nodes;
//     uint32_t size;
// } PriorityQueue;
//
// /// TEST
// uint32_t next(uint32_t pos, uint32_t capacity) {
//     return ((pos + 1) % capacity);
// }
//
// uint32_t prev(uint32_t pos, uint32_t capacity) {
//     return ((pos + capacity - 1) % capacity);
// }
// // END TEST
//
// // This creates a priority queue, constructor function for pq
// PriorityQueue *pq_create(uint32_t capacity) {
//     // This allocates the space for the pq and node that will be used as this is
//     // a pq of nodes
//     //
//     // all the zeros just to initialize
//     PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
//
//     // allocating space for the queue for nodes with size capacity
//     q->inside = malloc(capacity * sizeof(Node *));
//
//     // assignes default values to the vars
//     // this value is the parameter that was passed into the create function
//     q->capacity = capacity;
//     // this is all assigning to empty pq
//     q->head = 0;
//
//     // TEST vars
//     q->tail = 0;
//     q->nodes = (Node **) calloc(capacity, sizeof(Node));
//     q->size = 0;
//
//     return q;
// }
//
// // this deletes the pq deallocates and frees the memory
// void pq_delete(PriorityQueue **q) {
//     free((*q)->inside);
//     free(*q);
// }
//
// // this checks to see if the queue is empty
// bool pq_empty(PriorityQueue *q) {
//     if (!(q->head)) {
//         return true;
//     }
//     return false;
// }
//
// // this checks to see if the queue reached its capacity
// bool pq_full(PriorityQueue *q) {
//     if (q->capacity == q->head) {
//         return true;
//     }
//     return false;
// }
//
// // returns the size of the queue
// uint32_t pq_size(PriorityQueue *q) {
//     return q->head;
// }
//
// // TEST
// bool enqueue(PriorityQueue *q, Node *n) {
//     if (pq_full(q)) {
//         return false;
//     }
//
//     uint32_t slot = q->tail;
//     // while (prev(slot) node freq > slot node freq) && (slot != head)
//     while ((slot != q->head) && (q->nodes[prev(slot, q->capacity)]->frequency > n->frequency)) {
//         q->nodes[slot] = q->nodes[prev(slot, q->capacity)];
//         // slot node = prev(slot) node
//         slot -= 1;
//     }
//     q->nodes[slot] = n;
//     q->size += 1;
//     q->tail = next(q->tail, q->capacity);
//
//     return true;
// }
// bool dequeue(PriorityQueue *q, Node **n) {
//     if (pq_empty(q)) {
//         return false;
//     }
//
//     *n = q->nodes[q->head];
//     q->head = next(q->head, q->capacity);
//     q->size -= 1;
//     return true;
// }
// END TEST

// // this enqueues the node and gets sorted to correct posision
// bool enqueue(PriorityQueue *q, Node *n) {
//     // checks if the queue is full before proceding
//     if (pq_full(q)) {
//         return false;
//     }
//
//     // Whenever we input something to the queue the pointer to the top needs to
//     // be incremented
//     // places the n node to the top of the queue
//     q->inside[0] = n;
//     q->head += 1;
//
//     // This uses the insertion sort algorithm
//     for (int i = 1; i <= (int) q->head - 1; i += 1) {
//         for (int j = i; j > 0; j -= 1) {
//             if (q->inside[j - 1] > q->inside[j]) {
//                 // This swaps the two nodes and puts in order
//                 Node *temp = q->inside[j];
//                 q->inside[j] = q->inside[j - 1];
//                 q->inside[j - 1] = temp;
//             }
//         }
//     }
//
//     return true;
// }

// // this function dequeues the nodes and loads into n
// bool dequeue(PriorityQueue *q, Node **n) {
//     // checks if the queue is empty before proceding
//     if (pq_empty(q)) {
//         return false;
//     }
//
//     // loads top head is pointing to this top node to n
//     *n = q->inside[q->head];
//     // updates the size and top pointer
//     q->head -= 1;
//     return true;
// }

// // This is a printing function for debugging
// void pq_print(PriorityQueue *q) {
//     for (int i = (int) (q->capacity - q->head); i < (int) (q->capacity); i += 1) {
//         if (q->inside[i] != NULL) {
//             node_print(q->inside[i]);
//         }
//     }
//     return;
// }
