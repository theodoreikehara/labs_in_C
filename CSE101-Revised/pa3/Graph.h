/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA3
 *  Graph.h
 *
 *  About: This countains the graph ADT function declarations this ADT performs
 *  DFS instead of BFS which was performed by the previous pa
 *****************************************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#include <stdint.h>
#include <stdio.h>

#define NIL   0
#define UNDEF -1

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph *pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

#endif
