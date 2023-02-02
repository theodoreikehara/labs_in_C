

// Theodore Ikehara
// CSE13 Assignment 3 winter 2022
// About: plays the game of life using ncurses

#include "universe.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

#define OPTIONS "tsn:i:o:"
#define DELAY   50000

int main(int argc, char **argv) {
    bool no_t;
    bool no_cur;
    int generations = 100;

    FILE *read = stdin;
    FILE *write = stdout;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': no_t = true; break;
        case 's': no_cur = true; break;
        case 'n': generations = atoi(optarg); break;
        case 'i': read = fopen(optarg, "r"); break;
        case 'o': write = fopen(optarg, "w"); break;
        }
    }

    // setting the rows and the cols of the univers
    int urows = 0;
    int ucols = 0;
    fscanf(read, "%d %d\n", &urows, &ucols);

    // creating two universes to use ncurses and to know the position of the
    // previous state
    Universe *unia = uv_create(urows, ucols, no_t);
    Universe *unib = uv_create(urows, ucols, no_t);

    uv_populate(unia, read);
    unia = unib;

    // playing the game with n curses
    if (!no_cur) {
        initscr();
        curs_set(false);
        while (generations > 0) {
            clear();
            for (int row = 0; row < urows; row++) {
                for (int col = 0; col < ucols; col++) {
                    // updateing based on the rules
                    if ((uv_census(unib, row, col) == 3)) { //check the census to decide
                        uv_live_cell(unia, row, col);
                    }
                    if ((uv_census(unib, row, col) < 2) || (uv_census(unia, row, col) > 3)) {
                        uv_dead_cell(unia, row, col);
                    }

                    if (uv_get_cell(unia, row, col)) {
                        mvprintw(row, col, "o");
                    }
                }
            }
            usleep(DELAY);
            refresh();

            Universe *unic = unia;
            unia = unib;
            unib = unia;
            uv_delete(unic);

            generations--;
        }
        endwin();
        // Playing the game without n curses
    } else {
        while (generations > 0) {

            for (int row = 0; row < urows; row++) {
                for (int col = 0; col < ucols; col++) {
                    // updateing the grid based on the game
                    if ((uv_census(unib, row, col) == 3)) {
                        uv_live_cell(unib, row, col);
                    }
                    if ((uv_census(unib, row, col) < 2) || (uv_census(unia, row, col) > 3)) {
                        uv_dead_cell(unib, row, col);
                    }
                }
            }
            Universe *unic = unia;
            unia = unib;
            unib = unia;
            uv_delete(unic);

            generations--;
        }
    }

    uv_print(unia, write);
    fclose(read);
    fclose(write);
    uv_delete(unia);
    uv_delete(unib);
    return 0;
}
