CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: life

life: life.o universe.o
	$(CC) -o life life.o universe.o -lm -lncurses
life.o: life.c
	$(CC) $(CFLAGS) -c life.c

clean:
	rm -f life *.o

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
