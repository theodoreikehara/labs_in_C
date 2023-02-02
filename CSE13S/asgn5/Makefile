CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: clean encrypt decrypt keygen

# numtheorytest: numtheorytest.o numtheory.o randstate.o
# 	$(CC) -o numtheorytest numtheorytest.o numtheory.o randstate.o $(LFLAGS)
# numtheorytest.o: numtheorytest.c numtheory.c randstate.c
# 	$(CC) $(CFLAGS) -c numtheorytest.c numtheory.c randstate.c
#
#rsa: rsa.o numtheory.o randstate.o
#	$(CC) -o rsa rsa.o numtheory.o randstate.o $(LFLAGS)
#rsa.o: rsa.c numtheory.c randstate.c
#	$(CC) $(CFLAGS) -c rsa.c numtheory.c randstate.c
#
#
encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o encrypt encrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)
encrypt.o: encrypt.c numtheory.c randstate.c rsa.c
	$(CC) $(CFLAGS) -c encrypt.c numtheory.c randstate.c rsa.c

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) -o decrypt decrypt.o numtheory.o randstate.o rsa.o $(LFLAGS)
decrypt.o: decrypt.c numtheory.c randstate.c rsa.c
	$(CC) $(CFLAGS) -c decrypt.c numtheory.c randstate.c rsa.c

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) -o keygen keygen.o numtheory.o randstate.o rsa.o $(LFLAGS)
keygen.o: keygen.c numtheory.c randstate.c rsa.c
	$(CC) $(CFLAGS) -c keygen.c numtheory.c randstate.c rsa.c

clean:
	rm -f *.o
	rm -f encrypt
	rm -f decrypt
	rm -f keygen

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
