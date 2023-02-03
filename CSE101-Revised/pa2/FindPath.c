/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA2
 *  FindPath.c
 *
 *  About: This countains the main function for finding the path
 *****************************************************************************************/

#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // checks if the format is correct
    if (argc != 3) {
        printf("Usage: FindPath <input> <output>\n");
        exit(EXIT_FAILURE);
    }

    int num = 0;
    int v1 = 1;
    int v2 = 1;
    Graph g;

    // checks if the input and output files are valid
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("unable to read input\n");
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen(argv[2], "w");
    if (!output) {
        printf("unable to write to output\n");
        exit(EXIT_FAILURE);
    }

    // creating the graph from the input here
    fscanf(input, "%d", &num);
    g = newGraph(num);

    // reading in the vert
    while (v1 != 0 || v2 != 0) {
        fscanf(input, "%d %d", &v1, &v2);
        if (v1 == 0 && v2 == 0) {
            break;
        }
        addEdge(g, v1, v2);
    }

    // print out the outcomes
    printGraph(output, g);
    fprintf(output, "\n");

    v1 = 1;
    v2 = 1;

    while (v1 != 0 || v2 != 0) {
        fscanf(input, "%d %d", &v1, &v2);
        if (v1 == 0 && v2 == 0) {
            break;
        }
        BFS(g, v1);
        List L = newList();
        getPath(L, g, v2);

        fprintf(output, "\n");

        if (getDist(g, v2) == INF) {

            fprintf(output, "The distance from %d to %d is infinity\n", v1, v2);
            fprintf(output, "No %d-%d path exists\n", v1, v2);
        } else {
            fprintf(output, "The distance from %d to %d is %d\n", v1, v2,
                    getDist(g, v2));
            fprintf(output, "A shortest %d-%d path is: ", v1, v2);
            printList(output, L);
            fprintf(output, "\n");
        }
    }

    // freeing all the used space
    freeGraph(&g);
    fclose(input);
    fclose(output);

    return 0;
}
