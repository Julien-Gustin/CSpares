###
## Makefile skeleton
## INFO0030: Projet 2
##
###

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
LD=gcc

# Files
EXEC_WILCOXON=main
MODULES_WILCOXON=main.c matrice.c MergeSort.c
OBJECTS_WILCOXON=main.o matrice.o MergeSort.o


EXEC_ALL=main

## Rules

############# WILCOXON #############

main: $(OBJECTS_WILCOXON)
	$(LD) -o $(EXEC_WILCOXON) $(OBJECTS_WILCOXON)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

matrice.o: matrice.c
	$(CC) -c matrice.c -o matrice.o $(CFLAGS)

MergeSort.o: MergeSort.c
	$(CC) -c MergeSort.c -o MergeSort.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC_ALL) *~
