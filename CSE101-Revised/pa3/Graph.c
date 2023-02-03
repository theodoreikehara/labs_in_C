/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA3
 *  Graph.c
 *
 *  About: This countains the graph ADT function definitions executes DFS
 *  some code sourced from pa2
 * *****************************************************************************************/

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

    // this is the distance from the source
    int *parent;
    int *discover;
    int *color;
    int *finish;

    // non pointers
    int order;
    int size;

} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
    // allocates memory for the the graph adt that we will be creating here
    Graph g = malloc(sizeof(GraphObj));

    // allocates memory to the individual components of this adt
    g->list = calloc(n + 1, sizeof(List));

    g->parent = calloc(n + 1, sizeof(int));
    g->discover = calloc(n + 1, sizeof(int));
    g->color = calloc(n + 1, sizeof(int));
    g->finish = calloc(n + 1, sizeof(int));

    // sets the default values of this adt
    g->order = n;
    g->size = 0;

    for (int i = 1; i <= n; i++) {
        // makes the list of graph adt
        g->list[i] = newList();

        // assigns the values of the list
        g->color[i] = 0;
        g->parent[i] = NIL;
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
    }

    // returns the object
    return g;
}

// frees the allocated memory here
void freeGraph(Graph *pG)
{

    // makes sure pG is not null or else cannot free
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            // frees the list here
            freeList(&(*pG)->list[i]);
        }
        // frees all the individual components before freeing the graph
        free((*pG)->list);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
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
    if (G == NULL) {
        exit(EXIT_FAILURE);
    }
    return G->size;
}
int getParent(Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
int getDiscover(Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}
int getFinish(Graph G, int u)
{
    if (u < 1 || u > getOrder(G)) {
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation procedures
// this is from the Graph.c from pa2
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

    // visits the constraints
    if (v > G->order || u > G->order || u < 1 || v < 1) {
        exit(EXIT_FAILURE);
    }
    if (length(G->list[v]) == 0 && length(G->list[u]) == 0) {
        G->size += 1;

        append(G->list[v], u);
        append(G->list[u], v);

    } else if (length(G->list[v]) != 0 && length(G->list[u]) == 0) {
        G->size += 1;

        append(G->list[u], v);
        sortL(G->list[v], u);

    } else if (length(G->list[v]) == 0 && length(G->list[u]) != 0) {
        G->size += 1;

        append(G->list[v], u);
        sortL(G->list[u], v);

    } else if (length(G->list[v]) != 0 && length(G->list[u]) != 0) {
        G->size += 1;

        sortL(G->list[u], v);
        sortL(G->list[v], u);
    }

    return;
}
// adding the arc to the graph similar to adding edge
//

void addArc(Graph G, int u, int v)
{
    // visits constraint
    if (v > G->order || u > G->order || u < 1 || v < 1) {
        exit(EXIT_FAILURE);
    }
    // searches for the correct location to add arc
    if (length(G->list[u]) != 0) {
        G->size += 1;
        sortL(G->list[u], v);

    } else {
        G->size += 1;
        append(G->list[u], v);
    }

    return;
}
// abstraction of visiting and visiting each node
int count = 0;
void visit(Graph G, int x)
{
    count += 1;

    // assigns to the global var for DFS
    G->discover[x] = count;
    G->color[x] = 1;

    for (moveFront(G->list[x]); index(G->list[x]) != -1; moveNext(G->list[x])) {
        int y = get(G->list[x]);
        if (G->color[y] == 0) {
            G->parent[y] = x;
            visit(G, y);
        }
    }

    G->color[x] = 2;
    count += 1;
    G->finish[x] = count;
}

// performs the DFS
// this is provided in psudo code in the lab doc examples
void DFS(Graph G, List S)
{
    count = 0;
    for (int i = 1; i <= getOrder(G); i++) {
        G->parent[i] = NIL;
        G->color[i] = 0;
    }

    for (moveFront(S); index(S) != -1; moveNext(S)) {
        if (G->color[get(S)] == 0) {
            visit(G, get(S));
        }
    }
    clear(S);

    // strart DFS algorithm this is from the psudo code prvided
    for (int i = 1; i <= getOrder(G); i++) {
        if (length(S) != 0) {
            for (moveFront(S); index(S) != -1; moveNext(S)) {
                if (G->finish[i] > G->finish[get(S)]) {
                    insertBefore(S, i);
                    break;
                }
            }
            // if bellow the threshhold amount
            if (index(S) == -1) {
                append(S, i);
            }
        } else {
            append(S, i);
        }
    }
    return;
}

/*** Other operations ***/
// just prints the graph makes use of the list print function
Graph transpose(Graph G)
{
    // iterate through the graph and return the same graph
    //
    Graph x = newGraph(getOrder(G));

    // iterates through the graph
    for (int i = 1; i <= getOrder(G); i++) {
        for (moveFront(G->list[i]); index(G->list[i]) != -1;
             moveNext(G->list[i])) {
            addArc(x, get(G->list[i]), i);
        }
    }

    return x;
}

// will be copying over the graph here
Graph copyGraph(Graph G)
{
    // this is the where the copy will be stored
    Graph x = newGraph(getOrder(G));

    // this litterally just copys everything over
    for (int i = 1; i <= getOrder(G); i++) {
        x->list[i] = copyList(G->list[i]);
        x->color[i] = G->color[i];
        x->parent[i] = G->parent[i];
        x->discover[i] = G->discover[i];
        x->finish[i] = G->finish[i];
    }

    // returns the copied over graph
    return x;
}

void printGraph(FILE *out, Graph G)
{
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->list[i]);
        fprintf(out, "\n");
    }
    return;
}
