/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA1
 *  Lex.c
 *
 *  About: This is Lex.c countains the main function for this assignment
 *****************************************************************************************/

#include "List.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    int max = 450;

    // creating the files that the program is going to be recieving
    FILE *input;
    FILE *output;

    // contains the string on the lines in the files
    char string[max];
    // this keeps track of the lines that are being used
    int line = 0;

    // this array will be used for the input will be realloced later on
    char **arr = malloc(0);

    // this is the list that we will be using in this module
    List l = newList();

    // first check if the amount of commanline inputs match the needed for this
    // module
    if (argc != 3) {
        printf("Usage: ./Lex [input file] [output file]\n");
        exit(EXIT_FAILURE);
    }

    // open the files and get them ready for usage in this module
    // then checks weather these files actuall exists
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (input == NULL) {
        printf("unable to open input file\n");
        exit(EXIT_FAILURE);
    }
    if (input == NULL) {
        printf("unable to open output file\n");
        exit(EXIT_FAILURE);
    }

    // reading each line of the file and putting into the array
    while (fgets(string, max, input) != NULL) {
        line += 1;
        arr = realloc(arr, line * sizeof(char *));
        arr[line - 1] = malloc(100 * sizeof(char));

        strcpy(arr[line - 1], string);
    }

    // the insertion sort portion part 3 of the psudo code given by the doc
    append(l, 0);
    for (int i = 1; i < line; i++) {
        moveBack(l);
        int j = get(l);
        while (strcmp(arr[i], arr[j]) <= 0) {
            movePrev(l);
            if (index(l) == -1) {
                prepend(l, i);
                break;
            }
            j = get(l);
        }
        if (index(l) >= 0) {
            insertAfter(l, i);
        }
    }

    // print the array last part then free the memory used
    for (moveFront(l); index(l) >= 0; moveNext(l)) {
        fprintf(output, "%s", arr[get(l)]);
    }

    // free all the memory
    fclose(input);
    fclose(output);

    freeList(&l);
    for (int i = 0; i < line; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}
