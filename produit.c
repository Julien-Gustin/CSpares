#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include "produit.h"


/* Liste definition */





ELEMENTS *cree_element(unsigned ligne, unsigned colonne) {
   ELEMENTS *s = malloc(sizeof(ELEMENTS));
   if(!s)
      return NULL;
   s->ligne = ligne;
   s->colonne = colonne;
   s->next = NULL;
   return s;
}
/* Supprimer element */
void supprimer_elements(ELEMENTS *s, ELEMENTS *d) {
   if(!s || !d)
      return;

   /* 1ier element */
   if(s == d) {
      s = s->next;
      free(d);
      return;
   }

   /* Cherche elements */
   while(s->next != d && s->next)
      s = s->next;

   /* Element n existe pas */
   if(!s->next) {
      printf("Elements n exite pas\n");
      return;
   }

   /* On a trouve l elements */
   s->next = s->next->next;
   free(d);

}
/* Ajoute a la fin */
void ajouter_element(ELEMENTS *s, ELEMENTS *f) {
   if(!s) { /* Liste vide */
      s = f;
      return;
   }
   while(s->next)
      s = s->next;    /* Ici on est a la fin de la liste */
   s->next = f;
}



/* Liste definition */




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
/* A-> premiere && B-> deuxieme */
/* Le fais que se sont des constantes garantie qu'on ne les modifies pas */
ELEMENTS *produit_matrice(const MATRICE *A, const MATRICE *B) {
   assert(A && B);

   /* Testons si A*B est possible */
   if(A->nbrColonnes != B->nbrLignes) {
      printf("Multiplication matricielle impossible\n");
      return NULL;
   }

   /* Alloue le resultats dans C */
   MATRICE *c = malloc(sizeof(MATRICE));
   if(!c) {
      fprintf(stderr, "Erreur dans produit matrice\n");
      exit(EXIT_FAILURE);
   }

   /* Alloue le nombre de collone*/
   /* nbreCollone C = nbreCollone B*/
   c->P = malloc(sizeof(unsigned int)* B->nbrColonnes);
   if(!c->P) {
      fprintf(stderr, "Erreur dans produit matrice\n");
      exit(EXIT_FAILURE);
   }

   /* 1) trouvons les non nul de c */
   /* Sentinelle */
   ELEMENTS *s = malloc(sizeof(ELEMENTS));
   if(!s)
      return NULL;
   s->next = NULL;
   size_t j = 0;
   size_t nbreElements = 0, nbreElementsA = 0;
   for(size_t i = 0; i < B->nz; ++i) {
      if(i < A->nbrColonnes -1)
         nbreElementsA = A->P[B->I[i]+1] - A->P[B->I[i]] ;
      else // Derniere collone
         nbreElementsA = A->nz - A->P[B->I[i]] ;

      for(; j < nbreElementsA; ++j)
         ajouter_element(s, cree_element(A->I[A->P[B->I[i]]+j], B->I[i]));
         // Donne la ligne des elements non nul de c
      j = 0;


   }

   return s;

}
