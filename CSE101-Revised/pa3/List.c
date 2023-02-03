/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA1
 *  List.c
 *
 *  About: This countains the list ADT with private type node
 *****************************************************************************************/

#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Node Object for list
// only accessable in this class

/////////////////////////////////// Private Node ADT

// type definition
typedef struct NodeObj *Node;

typedef struct NodeObj {
    int data;
    Node next;
    Node pre;
} NodeObj;

// creates new node
Node newNode(int data)
{
    Node n = malloc(sizeof(NodeObj));
    n->data = data;
    n->next = NULL;
    n->pre = NULL;
    return n;
}

// node destructor
void freeNode(Node *n)
{
    if (*n != NULL) {
        if (n != NULL) {
            free(*n);
            n = NULL;
        }
    }
    return;
}

/////////////////////////////////// End Private Node ADT

/////////////////////////////////// Start List ADT

// ADT def
typedef struct ListObj {
    int len;
    int index;
    Node front;
    Node back;
    Node cur;
} ListObj;

// creates a new empty list
List newList(void)
{
    List l;
    l = malloc(sizeof(ListObj));
    l->len = 0;
    l->index = -1;
    l->front = NULL;
    l->back = NULL;
    l->cur = NULL;
    return l;
}

// frees the list
void freeList(List *pL)
{
    if (*pL != NULL) {
        if (pL != NULL) {
            while (!length(*pL) == 0) {
                deleteFront(*pL);
            }
            free(*pL);
            *pL = NULL;
        }
    }
}

// access functions for the list ADT
// returns the length of the list
int length(List L)
{
    if (L == NULL) {
        printf("list length call error\n");
        exit(EXIT_FAILURE);
    }
    return L->len;
}

