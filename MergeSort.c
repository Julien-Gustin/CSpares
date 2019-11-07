/* ========================================================================= *
 * MergeSort
 * Implémentation de l'algorithme MergeSort.
 * ========================================================================= */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "Sort.h"
#include "matrice.h"

/* ------------------------------------------------------------------------- *
 * Trie un tableau d'entier.
 *
 * PARAMETRES
 * array        Le tableau à trier
 * p            l'indice du premier élément du tableau
 * length       Nombres d'éléments du tableau
 * ------------------------------------------------------------------------- */
static void MergeSort(unsigned int* array, char (*cours)[MAX], size_t p, size_t length);

/* ------------------------------------------------------------------------- *
 * Fusionne deux sous tableau en un meme tableau array[p..length]
 *
 * array[p..q] et array[q+1..length] sont triée
 *
 * PARAMETRES
 * array        Le tableau à trier
 * p            array[p..q-p+1], p <= q < length
 * q            array[q+1..length-q+1],
 * length       Nombres d'éléments du tableau (0 <= length)
 * ------------------------------------------------------------------------- */
static void Merge(unsigned int* array, char (*cours)[MAX], size_t p, size_t q, size_t length);

static void Merge(unsigned int* array, char (*cours)[MAX], size_t p, size_t q, size_t length){
  assert(p <= q && q < length); // On ne peut pas avoir de tableau vide
  assert(length > 0);

  size_t n1 = q - p + 1;
  size_t n2 = length - q;
  unsigned int *L = malloc(sizeof(unsigned int) *(n1+1)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(L == NULL)
    return;

  unsigned int *R = malloc(sizeof(unsigned int) *(n2+1)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(R == NULL)
    return;

  char (*L2)[MAX] = malloc(sizeof(char[MAX]) *(n1)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(L2 == NULL)
    return;

  char (*R2)[MAX] = malloc(sizeof(char[MAX]) *(n2)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(R2 == NULL)
    return;

  for(size_t i = 0; i < n1; i++) // copie une partie du tableau tel que : L[] = array[p..p+n1]
    L[i] = array[p+i];

  for(size_t j = 0; j < n2; j++) // copie une partie du tableau tel que : R[] = array[q+1..q+n2+1]
    R[j] = array[q+j+1];

  for(size_t i = 0; i < n1; i++){ // copie une partie du tableau tel que : L[] = array[p..p+n1]
    strcpy(L2[i], cours[p+i]);
  //  printf("[%s]", cours[p+i]);
  }

  for(size_t j = 0; j < n2; j++) // copie une partie du tableau tel que : R[] = array[q+1..q+n2+1]
    strcpy(R2[j], cours[q+j+1]);

  L[n1] = INT_MAX; // Parce que rien n'est plus grand que INT_MAX
  R[n2] = INT_MAX;

  size_t i = 0;
  size_t j = 0;

  for(unsigned long k = p; k <= length; k++){ // Fusion
    if(L[i] <= R[j]){
      array[k] = L[i];
      strcpy(cours[k], L2[i]);
      i++;
    }
    else{
      array[k] = R[j];
      strcpy(cours[k], R2[j]);
      j++;
    }
  }

  free(L);
  free(R);
  free(L2);
  free(R2);
}

static void MergeSort(unsigned int* array, char (*cours)[MAX], size_t p, size_t length){

  if(p < length){
    size_t q = (length+p)/2; // Scinde le tableau en deux
    MergeSort(array, cours, p, q);
    MergeSort(array, cours, q+1, length);

    Merge(array, cours, p, q, length); // Fusionne deux sous tableaux déjà trié
  }
}

void sort(unsigned int* array, char (*cours)[MAX], size_t length){
  if(array == NULL || length == 0)
    return;

  MergeSort(array, cours, 0, length-1); //array[0..length-1]
  }
