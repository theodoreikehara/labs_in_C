# Assignment 5 Public Key Cryptography
## Author: Theodore Ikehara

### About:
This assignment is a public key cryptography library using the rsa private,
public key cryptography. This assignment is mainly split into 3 parts: keygen,
decrypt, and encrypt.

### How to run this program:
This program is ran in C using the C compiler clang you will type in the
terminal in the directory of this assignment command listed below to compile:

- *make all* This will make all the components of the assignment.
- *make keygen* This will make keygen.c
- *make decrypt* This will make decrypt.c
- *make encrypt* This will make encrypt.c
- *make format* This will format all the C and header files
- *make clean* This will clean all the generated files from make

- First *./keygen* will be ran first to generate the key pair
- Then *./encrypt* will be used to encrypt the files
- Finally *./decrypt* will be used to decrypt the encrypted file

#### Command Line options for the programs as follows
- keygen
- -b : specifies the minimum bits needed for the public modulus n .
- -i : specifies the number of Miller-Rabin iterations for testing primes (default: 50).
- -n pbfile : specifies the public key file (default: rsa.pub).
- -d pvfile : specifies the private key file (default: rsa.priv).
- -s : specifies the random seed for the random state initialization (default: the seconds since the
U NIX epoch, given by time(NULL) ).
- -v : enables verbose output.
- -h : displays program synopsis and usage.

- encryptor
- -i : specifies the input file to encrypt (default: stdin ).
- -o : specifies the output file to encrypt (default: stdout ).
- -n : specifies the file containing the public key (default: rsa.pub ).
- -v : enables verbose output.
- -h : displays program synopsis and usage.

- decryptor
- -i : specifies the input file to decrypt (default: stdin ).
- -o : specifies the output file to decrypt (default: stdout ).
- -n : specifies the file containing the private key (default: rsa.priv ).
- -v : enables verbose output.
- -h : displays program synopsis and usage.
