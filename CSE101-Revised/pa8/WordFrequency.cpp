// Client for pa8

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LEN 300

int main(int argc, char *argv[])
{
    Dictionary D;

    ifstream in;
    ofstream out;
    string line;

    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    string word;

    if (argc != 3) {
        cerr << "Usage: [input] [output]" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open()) {
        cerr << "unable to open infile" << endl;
        return (EXIT_FAILURE);
    }
    if (!out.is_open()) {
        cerr << "unable to open outfile" << endl;
        return (EXIT_FAILURE);
    }

    while (getline(in, line)) {
        for (unsigned long int i = 0; i < line.length(); i++) {
            line[i] = tolower(line[i]);
        }
    }

    return 0;
}
