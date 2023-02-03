# PA4 CSE101 Spring 2022
## Author: Theodore Ikehara, CruzId: tikehara

### About:
In this assignment you will create a calculator for performing matrix operations that exploits the (expected)
sparseness of its matrix operands. An 𝑛 × 𝑛 square matrix is said to be sparse if the number of non-zero
entries (here abbreviated NNZ) is small compared to the total number of entries 𝑛 squared

### How to run:
This program is to be ran in the terminal using the make file in the directory

- *make* This makes all the executables
- *make clean* This cleans all the generated files

- *./Sparse [input.txt] [output.txt]* This will run the code that was generated

#### example:
./Sparese in1.txt out1.txt

##### BUGS
current iteration there changeEntry has a memory leak, cannot seem to find where
the memory leak is in changeEntry tried freeing the allocated with newEntry but
frees to much, when testing with provided test client does not register the
leak.
