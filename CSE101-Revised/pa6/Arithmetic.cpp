/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA6
 *  Arithmetic.cpp
 *
 *  About: top level of pa6 includes the main function
 *****************************************************************************************/

#include "BigInteger.h"
#include <fstream>

using namespace std;

#define MAX_LEN 800

int main(int argc, char *argv[])
{

    // make sure the command line inputs are correct before doing anything
    if (argc != 3) {
        cout << "Usage <input> <output>" << endl;
        return EXIT_FAILURE;
    }

    ifstream in;
    ofstream out;
    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open() || !out.is_open()) {
        cout << "either input or output could not be read in" << endl;
        return EXIT_FAILURE;
    }

    BigInteger A;
    BigInteger B;

    int count = 0;
    string line;
    while (getline(in, line)) {
        size_t length = line.length();
        count++;

        int tokencount = 0;
        string buff = "";

        size_t begin = min(line.find_first_not_of(" ", 0), length);
        size_t end = min(line.find_first_not_of(" ", begin), length);

        string token = line.substr(begin, end - begin);

        while (token != "") {
            buff += "   " + token + "\n";
            tokencount++;

            begin = min(line.find_first_not_of(" ", end + 1), length);
            end = min(line.find_first_of(" ", begin), length);
            token = line.substr(begin, end - begin);
        }
        if (line.empty() == false && count == 1) {
            A = BigInteger(line);
        }
        if (line.empty() == false && count != 1) {
            B = BigInteger(line);
        }
    }

    BigInteger C = A * BigInteger("3");
    BigInteger D = B * BigInteger("2");

    BigInteger E = A;
    E *= A;
    E *= A;
    E *= A;

    BigInteger F = B;
    F *= B;
    F *= B;
    F *= B;
    F *= B;

    BigInteger G = E * BigInteger("9");
    BigInteger H = F * BigInteger("16");

    out << A << endl;
    out << endl;

    out << B << endl;
    out << endl;
    out << A + B << endl;
    out << endl;
    out << A - B << endl;
    out << endl;
    out << A - A << endl;
    out << endl;
    out << C - D << endl;
    out << endl;
    out << A * B << endl;
    out << endl;
    out << A * A << endl;
    out << endl;
    out << B * B << endl;
    out << endl;
    out << G + H << endl;

    in.close();
    out.close();

    return 0;
}
