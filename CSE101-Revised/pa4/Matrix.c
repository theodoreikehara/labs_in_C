/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA4
 *  Matrix.c
 *
 *  About: countains the definitions for the matrix adt declared in the header
 *  file
 *****************************************************************************************/

#include "Matrix.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs
// -----------------------------------------------------------------------------------------

// node type for the entries into the matrix
typedef struct EntryObj *Entry;

// type definition of  the entry obj
typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj {
    List *rows;
    int size;
    int nze;
} MatrixObj;

// con-des
// -----------------------------------------------------------------------------------------

// the constructor for the entry object
Entry newEntry(int col, double val)
{
    Entry n = malloc(sizeof(EntryObj));
    n->col = col;
    n->val = val;
    return n;
}

// the constructor for the matrix obj
Matrix newMatrix(int n)
{
    Matrix m = malloc(sizeof(MatrixObj));
    m->rows = malloc((n + 1) * sizeof(List));
    m->size = n;
    m->nze = 0;
    for (int i = 1; i <= n; i++) {
        m->rows[i] = newList();
    }
    return m;
}

// destructor for the entry obj
void freeEntry(Entry *pE)
{
    if (pE && *pE) {
        free(*pE);
        *pE = NULL;
    }
    return;
}

// destructor for the matrix obj
void freeMatrix(Matrix *pM)
{
    if (!pM) {
        printf("error in free matrix\n");
        return;
    }

    // need to free the entry inside list first then free list then free rows
    // than matrix
    for (int i = 1; i <= size(*pM); i++) {

        List L = (*pM)->rows[i];

        if (length(L) != 0) {
            for (moveFront(L); index(L) >= 0; moveNext(L)) {
                Entry E = (Entry)get(L);
                freeEntry(&E);
            }
        }
        freeList(&L);
    }

    free((*pM)->rows);
    free(*pM);
    *pM = NULL;
    return;
}

// access functions
// --------------------------------------------------------------------------------

// returns the size of matrix
int size(Matrix M)
{
    if (M) {
        return M->size;
    }
    printf("Error in size matrix\n");
    exit(EXIT_FAILURE);
}

// returns the non zero entry in the matrix
int NNZ(Matrix M)
{
    if (M) {
        return M->nze;
    }
    printf("Error in NNZ matrix\n");
    exit(EXIT_FAILURE);
}

// returns 1 if the matrix are equal if not return 0
// Tested
int equals(Matrix A, Matrix B)
{
    double valA;
    double valB;

    if ((size(A) != size(B))) {
        return 0;
    } else if (A == B) {
        return 1;
    } else {
        for (int i = 1; i <= size(A); i++) {
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            if (length(A->rows[i]) == length(B->rows[i])) {
                while (index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0) {
                    valA = ((Entry)get(A->rows[i]))->val;
                    valB = ((Entry)get(B->rows[i]))->val;
                    if (valA != valB) {
                        return 0;
                    }
                    moveNext(A->rows[i]);
                    moveNext(B->rows[i]);
                }
            } else {
                return 0;
            }
        }
        return 1;
    }
}

// manipulation functions
// --------------------------------------------------------------------------

