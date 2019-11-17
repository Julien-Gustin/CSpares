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

  /*------------------------------------------------------------------*/
  /* Points 7 */
  // MATRICE *a = malloc(sizeof(MATRICE));
  // a->P = malloc(sizeof(unsigned)*4);
  // a->I = malloc(sizeof(unsigned)*7);
  // a->X = malloc(sizeof(unsigned)*7);
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
  // a->nz = 8;
  //
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
  // b->nz = 4;
  // b->nbrColonnes = 2;
  // b->nbrLignes = 4;
  //
  // ELEMENTS *s = produit_matrice(a, b);
  // // ELEMENTS *s = NULL ;
  // // ajouter_element(s, cree_element(15, 5));
  //
  // /* Passe la sentinelle */
  // s = s->next;
  // while(s) {
  //     printf("ligneB %u  ColloneA %u\n", s->ligne, s->colonne);
  //     s = s->next;
  //  }
  //
  //
  //
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
  printf(" | durée de l'exécution = %f secondes pour la première fonction\n | durée de l'exécution = %f secondes pour la deuxième fonction\n| durée de l'exécution = %f secondes pour la troisieme fonction\n", temps, temps2, temps3);

  destroy_matrice(&matrice);
  destroy_fichier(&matrice);
  destroy_matrice(&matriceT);

}
