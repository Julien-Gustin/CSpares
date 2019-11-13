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
static void MergeSort(unsigned int* array, unsigned int *cours, size_t p, size_t length);

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
static void Merge(unsigned int* array, unsigned int *cours, size_t p, size_t q, size_t length);

static void Merge(unsigned int* array, unsigned int *cours, size_t p, size_t q, size_t length){
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

  unsigned int *L2 = malloc(sizeof(unsigned int) *(n1));
  if(L2 == NULL)
    return;

  unsigned int *R2 = malloc(sizeof(unsigned int) *(n2));
  if(R2 == NULL)
    return;

  for(size_t i = 0; i < n1; i++) // copie une partie du tableau tel que : L[] = array[p..p+n1]
    L[i] = array[p+i];

  for(size_t j = 0; j < n2; j++) // copie une partie du tableau tel que : R[] = array[q+1..q+n2+1]
    R[j] = array[q+j+1];

  for(size_t i = 0; i < n1; i++)
    L2[i] = cours[p+i];

  for(size_t j = 0; j < n2; j++)
    R2[j] = cours[q+j+1];

  L[n1] = INT_MAX; // Parce que rien n'est plus grand que INT_MAX
  R[n2] = INT_MAX;

  size_t i = 0;
  size_t j = 0;

  for(unsigned long k = p; k <= length; k++){ // Fusion
    if(L[i] <= R[j]){
      array[k] = L[i];
      cours[k] = L2[i];
      i++;
    }
    else{
      array[k] = R[j];
      cours[k] = R2[j];
      j++;
    }
  }

  free(L);
  free(R);
  free(L2);
  free(R2);
}

static void Merge2(unsigned int* array, char (*cours)[MAX], size_t p, size_t q, size_t length);

static void Merge2(unsigned int* array, char (*cours)[MAX], size_t p, size_t q, size_t length){
  assert(p <= q && q < length); // On ne peut pas avoir de tableau vide
  assert(length > 0);

  size_t n1 = q - p + 1;
  size_t n2 = length - q;
  unsigned int *L = malloc(sizeof(unsigned int) *(n1)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(L == NULL)
    return;

  unsigned int *R = malloc(sizeof(unsigned int) *(n2)); // la dernière case du tableau est réservé pour le dernier entier possible
  if(R == NULL)
    return;

  char (*L2)[MAX] = malloc(sizeof(char[MAX]) *(n1+1));
  if(L2 == NULL)
    return;

  char (*R2)[MAX] = malloc(sizeof(char[MAX]) *(n2+1));
  if(R2 == NULL)
    return;

  for(size_t i = 0; i < n1; i++) // copie une partie du tableau tel que : L[] = array[p..p+n1]
    L[i] = array[p+i];

  for(size_t j = 0; j < n2; j++) // copie une partie du tableau tel que : R[] = array[q+1..q+n2+1]
    R[j] = array[q+j+1];

  for(size_t i = 0; i < n1; i++)
    strcpy(L2[i], cours[p+i]);

  for(size_t j = 0; j < n2; j++)
    strcpy(R2[j], cours[q+j+1]);

  for(size_t i = 0; i < MAX; i++){
    L2[n1][i] = CHAR_MAX; // Parce que rien n'est plus grand que INT_MAX
    R2[n2][i] = CHAR_MAX;

}

  size_t i = 0;
  size_t j = 0;

  for(unsigned long k = p; k <= length; k++){ // Fusion
    if(strcmp(L2[i],R2[j]) <= 0){
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

static void Merge3(unsigned int* array, size_t p, size_t q, size_t length);

static void Merge3(unsigned int* array, size_t p, size_t q, size_t length){
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

  for(size_t i = 0; i < n1; i++) // copie une partie du tableau tel que : L[] = array[p..p+n1]
    L[i] = array[p+i];

  for(size_t j = 0; j < n2; j++) // copie une partie du tableau tel que : R[] = array[q+1..q+n2+1]
    R[j] = array[q+j+1];

  L[n1] = INT_MAX; // Parce que rien n'est plus grand que INT_MAX
  R[n2] = INT_MAX;

  size_t i = 0;
  size_t j = 0;

  for(unsigned long k = p; k <= length; k++){ // Fusion
    if(L[i] <= R[j]){
      array[k] = L[i];
      i++;
    }
    else{
      array[k] = R[j];
      j++;
    }
  }

  free(L);
  free(R);

}

static void MergeSort3(unsigned int* array, size_t p, size_t length){

  if(p < length){
    size_t q = (length+p)/2; // Scinde le tableau en deux
    MergeSort3(array, p, q);
    MergeSort3(array, q+1, length);

    Merge3(array, p, q, length); // Fusionne deux sous tableaux déjà trié
  }
}

static void MergeSort2(unsigned int* array, char (*cours)[MAX], size_t p, size_t length){

  if(p < length){
    size_t q = (length+p)/2; // Scinde le tableau en deux
    MergeSort2(array, cours, p, q);
    MergeSort2(array, cours, q+1, length);

    Merge2(array, cours, p, q, length); // Fusionne deux sous tableaux déjà trié
  }
}

static void MergeSort(unsigned int* array, unsigned int *cours, size_t p, size_t length){

  if(p < length){
    size_t q = (length+p)/2; // Scinde le tableau en deux
    MergeSort(array, cours, p, q);
    MergeSort(array, cours, q+1, length);

    Merge(array, cours, p, q, length); // Fusionne deux sous tableaux déjà trié
  }
}

void sort(unsigned int* array, unsigned int *cours, size_t length){
  if(array == NULL || length == 0)
    return;

  MergeSort(array, cours, 0, length-1); //array[0..length-1]
  }

void sortv3(unsigned int* array, size_t length){
  if(array == NULL || length == 0)
    return;

  MergeSort3(array, 0, length-1); //array[0..length-1]
  }

void sort_string(unsigned int* array, char (*cours)[MAX], size_t length){
  if(array == NULL || length == 0)
    return;

  MergeSort2(array, cours, 0, length-1); //array[0..length-1]
  }
