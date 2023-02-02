CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting

sorting: sorting.o stats.o insert.o quick.o heap.o batcher.o
	$(CC) -o sorting sorting.o stats.o insert.o quick.o heap.o batcher.o -lm
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
