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
  MATRICE matriceT = transposee_matrice(matrice); // O(n) n = nombres d'éléments

  t3 = clock();
  //statistique(matrice);
  t4 = clock();

  t5 = clock();
  //MATRICE c = produit_matrice_creuses(&matrice, &matriceT);
  etudiant_commun_cours(matrice, matriceT);
  cours_commun_etudiant(matrice, matriceT);
  t6 = clock();


  /*------------------------------------------------------------------*/
  /* Points 7 */
  // MATRICE *a = malloc(sizeof(MATRICE));
  // a->P = malloc(sizeof(unsigned)*4);
  // a->I = malloc(sizeof(unsigned)*8);
  // a->X = malloc(sizeof(unsigned)*8);
  //
  // a->P[0]= 0;
  // a->P[1]= 2;
  // a->P[2]= 5;
  // a->P[3]= 6;
  //
  // a->I[0]= 0;
  // a->I[1]= 2;
  // a->I[2]= 0;
  // a->I[3]= 1;
  // a->I[4]= 3;
  // a->I[5]= 0;
  // a->I[6]= 2;
  // a->I[7]= 3;
  //
  // a->X[0]= 1;
  // a->X[1]= 3;
  // a->X[2]= 2;
  // a->X[3]= 1;
  // a->X[4]= 1;
  // a->X[5]= 2;
  // a->X[6]= 4;
  // a->X[7]= 3;
  //
  // a->nz = 8;
  // a->nbrColonnes = 4;
  // a->nbrLignes = 4;
  //
  // MATRICE *b = malloc(sizeof(MATRICE));
  // b->P = malloc(sizeof(unsigned)*2);
  // b->I = malloc(sizeof(unsigned)*4);
  // b->X = malloc(sizeof(unsigned)*4);
  //
  // b->P[0]= 0;
  // b->P[1]= 2;
  //
  // b->I[0]= 0;
  // b->I[1]= 2;
  // b->I[2]= 1;
  // b->I[3]= 3;
  //
  // b->X[0]= 1;
  // b->X[1]= 2;
  // b->X[2]= 3;
  // b->X[3]= 4;
  //
  //
  // b->nz = 4;
  // b->nbrColonnes = 2;
  // b->nbrLignes = 4;
  //
  // MATRICE c = produit_matrice_creuses(a, b);
  //
  // for(size_t i = 0; i < c.nz; i++){
  //   printf("i: %d x: %d\n", c.I[i], c.X[i]);
  // }
  //
  // for(size_t i = 0; i < c.nbrColonnes; i++)
  //   printf("p: %d\n", c.P[i]);
  //
  //
  // free(b);
  // free(a);
  // return 0;

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
  printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n | durée de l'exécution = %f secondes pour la troisieme fonction\n", temps, temps2, temps3);

  destroy_matrice(&matrice);
  destroy_fichier(&matrice);
  destroy_matrice(&matriceT);

}
