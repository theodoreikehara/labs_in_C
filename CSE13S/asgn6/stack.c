
// Theodore Ikehara
// asgn6 Huffman Coding
//
// This file contains the code for stack.c
//
// source: Eugene's section

#include "stack.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// This contains the ADT info similar to pq implementation
struct Stack {
    // This is the nodes that are stored inside the stack
    Node **inside;
    // This keeps track of the head of the stack
    uint32_t head;
    // This is the capacity of the stack
    uint32_t capacity;
};

Stack *stack_create(uint32_t capacity) {
    // This dynamically allocates the space for the stack
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    // allocates space for the stuff inside the stack
    stack->inside = malloc(capacity * sizeof(Node *));
    // These are the assignments for an empty stack
    stack->capacity = capacity;
    stack->head = 0;

    return stack;
}

// frees the allocated space
void stack_delete(Stack **s) {
    free((*s)->inside);
    free(*s);
    return;
}

// checks if the stack is empty
bool stack_empty(Stack *s) {
    if (!s->head) {
        return true;
    }
    return false;
}

// checks to see if the stack is full
bool stack_full(Stack *s) {
    if (s->head == s->capacity) {
        return true;
    }
    return false;
}

// checks the stack size
uint32_t stack_size(Stack *s) {
    return s->head;
}

// this pushes node into stack
bool stack_push(Stack *s, Node *n) {
    // This checks if the stack is full first before proceding
    if (stack_full(s)) {
        return false;
    }
    // this assigns the top space for this node
    s->inside[s->head] = n;
    // after adding element head needs to incremented
    s->head += 1;

    return true;
}

// this pops element out of the stack
bool stack_pop(Stack *s, Node **n) {
    // checks to see if stack is empty before proceeding
    if (stack_empty(s)) {
        return false;
    }
    // head is an empty space so need space before that
    s->head -= 1;
    // loads n with the node at location of head-1
    *n = s->inside[s->head];

    return true;
}

// this prints the nodes in the stack
// for debugging
void stack_print(Stack *s) {
    for (int i = 0; i < (int) s->head; i += 1) {
        node_print(s->inside[i]);
    }
}
