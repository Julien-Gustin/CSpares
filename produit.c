#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

/* Structure de test */
// typedef struct {
//    size_t nbreEtudiants;
//    unsigned int *i;
//    unsigned int *x;
//    unsigned int *p;
//    size_t nz;
// }MATRICE;


 // Fait le produit d'une matrice creuse et d'un vecteur dense
 // s est la structure qui représente la matrice
 // v est le vecteur dense (je suppose que se sont des entiers)
 // Renvoie un vecteur z qui est le resultat qu'on devra free()
int *matrice_vecteurs_dense(MATRICE *s, int *v, const size_t nbreLigneV) {
   assert(s && v);

   if(nbreLigneV != s->nbreEtudiants) {
      fprintf(stderr, "La matrice et ce vecteur ne peuvent être "
      "multiplier.\n");
      return NULL;
   }

   /* Alloue le tableau Z donc le resultats */
   /* On sait que nbreligne de V = nbre Colonne de s = taille Z*/
   int *z = calloc(nbreLigneV, sizeof(int));
   if(!z) {
      fprintf(stderr, "Erreur d'allocation!\n");
      return NULL;
   }


   /* nbreElements dans une collone */
   size_t nbreElements = 0;
   /* compteur du tableau A.i[] */
   size_t j = 0;

   /* Compteur dans le vecteur V */
   size_t k = 0;

   for(size_t i = 0; i < s->nbreEtudiants ; ++i) {
      /* Calcule le nombres d'éléments dans la collone i */
      if(i < s->nbreEtudiants -1)
         nbreElements = s->P[i+1] - s->P[i] ;
      else // Derniere collone
         nbreElements = s->nz - s->P[i] ;

      /* Parcours tous les éléments d'une collone */
      nbreElements += j;
      for(; j < nbreElements; ++j) {
         z[s->I[j]] += s->X[j] * v[k]; // Multiplications des composantes
      }
      ++k; // Car sa veut dire qu'on change de colone dans A.x[]
   }

   return z;

}

/* Fonction main qui test avec le vecteur et la matrice du cours */
//
// int main(void) {
//    MATRICE *s = malloc(sizeof(MATRICE));
//    if(!s)
//       return 1;
//
//    s->i = malloc(sizeof(unsigned int)*8);
//    s->x = malloc(sizeof(unsigned int)*8);
//    if(!s->x || !s->i)
//       return 1;
//
//    s->p = malloc(sizeof(unsigned int) *3);
//    if(!s->p)
//       return 1;
//
//
//    s->nbreEtudiants = 3;
//    s->nz = 8;
//
//    int v[] = {1, 2, 3};
//
//    int nbreLigneV = sizeof(v) / sizeof(v[0]);
//
//    unsigned int *tmp= s->p;
//    tmp[0]= 0;
//    tmp[1]= 3;
//    tmp[2]= 5;
//
//
//    tmp = s->i;
//    tmp[0]= 0;
//    tmp[1]= 1;
//    tmp[2]= 2;
//    tmp[3]= 0;
//    tmp[4]= 2;
//    tmp[5]= 0;
//    tmp[6]= 1;
//    tmp[7]= 2;
//
//    tmp = s->x;
//    tmp[0]= 3;
//    tmp[1]= 4;
//    tmp[2]= 5;
//    tmp[3]= 1;
//    tmp[4]= 2;
//    tmp[5]= 4;
//    tmp[6]= -1;
//    tmp[7]= 2;
//
//    int *z =matrice_vecteurs_dense(s, v, nbreLigneV);
//    if(!z)
//       return 1;
//
//    printf("[");
//
//    for(size_t k =0; k < 3; ++k)
//       printf("%d ", z[k]);
//    printf("]\n");
//
//    free(s->i);
//    free(s->x);
//    free(s->p);
//    free(s);
//    free(z);
//    return 0;
// }
