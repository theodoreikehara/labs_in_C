/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA1
 *  List.h
 *
 *  About: countains the List function and ADT declaration
 *****************************************************************************************/

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// struct declare
typedef struct ListObj *List;

// constructor and destructor
List newList();
void freeList(List *pL);

// access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

// Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete (List L);

// other operations
void printList(FILE *out, List L);
List copyList(List L);

