/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA5
 *  Shuffle.cpp
 *
 *  About: This countains the main function for pa5 includes shuffle
 *****************************************************************************************/

#include "List.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LEN 300

void shuffle(List &L);

int main(int argc, char *argv[])
{
    // detects if input are incorrect
    if (argc != 2) {
        cout << "Usage: [input] [output]" << endl;
        return (EXIT_FAILURE);
    }

    int shuffleSize = atoi(argv[1]);
    cout << endl;
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    for (int i = 1; i <= shuffleSize; i++) {
        List newS;
        List old;
        int counter;

        newS.insertBefore(i);
        old = newS;
        shuffle(newS);
        counter += 1;

        while (!(newS == old)) {
            shuffle(newS);
            counter += 1;
        }
        cout << i << "            " << counter << endl;
        counter = 0;
    }

    List L;
    shuffle(L);

    return 0;
}

void shuffle(List &L)
{
    int half;
    int full;
    List first;
    List second;
    List finish;

    half = L.length() / 2;
    full = L.length();

    L.moveFront();
    for (int i = 0; i < half; i++) {
        first.insertBefore(L.peekNext());
        L.moveNext();
    }
    for (int i = half; i < L.length(); i++) {
        second.insertBefore(L.peekNext());
        L.moveNext();
    }

    L.moveFront();
    if ((full % 2) == 0) {
        first.moveFront();
        second.moveFront();
        for (int i = 0; i < half; i++) {
            finish.insertBefore(second.peekNext());
            second.moveNext();
            finish.insertBefore(first.peekNext());
            first.moveNext();
        }

    } else {
        first.moveFront();
        second.moveFront();
        for (int i = 0; i < half; i++) {
            finish.insertBefore(second.peekNext());
            second.moveNext();
            finish.insertBefore(first.peekNext());
            first.moveNext();
        }
        finish.insertBefore(second.peekNext());
    }

    L.moveFront();
    finish.moveFront();
    for (int i = 0; i < L.length(); i++) {
        L.setAfter(finish.peekNext());
        L.moveNext();
        finish.moveNext();
    }
}
