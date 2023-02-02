CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: encode decode

encode: encode.o stack.o pq.o code.o huffman.o node.o io.o
	$(CC) -o encode encode.o stack.o pq.o code.o huffman.o node.o io.o -lm
encode.o: encode.c stack.c pq.c code.c huffman.c node.c io.c
	$(CC) $(CFLAGS) -c encode.c stack.c pq.c code.c huffman.c node.c io.c

decode: decode.o stack.o pq.o code.o huffman.o node.o io.o
	$(CC) -o decode decode.o stack.o pq.o code.o huffman.o node.o io.o -lm
decode.o: decode.c stack.c pq.c code.c huffman.c node.c io.c
	$(CC) $(CFLAGS) -c decode.c stack.c pq.c code.c huffman.c node.c io.c

clean:
	rm -f *.o
	rm -f encode
	rm -f decode

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
