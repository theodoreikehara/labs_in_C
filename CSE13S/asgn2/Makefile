CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: integrate

integrate: integrate.o mathlib.o functions.o
	$(CC) -o integrate integrate.o mathlib.o functions.o -lm

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c

clean:
	rm -f integrate mathlib functions *.o

format:
	clang-format -i -style=file integrate.c mathlib.c
