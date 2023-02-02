CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: identify

identify: identify.o bv.o bf.o speck.o node.o ht.o pq.o text.o parser.o
	$(CC) -o identify identify.o bv.o bf.o speck.o node.o ht.o pq.o text.o parser.o -lm
identify.o: identify.c bv.c bf.c speck.c node.c ht.c pq.c text.c parser.c
	$(CC) $(CFLAGS) -c identify.c bv.c bf.c speck.c node.c ht.c pq.c text.c parser.c

clean:
	rm -f *.o
	rm -f identify

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
