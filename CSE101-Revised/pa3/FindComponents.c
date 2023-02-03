/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA3
 *  FindComponents.c
 *
 *  About: This contains the main function for pa3
 * *****************************************************************************************/

#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 3) {
        printf("Usage: FindComponents <in file> <out file>");
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("unable to read in file\n");
        exit(EXIT_FAILURE);
    }
    FILE *out = fopen(argv[2], "w");
    if (!in) {
        printf("unable to write out file\n");
        exit(EXIT_FAILURE);
    }

    // reads the verticies from the in file
    int ver = 0;
    fscanf(in, "%d", &ver);
    Graph G = newGraph(ver);

    int ver1 = 1;
    int ver2 = 1;

    // reads in the verticies from the in file and builds the tree
    while (ver1 != 0 || ver2 != 0) {
        fscanf(in, "%d %d", &ver1, &ver2);
        if (ver1 == 0 && ver2 == 0) {
            break;
        }
        addArc(G, ver1, ver2);
    }

    // prints out the list and graph here
    fprintf(out, "\nAdjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // creates a list of all the verticies
    List L = newList();
    for (int i = 1; getOrder(G) >= i; i++) {
        append(L, i);
    }

    // performs the DFS algorithm
    DFS(G, L);
    Graph trans = transpose(G);
    DFS(trans, L);

    int comp = 0;
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        if (getParent(trans, get(L)) == NIL) {
            comp += 1;
        }
    }

    // prints result of above
    fprintf(out, "G contains %d strongly connected components:\n", comp);

    // using stack here for DFS
    int count = 1;
    List stack = newList();
    for (moveBack(L); index(L) != -1; movePrev(L)) {

        prepend(stack, get(L));

        if (getParent(trans, get(L)) == NIL) {
            fprintf(out, "Component %d:", count);
            printList(out, stack);
            fprintf(out, "\n");
            clear(stack);
            count += 1;
        }
    }

    // clear and free everything used
    fclose(in);
    fclose(out);

    freeList(&L);
    freeList(&stack);

    freeGraph(&G);
    freeGraph(&trans);

    return 0;
}
