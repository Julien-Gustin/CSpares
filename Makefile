###
## Makefile skeleton
## INFO0030: Projet 2
##
###

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -O3 -g
LDFLAGS =  -lm
LD=gcc

# Files
EXEC_WILCOXON=main
MODULES_WILCOXON=main.c matrice.c MergeSort.c vecteur.c statistique.c
OBJECTS_WILCOXON=main.o matrice.o MergeSort.o vecteur.o statistique.o


EXEC_ALL=main

## Rules

############# WILCOXON #############

main: $(OBJECTS_WILCOXON)
	$(LD) -o $(EXEC_WILCOXON) $(OBJECTS_WILCOXON)  $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

matrice.o: matrice.c
	$(CC) -c matrice.c -o matrice.o $(CFLAGS)

MergeSort.o: MergeSort.c
	$(CC) -c MergeSort.c -o MergeSort.o $(CFLAGS)

vecteur.o: vecteur.c
	$(CC) -c vecteur.c -o vecteur.o $(CFLAGS)

statistique.o: statistique.c
	$(CC) -c statistique.c -o statistique.o $(CFLAGS)

c:	$(EXEC_ALL)
	valgrind --leak-check=full ./$(EXEC_ALL)

clean:
	rm -f *.o $(EXEC_ALL) *~
