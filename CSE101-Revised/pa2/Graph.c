/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA2
 *  Graph.c
 *
 *  About: This countains the graph ADT function definitions
 *****************************************************************************************/

#include "Graph.h"
#include "List.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// type definition for the graph ADT
typedef struct GraphObj {

    // pointers
    // this list will contain the neighbors
    List *list;
    int *parent;
    // this is the distance from the source
    int *distance;
    int *color;

    // non pointers
    int order;
    int size;
    int source;

} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
    // allocates memory for the the graph adt that we will be creating here
    Graph g = malloc(sizeof(GraphObj));

    // allocates memory to the individual components of this adt
    g->list = calloc(n + 1, sizeof(List));
    g->parent = calloc(n + 1, sizeof(int));
    g->distance = calloc(n + 1, sizeof(int));
    g->color = calloc(n + 1, sizeof(int));

    // sets the default values of this adt
    g->order = n;
    g->size = 0;
    g->source = NIL;

    for (int i = 1; i <= n + 1; i++) {
        // makes the list of graph adt
        g->list[i] = newList();

        // assigns the values of the list
        g->color[i] = 0;
        g->parent[i] = NIL;
        g->distance[i] = INF;
    }

    // returns the object
    return g;
}

// frees the allocated memory here
void freeGraph(Graph *pG)
{

    // makes sure pG is not null or else cannot free
    if (pG != NULL) {
        for (int i = 1; i < (*pG)->order; i++) {
            // frees the list here
            freeList(&(*pG)->list[i]);
        }
        // frees all the individual components before freeing the graph
        free((*pG)->list);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->color);
        free((*pG));
    }
    return;
}
/*** Access functions ***/
int getOrder(Graph G)
{
    return G->order;
}
int getSize(Graph G)
{
    return G->size;
}
int getSource(Graph G)
{
    return G->source;
}
int getParent(Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
int getDist(Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}
void getPath(List L, Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        exit(EXIT_FAILURE);
    }

    // cursor for keeping track of the parent
    int cursor = u;
    append(L, cursor);

    // loops through the parent to find the path
    while (G->parent[cursor] != NIL) {
        cursor = G->parent[cursor];
        prepend(L, cursor);
    }
    // checks the parent and the source
    if (G->parent[u] == NIL && u != getSource(G)) {
        deleteFront(L);
        append(L, NIL);
    }

    return;
}
/*** Manipulation procedures ***/
void makeNull(Graph G)
{
    for (int i = 1; i < G->size; i++) {
        clear(G->list[i]);
    }
    return;
}

// simple soring routine
void sortL(List l, int i)
{
    moveBack(l);
    while (get(l) > i && index(l) >= 0) {
        movePrev(l);
        if (index(l) == -1) {
            prepend(l, i);
            break;
        }
    }
    if (index(l) >= 0) {
        insertAfter(l, i);
    }
    return;
}

void addEdge(Graph G, int v, int u)
{

    // checks the constraints
    if (v > G->order || u > G->order || u < 1 || v < 1) {
        exit(EXIT_FAILURE);
    }
    if (length(G->list[v]) == 0 && length(G->list[u]) == 0) {

        append(G->list[v], u);
        append(G->list[u], v);

    } else if (length(G->list[v]) != 0 && length(G->list[u]) == 0) {

        append(G->list[u], v);
        sortL(G->list[v], u);

    } else if (length(G->list[v]) == 0 && length(G->list[u]) != 0) {

        append(G->list[v], u);
        sortL(G->list[u], v);

    } else if (length(G->list[v]) != 0 && length(G->list[u]) != 0) {
        sortL(G->list[u], v);
        sortL(G->list[v], u);
    }

    G->size += 1;

    return;
}
// adding the arc to the graph similar to adding edge
void addArc(Graph G, int u, int v)
{
    // checks constraint
    if (v > G->order || u > G->order || u < 1 || v < 1) {
        exit(EXIT_FAILURE);
    }
    // searches for the correct location to add arc
    if (length(G->list[u]) != 0) {
        sortL(G->list[u], v);

    } else {
        append(G->list[u], v);
    }

    G->size += 1;

    return;
}
void BFS(Graph G, int s)
{

    // checks constraints
    if (s > G->order || s < 1) {
        exit(EXIT_FAILURE);
    }

    // iterates the graph
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = 0;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }

    G->color[s] = 1;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->source = s;

    List Q = newList();
    append(Q, s);

    while (length(Q) != 0) {
        // This is for the list queue
        int x = front(Q);
        deleteFront(Q);

        for (moveFront(G->list[x]); index(G->list[x]) != -1;
             moveNext(G->list[x])) {
            int y = get(G->list[x]);

            if (G->color[y] == 0) {
                G->color[y] = 1;
                G->parent[y] = x;
                G->distance[y] = G->distance[x] + 1;
                append(Q, y);
            }
        }

        G->color[x] = 2;
    }
    freeList(&Q);
    return;
}
/*** Other operations ***/
// just prints the graph makes use of the list print function
void printGraph(FILE *out, Graph G)
{
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->list[i]);
        if (i != getOrder(G)) {
            fprintf(out, "\n");
        }
    }
    return;
}
