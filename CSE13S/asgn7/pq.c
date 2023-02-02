//
// Assignment 7: Author Identification
// Theodore Ikehara
// pq.c
//
// Priority Queue

#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// start of the nodepq struct
// my ADT to account for the dist and auth
struct NodePQ {
    char *author;
    double dist;
};

struct NodePQ *nodepq_create(char *auth, double dist) {

    // createing a node for the PriorityQueue
    struct NodePQ *npq = (struct NodePQ *) malloc(sizeof(struct NodePQ));

    if (npq != NULL) {
        // sets the author
        if (auth != NULL) {
            npq->author = strdup(auth);
        }
        // sets the dist
        npq->dist = dist;
    }
    return npq;
}

// deletes the nodepq
void nodepq_delete(struct NodePQ **n) {
    // checks if this location exists
    if (*n != NULL) {
        // frees word that was allocated with strdup
        free((*n)->author);
        // frees the nodepq
        free(*n);
    }
    return;
}

void nodepq_print(struct NodePQ *n) {
    if (n != NULL) {
        printf("word: %s, dist: %f\n", n->author, n->dist);
    } else {
        printf("null\n");
    }
}
// end of the node pq struct

// start of the pq struct --------------
struct PriorityQueue {
    uint32_t top;
    uint32_t cap;
    struct NodePQ **auth;
};

PriorityQueue *pq_create(uint32_t capacity) {
    // creating the pq
    PriorityQueue *pq = (PriorityQueue *) calloc(1, sizeof(PriorityQueue));

    if (pq != NULL) {
        // setting all the values
        pq->top = 0;
        pq->cap = capacity;
        pq->auth = calloc(capacity, sizeof(struct NodePQ *));

        // loads in the items so no segfault
        char *a = "";
        double d = 0.0;
        for (int i = 0; i < (int) capacity; i += 1) {
            pq->auth[i] = nodepq_create(a, d);
        }
        // nodepq_delete(&n);
        return pq;
    }
    return NULL;
}

void pq_delete(PriorityQueue **q) {
    if (*q != NULL) {
        // deletes all the nodes
        // printf("cap = %d\n", (*q)->cap);
        // nodepq_print((*q)->auth[8]);
        for (int i = 0; i < (int) (*q)->cap; i += 1) {
            // printf("looping...%d\n", i);
            nodepq_delete(&(*q)->auth[i]);
            // (*q)->auth[i] = NULL;
        }
        free((*q)->auth);
        free(*q);
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->top == q->cap) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    // return q->top;
    return q->cap;
}

// void swap_temp(char *str1, char *str2) {
//     char *temp = str1;
//     str1 = str2;
//     str2 = temp;
// }

bool enqueue(PriorityQueue *q, char *author, double dist) {
    // this checks if the pq is full first
    if (pq_full(q)) {
        return false;
    }
    // this puts in the node to the pq

    // nodepq_print(q->auth[0]);
    // q->auth[0]->author = author;

    // This portion is giving me valgrind errors....

    if (author == NULL || q->auth[0] == NULL) {
        printf("NULL detected\n");
        return false;
    }

    // swap_temp(q->auth[0]->author, author);
    // printf("%s\n", q->auth[0]->author);
    strcpy(q->auth[0]->author, author);

    // q->auth[0]->author = author;

    q->auth[0]->dist = dist;
    // nodepq_print(*q->auth);
    // printf("starting node: %s.\n", q->auth[0]->author);

    // q->auth[0] = nodepq_create(author, dist);
    // q->auth[1]->dist = 2.0;
    q->top += 1;
    // printf("this is after set\n");
    // nodepq_print(q->auth[0]);
    // nodepq_print(q->auth[1]);
    // sorting with insertion sort
    int count = q->cap;
    bool swap = true;
    // sorting nested loop
    while (swap) {
        swap = false;
        for (int i = 1; i < count; i += 1) {
            // checking if previous index is greater than itself

            // printf("[i - 1]: %f > [i]: %f\n", q->auth[i - 1]->dist, q->auth[i]->dist);
            if ((q->auth[i - 1]->dist) > (q->auth[i]->dist)) {
                // swaps here
                //
                // printf("sorting...\n");
                struct NodePQ *temp = q->auth[i];
                q->auth[i] = q->auth[i - 1];
                q->auth[i - 1] = temp;
                swap = true;
            }
        }
        count -= 1;
    }
    return true;
}

bool dequeue(PriorityQueue *q, char **author, double *dist) {
    // checks if the pq is empty first
    if (pq_empty(q)) {
        return false;
    }
    struct NodePQ *n = q->auth[q->cap - q->top];

    *author = n->author;
    //strcpy(*author, n->author);
    *dist = n->dist;

    char *a = "";
    double d = 0.0;
    // takes out this posision
    //q->auth[q->cap - q->top]->author = a;
    strcpy(q->auth[q->cap - q->top]->author, a);

    q->auth[q->cap - q->top]->dist = d;
    // makes sure to decrement the top
    q->top -= 1;

    return true;
}

// printing function for debug
void pq_print(PriorityQueue *q) {
    uint32_t total = q->cap - q->top;
    for (uint32_t i = total; i < q->cap; i += 1) {
        printf("position %d: ", i);
        nodepq_print(q->auth[i]);
        // char *auth = q->auth[i]->author;
        // double dist = q->auth[i]->dist;
        // printf("position ");
        // printf("%d: auth: %s, dist: %f\n", i, auth, dist);
    }
}
