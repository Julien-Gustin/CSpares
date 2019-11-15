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



 /* test de  mult_matrice_vecteurs_creux */

  // MATRICE test;
  // test.nz = 8;
  // test.P = malloc(sizeof(unsigned int)*4);
  // test.I = malloc(sizeof(unsigned int)*test.nz);
  // test.X = malloc(sizeof(unsigned int)*test.nz);
  // test.nbrColonnes = 4;
  //
  // test.P[0] = 0;
  // test.P[1] = 2;
  // test.P[2] = 5;
  // test.P[3] = 6;
  //
  //
  // test.I[0] = 0;
  // test.I[1] = 2;
  // test.I[2] = 0;
  // test.I[3] = 1;
  // test.I[4] = 3;
  // test.I[5] = 0;
  // test.I[6] = 2;
  // test.I[7] = 3;
  //
  // test.X[0] = 1;
  // test.X[1] = 3;
  // test.X[2] = 2;
  // test.X[3] = 1;
  // test.X[4] = 1;
  // test.X[5] = 2;
  // test.X[6] = 4;
  // test.X[7] = 3;
  //
  // int v[4] = {1, 0, 2, 3};
  //
  // VECTEUR vecteur;
  // vecteur.nbrNonZero = 0;
  //
  // for(size_t i = 0; i < test.nbrColonnes; i++){ //Compte le nombre de non zero, cad quand v[i] n'est pas égale à 0
  //   if(v[i] != 0)
  //     vecteur.nbrNonZero++;
  // }
  //
  // vecteur.I = malloc(sizeof(unsigned int)*vecteur.nbrNonZero); // crée un vecteur creux de taille du nombres de non zero, (ligne)
  // vecteur.X = malloc(sizeof(int) *vecteur.nbrNonZero);
  //
  // size_t k = 0;
  // for(size_t i = 0; i < test.nbrColonnes; i++){ //remplit le vecteur avec les données
  //   if(v[i] != 0){
  //
  //     vecteur.I[k] = i;
  //     vecteur.X[k] = v[i];
  //     k++;
  //
  //   }
  //
  // }
  // //int z[5];
  //
  // VECTEUR z = mult_matrice_vecteurs_creux(test, vecteur);
  //
  // for(size_t i = 0; i < z.nbrNonZero; i++)
  //   printf("%d\n", z.X[i]);
  //
  // printf("sommes : %d\n", z.sommeTot);

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
/*
  free(matrice.fichier.matricules);
  free(matrice.fichier.cours);
  free(matrice.P);
  free(matrice.I);
  free(matrice.fichier.coursDif);
  free(matrice.X);*/

  // free(matriceT.I);
  // free(matriceT.P);

}
