# PA2 CSE101 Spring 2022
## Author: Theodore Ikehara CruzId: tikehara

### About:
Breadth First Search and Shortest Paths
The purpose of this assignment is to implement a Graph ADT and some associated algorithms in C. This
project will utilize your List ADT from pa1. Begin by reading the handout on Graph Algorithms, as well
as appendices B.4, B.5 and sections 22.1, 22.2 from the text.

### How to run:
This program is to be ran in the terminal using the make file in the directory

- *make* This makes all the executables
- *make clean* This cleans all the generated files

- *./FindPath [input.txt] [output.txt]* This will run the code that was generated

#### example:
./FindPath in1.txt out1.txt

##### BUGS
Currently running into issues with in3 and in 4 seems like it is a double free
error. The bugs most likely reside in the FindPath.c. This shows the paths
correctly but does not print out all the statements.
