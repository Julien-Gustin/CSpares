#include <assert.h>

#include <stdio.h>
#include <stdlib.h>


 // Fait le produit d'une matrice creuse et d'un vecteur dense
 // s est la structure qui représente la matrice
 // v est le vecteur dense (je suppose que se sont des entiers)

int *matrice_vecteurs_dense(MATRICE *s, int *v) {
   assert(s && v);

   /* Determiner le nombre de ligne de v */
   size_t nbreLigneV = sizeof(v) / sizeof(v[0])
   if(nbreLigneV != s->nbreEtudiants) {
      fprintf(stderr, "La matrice et ce vecteur ne peuvent être"
      "multiplier.\n");
      return NULL;
   }

   /* Alloue le tableau Z donc le resultats */
   /* On sait que nbreligne de V = nbre Colonne de s = taille Z*/
   int *z = calloc(nbreLigneV, sizeof(unsigned int));
   if(!z) {
      fprintf(stderr, "Erreur d'allocation!\n");
      return NULL;
   }


   /* nbreElements dans une collone */
   size_t nbreElements = 0;
   /* compteur du tableau A.i[] */
   size_t j = 0;

   for(size_t i = 0; i < s->nbreEtudiants ; ++i) {
      /* Calcule le nombres d'éléments dans la collone i */
      if(i < s->nbreEtudiants -1)
         nbreElements = s->i[i+1] - s->i[i] ;
      else // Derniere collone
         nbreElements = s->nz - s->i[i] ;

      /* Gardien de boucle */
      nbreElements += j;
      for(; j < nbreElements; ++j) {
         z[j]= 
      }


   }

}