// resets the entire matrix m to a zero matrix
// tested
void makeZero(Matrix M)
{
    if (!M) {
        printf("Error in makeZero\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= M->size; i++) {

        moveFront(M->rows[i]);

        while (index(M->rows[i]) != -1) {
            Entry e = get(M->rows[i]);
            freeEntry(&e);
            moveNext(M->rows[i]);
        }
        clear(M->rows[i]);
    }

    M->nze = 0;

    return;
}

// changes value in given location to x
// tested
void changeEntry(Matrix M, int i, int j, double x)
{

    if (M == NULL) {
        printf("NULL Error in changeEntry\n");
        exit(EXIT_FAILURE);
    }
    if ((i > M->size) || (j > M->size) || (i < 1) || (j < 1)) {
        printf("out of bounds changeEntry\n");
        exit(EXIT_FAILURE);
    }

    Entry A;
    Entry B;

    moveFront(M->rows[i]);

    if (index(M->rows[i]) == -1 && x != 0.0) {
        A = newEntry(j, x);
        append(M->rows[i], A);
        M->nze++;

        return;
    }

    while (index(M->rows[i]) != -1) {
        B = get(M->rows[i]);

        if (B->col == j && x == 0.0) {
            delete (M->rows[i]);
            M->nze--;
            return;
        }

        if (B->col == j && x != 0.0) {
            A = newEntry(j, x);
            insertBefore(M->rows[i], A);
            delete (M->rows[i]);

            return;
        }

        moveNext(M->rows[i]);
    }

    if (index(M->rows[i]) == -1 && x == 0.0) {
        return;
    }

    A = newEntry(j, x);
    moveFront(M->rows[i]);

    while (index(M->rows[i]) != -1) {
        B = get(M->rows[i]);

        if (j < B->col) {
            insertBefore(M->rows[i], A);
            M->nze++;

            return;
        }

        moveNext(M->rows[i]);
    }

    append(M->rows[i], A);

    M->nze++;

    return;
}

// copy matrix
// tested
Matrix copy(Matrix A)
{

    if (!A) {
        printf("NULL Error in copy\n");
        exit(EXIT_FAILURE);
    }

    Matrix Z = newMatrix(A->size);
    Entry Ae;

    for (int i = 1; i <= A->size; i++) {
        moveFront(A->rows[i]);

        while (index(A->rows[i]) != -1) {
            Ae = get(A->rows[i]);
            changeEntry(Z, i, Ae->col, Ae->val);
            moveNext(A->rows[i]);
        }
    }

    return Z;
}

// transposes the matrix
// tested
Matrix transpose(Matrix A)
{
    if (A == NULL) {
        printf("NULL Error in transpose\n");
        exit(EXIT_FAILURE);
    }

    Matrix Z = newMatrix(A->size);
    Entry Ae;

    for (int i = 1; i <= A->size; i++) {
        moveFront(A->rows[i]);

        while (index(A->rows[i]) != -1) {
            Ae = get(A->rows[i]);
            changeEntry(Z, Ae->col, i, Ae->val);
            moveNext(A->rows[i]);
        }
    }

    return Z;
}

// tested
Matrix scalarMult(double x, Matrix A)
{

    Matrix Z = newMatrix(A->size);
    Entry Ae;

    int col;

    for (int i = 1; i <= A->size; i++) {
        moveFront(A->rows[i]);

        while (index(A->rows[i]) != -1) {
            Ae = get(A->rows[i]);
            col = Ae->col;
            changeEntry(Z, i, col, x * Ae->val);
            moveNext(A->rows[i]);
        }
    }
    return Z;
}

// this function will be used to assign in the adding sub and div functions
void assi(int col, double val, List A, List B, Matrix M, int i)
{
    // checks for NULL for debugging
    if (!A || !M) {
        printf("NULL error in assi function matrix\n");
        exit(EXIT_FAILURE);
    }

    col = ((Entry)get(A))->col;
    val = ((Entry)get(B))->val;
    changeEntry(M, i, col, val);
    return;
}
void assi2(int col, double val, List A, List B, Matrix M, int i)
{
    // checks for NULL for debugging
    if (!A || !M) {
        printf("NULL error in assi function matrix\n");
        exit(EXIT_FAILURE);
    }

    col = ((Entry)get(A))->col;
    val = ((Entry)get(B))->val;
    changeEntry(M, i, col, val * (-1));
    return;
}

// take the sum for the matrix
// tested
Matrix sum(Matrix A, Matrix B)
{

    if (!A || !B) {
        printf("NULL Error in matrix sum\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("size not the same in sum\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        return scalarMult(2.0, A);
    } else {
        Matrix M = newMatrix(size(A));
        List ListA;
        List ListB;

        int colListA;
        int colListB;
        double valListA;
        double valListB;

        for (int i = 1; i <= size(A); i++) {
            ListA = A->rows[i];
            ListB = B->rows[i];

            // algorithm starts here
            int col = 0;
            double val = 0;

            if (length(ListA) == 0 && length(ListB) != 0) {
                for (moveFront(ListB); index(ListB) >= 0; moveNext(ListB)) {

                    assi(col, val, ListB, ListB, M, i);
                }
            } else if (length(ListA) != 0 && length(ListB) == 0) {
                for (moveFront(ListA); index(ListA) >= 0; moveNext(ListA)) {

                    assi(col, val, ListA, ListA, M, i);
                }
            } else {
                moveFront(ListA);
                moveFront(ListB);
                while (index(ListA) != -1 || index(ListB) != -1) {
                    if (index(ListA) == -1 && index(ListB) != -1) {

                        assi(colListB, valListB, ListB, ListB, M, i);
                        moveNext(ListB);

                    } else if (index(ListA) != -1 && index(ListB) == -1) {

                        assi(colListA, valListA, ListA, ListA, M, i);
                        moveNext(ListA);

                    } else {

                        valListA = ((Entry)get(ListA))->val;
                        valListB = ((Entry)get(ListB))->val;

                        colListA = ((Entry)get(ListA))->col;
                        colListB = ((Entry)get(ListB))->col;

                        if (colListA == colListB) {
                            if (valListA + valListB != 0) {
                                changeEntry(M, i, colListA,
                                            (valListB + valListA));
                            }
                            moveNext(ListB);
                            moveNext(ListA);
                        }

                        if (colListA < colListB) {
                            changeEntry(M, i, colListA, valListA);
                            moveNext(ListA);
                        }

                        if (colListA > colListB) {
                            changeEntry(M, i, colListB, valListB);
                            moveNext(ListB);
                        }
                    }
                }
            }
            //
        }
        return M;
    }
}

// this takes the matrix difference between A and B
// very similar to the summ function
// tested
Matrix diff(Matrix A, Matrix B)
{
    if (!A || !B) {
        printf("NULL Error in matrix sum\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("size not the same in sum\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        Matrix dupe = copy(A);
        Matrix dif = diff(A, dupe);
        freeMatrix(&dupe);
        return dif;
    } else {
        Matrix M = newMatrix(size(A));

        List ListA;
        List ListB;

        for (int i = 1; i <= size(A); i++) {
            ListA = A->rows[i];
            ListB = B->rows[i];
            // algorithm starts here
            int col = 0;
            double val = 0;

            int col_ListA;
            int col_ListB;
            double valListA;
            double valListB;

            if (length(ListA) == 0 && length(ListB) != 0) {
                for (moveFront(ListB); index(ListB) >= 0; moveNext(ListB)) {

                    assi2(col, val, ListB, ListB, M, i);
                }
            }

            if (length(ListA) != 0 && length(ListB) == 0) {
                for (moveFront(ListA); index(ListA) >= 0; moveNext(ListA)) {

                    assi(col, val, ListA, ListA, M, i);
                }
            }

            moveFront(ListA);
            moveFront(ListB);

            while (index(ListA) != -1 || index(ListB) != -1) {
                if (index(ListA) == -1 && index(ListB) != -1) {

                    assi2(col_ListB, valListB, ListB, ListB, M, i);
                    moveNext(ListB);

                } else if (index(ListA) != -1 && index(ListB) == -1) {

                    assi(col_ListA, valListA, ListA, ListA, M, i);
                    moveNext(ListA);

                } else {
                    // updates the vals
                    valListA = ((Entry)get(ListA))->val;
                    valListB = ((Entry)get(ListB))->val;

                    col_ListA = ((Entry)get(ListA))->col;
                    col_ListB = ((Entry)get(ListB))->col;

                    // checks for the different conditions of the list
                    if (col_ListA == col_ListB) {
                        if (valListA - valListB != 0) {
                            changeEntry(M, i, col_ListA, (valListA - valListB));
                        }
                        moveNext(ListB);
                        moveNext(ListA);
                    }
                    if (col_ListA < col_ListB) {
                        changeEntry(M, i, col_ListA, valListA);
                        moveNext(ListA);
                    }
                    if (col_ListA > col_ListB) {
                        changeEntry(M, i, col_ListB, -1 * valListB);
                        moveNext(ListB);
                    }
                }
            }
            //
        }
        return M;
    }
}

// helper function for the product function
// tested
double pro_helper(List ListA, List ListB)
{
    double sum = 0;
    int colListA;
    int colListB;

    double valListA;
    double valListB;
    moveFront(ListA);
    moveFront(ListB);
    while (index(ListA) >= 0 && index(ListB) >= 0) {

        colListA = ((Entry)get(ListA))->col;
        colListB = ((Entry)get(ListB))->col;
        valListA = ((Entry)get(ListA))->val;
        valListB = ((Entry)get(ListB))->val;

        if (colListA == colListB) {
            sum += ((valListA) * (valListB));
            moveNext(ListB);
            moveNext(ListA);
        }

        if (colListA < colListB) {
            moveNext(ListA);
        }

        if (colListA > colListB) {
            moveNext(ListB);
        }
    }
    return sum;
}

// takes the product of the matrix
// tested
Matrix product(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL) {
        printf("NULL Error in product matrix\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("size error in product matrix\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        Matrix C = copy(A);
        Matrix S = product(A, C);
        freeMatrix(&C);
        return (S);
    } else {
        // new entry for this calculation
        double sum = 0;
        Matrix M = newMatrix(size(A));
        Matrix T = transpose(B);
        List ListA;
        List ListB;
        for (int i = 1; i <= size(A); i++) {
            ListA = A->rows[i];
            if (length(ListA) != 0) {
                for (int j = 1; j <= size(A); j++) {
                    ListB = T->rows[j];
                    sum = pro_helper(ListA, ListB);

                    changeEntry(M, i, j, sum);
                }
            }
        }

        freeMatrix(&T);
        return M;
    }
}

// prints the matrix
void printMatrix(FILE *out, Matrix M)
{
    for (int i = 1; i <= M->size; i++) {
        moveFront(M->rows[i]);

        if (index(M->rows[i]) != -1) {

            fprintf(out, "%d: ", i);
        }
        while (index(M->rows[i]) != -1) {
            Entry Ae = get(M->rows[i]);
            fprintf(out, "(");
            fprintf(out, "%d, ", Ae->col);
            fprintf(out, "%.1f) ", Ae->val);
            moveNext(M->rows[i]);
        }
        moveFront(M->rows[i]);
        if (i >= 1) {
            if (index(M->rows[i]) != -1) {
                fprintf(out, "\n");
            }
        }
    }
}
