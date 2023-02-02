# Assignment 7 Author Identification
## Author: Theodore Ikehara

### About:
This assignment is an implementation of stylometry algorithms that attempt to
determine the similarity between two texts.

### How to run:
This program is to be ran in the terminal using the make file in the firectory

- *make all* This makes identify.c this is where the main function is
- *make format* This formats the files using the given file format
- *make clean* This cleans all the generated files

- *./identify [OPTIONS]* This will run the code that was generated

#### Command line option for the program as follows
OPTIONS
   -d database     Database of authors and texts [default: lib.db]
   -k matches      Set number of top matches to display [default: 5]
   -n noisefile    Set file of words to ignore [default: noise.txt]
   -l limit        Set noise word limit [default: 100]
   -e              Set distance metric as Euclidean distance [default]
   -m              Set distance metric as Manhattan distance
   -c              Set distance metric as cosine distance
   -h              Display program help and usage

#### example:
./identify -d "small.db" -m

##### BUGS
New discovery on the bug. I see that on line 138 in identify.c is passing by
reference in my observation.

This program can only run reliably when all the db texts are readable when the
texts are not readable the program will mess up witch if author and witch is
test. This is a very small bug but was not able to fix within the given time.
Will have an update working version in the future.
