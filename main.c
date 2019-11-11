#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrice.h"
#include "produit.h"

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

/* TEST VECTEUR CREUX
  MATRICE test;
  test.nz = 12;
  test.P = malloc(sizeof(unsigned int)*5);
  test.I = malloc(sizeof(unsigned int)*test.nz);
  test.X = malloc(sizeof(unsigned int)*test.nz);
  test.nbrColonnes = 5;

  test.P[0] = 0;
  test.P[1] = 3;
  test.P[2] = 5;
  test.P[3] = 8;
  test.P[4] = 10;

  test.I[0] = 0;
  test.I[1] = 2;
  test.I[2] = 3;
  test.I[3] = 1;
  test.I[4] = 2;
  test.I[5] = 0;
  test.I[6] = 1;
  test.I[7] = 4;
  test.I[8] = 1;
  test.I[9] = 3;
  test.I[10] = 2;
  test.I[11] = 4;

  test.X[0] = 1;
  test.X[1] = 1;
  test.X[2] = 1;
  test.X[3] = 1;
  test.X[4] = 1;
  test.X[5] = 1;
  test.X[6] = 1;
  test.X[7] = 1;
  test.X[8] = 1;
  test.X[9] = 1;
  test.X[10] = 1;
  test.X[11] = 1;

  int v[5] = {1, 1, 2, 0, 1};
  //int z[5];

  int *z = matrice_vecteurs_creux(test, v);

  for(size_t i = 0; i < 5; i++)
    printf("%d, ", z[i]);
*/
   /*-----------------------------------------------------------------*/
   /* Points 3 */


   int *vecteur1 = malloc(sizeof(int)* matrice.nbrColonnes);
   if(!vecteur1) {
      fprintf(stderr, "Erreur lors de l'allocation!\n");
      return 1;
   }

   /* Remplir le vecteur de 1 */
   for(size_t k = 0; k < matrice.nbrColonnes; ++k)
      vecteur1[k] = 1;
   int *resultat =
      matrice_vecteurs_dense(&matrice, vecteur1, matrice.nbrColonnes) ;

   /* Utilisons notre disctionnaire */

   printf("Nombre d'étudiants qui suivent le cours de:\n");
   for(size_t k = 0; k < matrice.nbrLignes; ++k)
      printf("%s:  %d\n", matrice.fichier.coursDif[k], resultat[k]);



   free(vecteur1);
   free(resultat);

   /*-----------------------------------------------------------------*/


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
