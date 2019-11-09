#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrice.h"

int main(){

  char input[] = "cursusAnonyme.csv";
  clock_t t1, t2;
  float temps;

  t1 = clock();
  MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
  t2 = clock();

  MATRICE matriceT = transposee_matrice(matrice);

  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  printf(" | durée de l'exécution = %f secondes\n", temps);

  free(matrice.matricules);
  free(matrice.cours);
  free(matrice.P);
  free(matrice.I);
  free(matrice.coursDif);
  free(matrice.X);
}