// returns the index of the cursor in the list
int index(List L)
{
    if (L == NULL) {
        printf("list index call error\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// returns the front element
int front(List L)
{
    if (L == NULL || L->len == 0) {
        printf("list error list is either empty or null\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// returns the back element
int back(List L)
{
    if (L == NULL || L->len == 0) {
        printf("list error list is either empty or null\n");
        exit(EXIT_FAILURE);
    }

    return L->back->data;
}

// returns the element at the cursor
int get(List L)
{
    if (L->len > 0 && L->index >= 0) {
        return L->cur->data;
    }
    printf("error in get\n");
    exit(EXIT_FAILURE);
}

// checks to see if the list are equal
bool equals(List A, List B)
{

    if (A == NULL || B == NULL) {
        printf("list error list is null\n");
        exit(EXIT_FAILURE);
    }

    Node tempA = A->front;
    Node tempB = B->front;
    bool eq = (A->len == B->len);

    tempA = A->front;
    tempB = B->front;
    while (tempA != NULL && eq) {
        eq = (tempA->data == tempB->data);
        tempA = tempA->next;
        tempB = tempB->next;
    }
    return eq;
}

// manipulation functions
//

// resets the list to its original empty state
void clear(List L)
{
    if (L == NULL) {
        printf("list error null\n");
        exit(EXIT_FAILURE);
    }

    while (length(L) != 0) {
        deleteFront(L);
    }

    return;
}

// sets the cursor element to x
void set(List L, int x)
{
    if (L == NULL) {
        printf("list error null\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) >= 0) {
        L->cur->data = x;
    }

    return;
}

// sets cursor under the front element
void moveFront(List L)
{
    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        L->cur = NULL;
        L->index = -1;
        return;
    }

    L->cur = L->front;
    L->index = 0;
    return;
}

// sets cursor under the back element
void moveBack(List L)
{
    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        L->cur = NULL;
        L->index = -1;
        return;
    }
    L->cur = L->back;
    L->index = L->len - 1;
    return;
}

// move cursor to previous
void movePrev(List L)
{
    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }

    if (L->cur->pre == NULL) {
        L->cur = NULL;
        L->index = -1;
        return;
    }

    L->cur = L->cur->pre;
    L->index--;
    return;
}

// moves the cursor one step towards the back of the list
void moveNext(List L)
{
    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }

    if (L->cur->next == NULL) {
        L->cur = NULL;
        L->index = -1;
        return;
    }

    L->cur = L->cur->next;
    L->index++;

    return;
}

// prepends to the list
void prepend(List L, int x)
{

    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }

    // creates the new node to prepend
    Node n = newNode(x);

    if (L->len == 0) {
        L->back = n;
    } else if (length(L) > 0 && index(L) >= 0) {
        L->front->pre = n;
        n->next = L->front;
        L->index++;
    } else {
        // else increment the other node
        L->front->pre = n;
        n->next = L->front;
    }
    L->front = n;
    L->len++;
    return;
}

// this appends to the list
void append(List L, int x)
{
    if (L == NULL) {
        printf("list error null");
        exit(EXIT_FAILURE);
    }

    Node n = newNode(x);

    if (L->len == 0) {
        L->back = n;
        L->front = n;
        L->len += 1;
        return;
    }
    // This occurs when len is greater than 0
    L->back->next = n;
    n->pre = L->back;
    L->back = n;
    L->len += 1;
    return;
}

// inserts new element before the cursor
void insertBefore(List L, int x)
{
    if (L == NULL || length(L) == 0) {
        printf("list error in insertBefore\n");
        exit(EXIT_FAILURE);
    }

    Node n = newNode(x);
    Node temp;

    if (length(L) >= 1 && index(L) >= 0) {
        if (length(L) == 1) {
            L->front->pre = n;
            n->next = L->front;
            L->front = n;
            L->len += 1;
            L->index += 1;
            return;
        }

        if (L->cur == L->front) {
            L->cur->pre = n;
            n->next = L->cur;
            L->front = n;
            L->len += 1;
            L->index += 1;
            return;
        }

        if (L->cur == L->back) {
            temp = L->cur->pre;
            temp->next = n;
            n->pre = temp;
            n->next = L->cur;
            L->cur->pre = n;
            L->len += 1;
            L->index += 1;
            return;
        }

        temp = L->cur->pre;
        temp->next = n;
        n->pre = temp;
        n->next = L->cur;
        L->cur->pre = n;
        L->len += 1;
        L->index += 1;
        return;
    }
}

// inserts an element after the cursor
void insertAfter(List L, int x)
{
    if (L == NULL || length(L) == 0) {
        printf("list error in insertAfter\n");
        exit(EXIT_FAILURE);
    }

    Node n = newNode(x);
    Node temp;

    if (length(L) >= 1 && index(L) >= 0) {
        if (length(L) == 1) {
            L->back->next = n;
            n->pre = L->back;
            L->back = n;
        }

        else if (L->cur == L->front) {
            temp = L->cur->next;
            temp->pre = n;
            n->next = temp;
            n->pre = L->cur;
            L->cur->next = n;
        }

        else if (L->cur == L->back) {
            L->cur->next = n;
            n->pre = L->cur;
            L->back = n;
        }

        else {
            temp = L->cur->next;
            temp->pre = n;
            n->next = temp;
            n->pre = L->cur;
            L->cur->next = n;
        }

        L->len += 1;
        return;
    }
}

// this deletes the front element
void deleteFront(List L)
{
    if (L == NULL || length(L) == 0) {
        printf("list error in insertAfter\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->front;
    if (length(L) > 1) {
        if (L->cur == L->front) {
            L->front = L->front->next;
            L->front->pre = NULL;
            L->cur = NULL;
            L->index = -1;
        }

        else if (L->cur != L->front) {
            if (index(L) >= 0) {
                L->index -= 1;
            }
            L->front = L->front->next;
            L->front->pre = NULL;
        }

        else {
            L->front = NULL;
            L->back = NULL;
            L->cur = NULL;
        }
    } else {
        L->front = NULL;
        L->back = NULL;
        L->cur = NULL;
    }
    L->len -= 1;
    freeNode(&temp);
    return;
}

// deletes the back element of the list
void deleteBack(List L)
{
    if (L == NULL || length(L) == 0) {
        printf("list error in deleteBack\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->back;

    if (length(L) > 1) {
        if (L->cur == L->back) {
            L->back = L->back->pre;
            L->back->next = NULL;
            L->cur = NULL;
            L->index = -1;
        }

        else if (L->cur != L->back) {
            L->back = L->back->pre;
            L->back->next = NULL;
        }

        else {
            L->front = NULL;
            L->back = NULL;
            L->cur = NULL;
            L->index = -1;
        }
    }
    L->len -= 1;
    freeNode(&temp);
    return;
}

// deletes the cursor element
void delete (List L)
{
    if (L == NULL || length(L) == 0 || index(L) == -1) {
        printf("list error in delete\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->cur;

    if (L->cur == L->front) {
        L->front = L->front->next;
        L->front->pre = NULL;

    } else if (L->cur == L->back) {
        L->back = L->back->pre;
        L->back->next = NULL;

    } else if (length(L) == 1) {
        L->front = NULL;
        L->back = NULL;
    } else {
        L->cur->pre->next = L->cur->next;
        L->cur->next->pre = L->cur->pre;
    }

    freeNode(&temp);
    L->cur = NULL;
    L->index = -1;
    L->len -= 1;

    return;
}

// prints the list to outfile
void printList(FILE *out, List L)
{

    if (L == NULL) {
        printf("list is null nothing to print");
        exit(EXIT_FAILURE);
    }

    for (Node n = L->front; n != NULL; n = n->next) {
        fprintf(out, "%d ", n->data);
    }
    printf("\n");

    return;
}

// returns a new list with the elements in L
List copyList(List L)
{

    if (L == NULL) {
        printf("list is null nothing to copy");
        exit(EXIT_FAILURE);
    }

    List li = newList();

    for (Node n = L->front; n != NULL; n = n->next) {
        append(li, n->data);
    }

    return li;
}

