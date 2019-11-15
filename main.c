#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrice.h"
#include "produit.h"

int main(){

  char input[] = "cursusAnonyme.csv";
  clock_t t1, t2, t3, t4, t5, t6;
  float temps, temps2, temps3;

  t1 = clock();
  MATRICE matrice = fichier_en_matrice(input); // O(n log n) n = nbr lignes
  t2 = clock();

  t3 = clock();
  MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments
  t4 = clock();

  t5 = clock();
  statistique(matrice);
  t6 = clock();

   /*-----------------------------------------------------------------*/
   /* Points 3 */


   // int *vecteur1 = malloc(sizeof(int)* matrice.nbrColonnes);
   // if(!vecteur1) {
   //    fprintf(stderr, "Erreur lors de l'allocation!\n");
   //    return 1;
   // }
   //
   // /* Remplir le vecteur de 1 */
   // for(size_t k = 0; k < matrice.nbrColonnes; ++k)
   //    vecteur1[k] = 1;
   // int *resultat =
   //    matrice_vecteurs_dense(&matrice, vecteur1, matrice.nbrColonnes) ;
   //
   // /* Utilisons notre disctionnaire */
   //
   // printf("Nombre d'étudiants qui suivent le cours de:\n");
   // for(size_t k = 0; k < matrice.nbrLignes; ++k)
   //    printf("%s:  %d\n", matrice.fichier.coursDif[k], resultat[k]);
   //
   //
   //
   // free(vecteur1);
   // free(resultat);

   /*-----------------------------------------------------------------*/


  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  temps2 = (float)(t4-t3)/CLOCKS_PER_SEC;
  temps3 = (float)(t6-t5)/CLOCKS_PER_SEC;
  printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n| durée de l'exécution = %f secondes pour la troisieme fonction\n", temps, temps2, temps3);

  destroy_matrice(&matrice);
  destroy_fichier(&matrice);
  destroy_matrice(&matriceT);

}
