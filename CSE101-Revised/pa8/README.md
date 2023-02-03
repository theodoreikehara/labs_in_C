# PA8 CSE101 Spring 2022
## Author: Theodore Ikehara, CruzId: tikehara

### About:
In this project you will re-create the Dictionary ADT from pa7, but now based on a Red-Black Tree.
Red black trees are covered in Chapter 13 of the text, and will be discussed at length in lecture.
All relevant algorithms for RBTs (and BSTs) are posted on the webpage under Examples/Pseudo-code.
Aside from having a RBT as its underlying data structure, your Dictionary ADT will have only slight
changes to its interface. The recommended approach for this project is to just copy Dictionary.cpp
from pa7 and make the necessary changes, but you can start from scratch if you feel it is necessary.
The header file Dictionary.h is posted in Examples/pa8. It's most significant difference from the
header file for pa7 is a new Node field of type int called color. Other than that, the only
difference is a new section for RBT helper functions. Although these functions are listed as
optional, and you may make changes as you like, you should consider them as absolutely necessary for
this project.

### How to run:
This program is to be ran in the terminal using the make file in the directory
The input file also needs to be in the directory

- *make* This makes all the executables
- *make clean* This cleans all the generated files

- *./Order* This will run the code that was generated
- *./WordFrequency* This will run the code that was generated

### Included Files:

- *README* Written by you, a catalog of submitted files and any notes to the grader
- *Makefile* Provided, alter as you see fit
- *Dictionary.h* Provided, you may alter the "helper functions" section, but nothing else
- *Dictionary.cpp* Written by you, the majority of work for this project
- *DictionaryTest.cpp* Written by you, your test client of the Dictionary ADT
- *Order.cpp* Written by you, the client for this project
- *WordFrequency.cpp* Written by you, a client for this project

#### example:
./Order [input] [output]
./WordFrequency [input] [output]

##### BUGS
Currently have valgrind errors but working on it
