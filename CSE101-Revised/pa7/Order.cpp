#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

    int line_count;
    ifstream in;
    ofstream out;
    string line;
    Dictionary A;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    out.open(argv[2]);
    line_count = 0;

    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return (EXIT_FAILURE);
    }
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return (EXIT_FAILURE);
    }

    while (getline(in, line)) {
        line_count++;
        A.setValue(line, line_count);
    }

    out << A << endl;
    out << A.pre_string() << endl;

    in.close();
    out.close();

    return (EXIT_SUCCESS);
}

