# PA5 CSE101 Spring 2022
## Author: Theodore Ikehara, CruzId: tikehara

### About:
In this assignment you will create a BigInteger ADT in C++ that is capable of performing arithmetic
operations on arbitrarily large signed integers. The underlying data structure for this ADT will be
a List of longs. It will therefore be necessary to alter your List ADT from pa5 slightly.
Fortunately, this can be done by changing a single line of code in List.h, namely line 15

### How to run:
This program is to be ran in the terminal using the make file in the directory
The input file also needs to be in the directory

- *make* This makes all the executables
- *make clean* This cleans all the generated files

- *./Arithmetic* This will run the code that was generated

### Included Files:

- *README* : Written by you, a catalog of submitted files and any notes to the grader
- *Makefile* : Provided, alter as you see fit
- *List.h* : Provided, do not alter
- *List.cpp* : Written by you, most of the work in this assignment
- *ListTest.cpp* : Written by you, a test harness for your List
- *BigInteger.cpp* : Written by you
- *BigInteger.h* : Written by you
- *BigIntegerTest.cpp* : Test harness provided by asignment doc
- *Arithmetic.cpp* : main function and top level of this pa

#### example:
./Arithmetic [input] [output]

##### BUGS
Currently have valgrind errors but working on it
