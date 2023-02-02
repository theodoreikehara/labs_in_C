

// Theodore Ikehara
// Assignment 4
// Universe.h
//
// sources: Eugene's lab, lecture, assignment doc

#include "universe.h"

#include <stdlib.h>

// creates the universe struct
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

// dynamically allocates space for universe
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t i = 0; i < rows; i++) {
        u->grid[i] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

// Frees the space
void uv_delete(Universe *u) {
    for (uint32_t rows = 0; rows < u->rows; rows += 1) {
        free(u->grid[rows]);
    }
    free(u->grid);
    free(u);
    return;
}

// returns the rows and cols
uint32_t uv_rows(Universe *u) {
    return u->rows;
}
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

// Sets the dead and a live cells
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((0 <= r && 0 <= c) && (r < u->rows && c < u->cols)) {
        u->grid[r][c] = true;
    }
    return;
}
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((0 <= r && 0 <= c) && (r < u->rows && c < u->cols)) {
        u->grid[r][c] = true;
    }
    return;
}

// checks the state of the cell
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    return u->grid[r][c];
}

// populates the universe with the file
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t u_rows;
    uint32_t u_cols;

    while (fscanf(infile, "%d %d\n", &u_rows, &u_cols) != EOF) {
        if (u_rows > uv_rows(u)) {
            return false;
        }
        if (u_cols > uv_cols(u)) {
            return false;
        }
        if ((u_cols < 0) || (u_rows < 0)) {
            return false;
        }

        uv_live_cell(u, u_rows, u_cols);
    }
    return true;
}

// checks the surrounding cells depending on toroidial or not
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    // creating var to count the live cells
    uint32_t live = 0;
    uint32_t rows;
    uint32_t cols;

    // played with toroidal
    if (u->toroidal) {
        for (uint32_t row = r - 1; row <= r + 1; row++) {
            for (uint32_t col = c - 1; col <= c + 1; col++) {
                if (row != r && col != c) {
                    if (row >= u->rows || row < 0 || col >= u->cols || col < 0) {
                        rows = (r + u->rows - 1) % u->rows;
                        cols = (c + u->cols - 1) % u->cols;
                        if (u->grid[rows][cols]) {
                            live++;
                        }
                    } else {
                        if (u->grid[row][col]) {
                            live++;
                        }
                    }
                }
            }
        }
        // played without toroidal
    } else {
        for (uint32_t row = r - 1; row <= r + 1; row++) {
            for (uint32_t col = c - 1; col <= c + 1; col++) {
                if (row != r && col != c) {
                    if (row < u->rows && row > 0 && col < u->cols && col > 0) {
                        if (u->grid[row][col]) {
                            live++;
                        }
                    }
                }
            }
        }
    }
    // returns the amount alive
    return live;
}

// prints out the universe
void uv_print(Universe *u, FILE *outfile) {

    for (uint32_t i = 0; i < uv_rows(u); i++) {
        for (uint32_t j = 0; j < u->cols; j++) {
            if (uv_get_cell(u, i, j)) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
    return;
}
