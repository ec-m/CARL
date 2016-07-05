CC=clang
CFLAGS=-Wall -std=c99
DEBUG=-O0 -ggdb3
RELEASE=-03

new: clean all

all:	bdd_utils.o bdd.o
	$(CC) $(CFLAGS) $(DEBUG) bdd_utils.o bdd.o -o bdd

bdd_utils.o: bdd_utils.c bdd_utils.h
	$(CC) $(CFLAGS) $(DEBUG) -c bdd_utils.c

bdd.o: bdd.c
	$(CC) $(CFLAGS) $(DEBUG) -c bdd.c

clean:
	rm -rf *.o
	rm -rf bdd
