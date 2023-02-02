# Assignment 5 Huffman Coding
## Author: Theodore Ikehara

### About:
This assignment is an implementaiton of the Huffman Codes. This is an example of
loss less compression.

### How to run:
This program is to be ran in the terminal using the make file in the directory

- *make all* This will make all the executable programs
- *make encode* This will make encode
- *make decode* This will make decode
- *make format* This will format all the .c and .h files
- *make clean* This will clean all the generated files

- ./encode will compress the file
- ./decode will decode the file

#### Command line options for the program as follows
- *encode*
- -h : prints help
- -i : change input file default stdin
- -o : change output file default stdout
- -v : enables verbose

- *decode*
- -h : prints help
- -i : change input file default stdin
- -o : change output file default stdout
- -v : enables verbose

#### example:
./encode -i infile.txt -o outfile.txt -v

##### BUGS
My priority queue is bugged!! This can be caused by a couple things in priority
queue. Single queues and dequeues work perfectly fine but when more things are
queued and dequeued segfaults occur. A great portion of my total work was spent
here but I did not catch the bug until I tried testing everything. This
condition was not considered tests I wrote for myself. I tested each component
separetly and most of the other components should work as intended but pq only
partially works.
