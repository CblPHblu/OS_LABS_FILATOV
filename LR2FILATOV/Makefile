CC = gcc
CFLAGS = -c -Wall
FINALFLAGS = -pthread -o

all: main

main: main.o bitonic.o
	$(CC) main.o bitonic.o $(FINALFLAGS) main
main.o: main.c bitonic.h
	$(CC) $(CFLAGS) main.c
bitonic.o: bitonic.c bitonic.h
	$(CC) $(CFLAGS) bitonic.c
clean:
	rm -r *.o main