#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrice.h"

int main(){

  char input[] = "cursusAnonyme.csv";
  clock_t t1, t2, t3, t4;
  float temps, temps2;

  t1 = clock();
  MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
  t2 = clock();

  t3 = clock();
  MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
  t4 = clock();

  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  temps2 = (float)(t4-t3)/CLOCKS_PER_SEC;
  printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n", temps, temps2);

  free(matrice.fichier.matricules);
  free(matrice.fichier.cours);
  free(matrice.P);
  free(matrice.I);
  free(matrice.fichier.coursDif);
  free(matrice.X);

  free(matriceT.I);
  free(matriceT.P);
}
