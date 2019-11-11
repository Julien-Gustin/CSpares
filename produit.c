#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include "produit.h"

int *matrice_vecteurs_dense(MATRICE *s, int *v, const size_t N) {
   assert(s && v);

   /* N est la taille de V */
   if(N != s->nbrColonnes) {
      fprintf(stderr, "La matrice et ce vecteur ne peuvent être "
      "multiplier.\n");
      return NULL;
   }

   /* Alloue le tableau Z donc le resultats */
   /* On sait que nbreligne de V = nbre Colonne de s = taille Z*/
   int *z = calloc(s->nbrLignes, sizeof(int));
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

   for(size_t i = 0; i < s->nbrColonnes ; ++i) {
      /* Calcule le nombres d'éléments dans la collone i */
      if(i < s->nbrColonnes -1)
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
