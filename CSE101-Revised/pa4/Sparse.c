/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA4
 *  Sparse.c
 *
 *  About: countains the main function to use matrix.c main function that takes
 *  in and outs out for pa4
 *****************************************************************************************/

#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    // needs to check if the format of running this is correct.
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in;
    FILE *out;

    // checks if the input and output are valid
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (!in) {
        printf("Error could not read input file\n");
        exit(EXIT_FAILURE);
    }
    if (!out) {
        printf("Error could not write to output file\n");
        exit(EXIT_FAILURE);
    }

    int count;
    int lineCount;

    char line[250];
    char tokenBuffer[250];
    char *token;
    Matrix A;
    Matrix B;

    int nnA;
    int nnB;
    int row;
    int col;
    int countA;
    int countB;
    int item;
    double valItem;

    lineCount = 0;
    countA = 0;
    countB = 0;
    while (fgets(line, 250, in) != NULL) {
        lineCount++;

        count = 0;
        tokenBuffer[0] = '\0';

        token = strtok(line, " \n");

        while (token != NULL) {

            // updates the token here for every file
            strcat(tokenBuffer, "   ");
            strcat(tokenBuffer, token);
            strcat(tokenBuffer, "\n");
            count++;

            // for first line only
            if (lineCount == 1) {
                if (count == 1) {
                    sscanf(token, "%d", &item);
                    A = newMatrix(item);
                    B = newMatrix(item);
                }
                if (count == 2) {
                    sscanf(token, "%d", &item);
                    nnA = item;
                }
                if (count == 3) {

                    sscanf(token, "%d", &item);
                    nnB = item;
                }
            }
            // for all subsiquent lines
            if (lineCount != 1) {
                if (count == 1) {
                    sscanf(token, "%d", &item);
                    row = item;
                }
                if (count == 2) {
                    sscanf(token, "%d", &item);
                    col = item;
                }
                if (count == 3) {
                    sscanf(token, "%lf", &valItem);
                    if (countA != nnA) {
                        if (valItem != 0.0) {
                            changeEntry(A, row, col, valItem);
                            countA++;
                        }
                    } else {
                        if (countA == nnA && countB != nnB) {
                            if (valItem != 0.0) {
                                changeEntry(B, row, col, valItem);
                                countB++;
                            }
                        }
                    }
                }
            }
            //
            token = strtok(NULL, " \n");
        }
    }

    // checks for nonzeros
    fprintf(out, "A has %d non-zero entries: \n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries: \n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix Scalar = scalarMult(1.5, A);
    Matrix Add = sum(A, B);
    Matrix Add2 = sum(A, A);
    Matrix Sub = diff(B, A);
    Matrix Sub2 = diff(A, A);
    Matrix T = transpose(A);
    Matrix dot1 = product(A, B);
    Matrix dot2 = product(B, B);

    // scalar
    fprintf(out, "(1.5)*A =  \n");
    printMatrix(out, Scalar);
    fprintf(out, "\n");

    // addition
    fprintf(out, "A+B =  \n");
    printMatrix(out, Add);
    fprintf(out, "\n");
    fprintf(out, "A+A =  \n");
    printMatrix(out, Add2);
    fprintf(out, "\n");

    // subtraction
    fprintf(out, "B-A =  \n");
    printMatrix(out, Sub);
    fprintf(out, "\n");
    fprintf(out, "A-A =  \n");
    printMatrix(out, Sub2);
    fprintf(out, "\n");

    // transpose
    fprintf(out, "Transpose(A) =  \n");
    printMatrix(out, T);
    fprintf(out, "\n");

    // dot product
    fprintf(out, "A*B =  \n");
    printMatrix(out, dot1);
    fprintf(out, "\n");
    fprintf(out, "B*B =  \n");
    printMatrix(out, dot2);
    fprintf(out, "\n");

    // close files
    fclose(in);
    fclose(out);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&Scalar);
    freeMatrix(&Add);
    freeMatrix(&Add2);
    freeMatrix(&Sub);
    freeMatrix(&Sub2);
    freeMatrix(&T);
    freeMatrix(&dot1);
    freeMatrix(&dot2);

    return (0);
}
