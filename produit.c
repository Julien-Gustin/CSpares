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

int *valeur_propre(MATRICE *a) {
   /* a-> doit etre carré */
   if(a->nbrLignes != a->nbrColonnes) {
      printf("La valeur propre d'une matrice non carré n'existe pas\n");
      return NULL;
   }


   /* 1ier etape initialiser un vecteur random  O(n) */
   VECTEUR *v = malloc(sizeof(VECTEUR));
   if(!v)
      return NULL;
   v->I = malloc(sizeof(int));
   v->X = malloc(sizeof(int));




   /* Simmule le vecteur 1 0 0 */
   v->I[0] = 0;
   v->X[0] = 1;
   v->nbrNonZero = 1;
   v->sommeTot = 1;

   /* 2ieme étape, la mutliplication */
   for(size_t k = 1; k <= 5; ++k) {
      *v = mult_matrice_vecteurs_creux(*a, *v);
      printf("Somme elements = %u\n", v->sommeTot);
   }



   return NULL;
}
  /* Points 8 */
// 
//   MATRICE *a = malloc(sizeof(MATRICE));
//   if(!a)
//    return 1;
//
//    a->P = malloc(sizeof(int)*3);
//    a->I =  malloc(sizeof(int)*9);
//    a->X =  malloc(sizeof(int)*9);
//
//    a->nz = 9;
//
//    a->P[0] = 0;
//    a->P[1] = 3;
//    a->P[2] = 6;
//
//    a->I[0] = 0;
//    a->I[1] = 1;
//    a->I[2] = 2;
//    a->I[3] = 0;
//    a->I[4] = 1;
//    a->I[5] = 2;
//    a->I[6] = 0;
//    a->I[7] = 1;
//    a->I[8] = 2;
//
//    a->X[0] = 4;
//    a->X[1] = 2;
//    a->X[2] = 2;
//    a->X[3] = 3;
//    a->X[4] = 4;
//    a->X[5] = 3;
//    a->X[6] = -3;
//    a->X[7] = -2;
//    a->X[8] = -1;
//
//
//   a = valeur_propre(a);
//
//
//   return 0;
//
//
// /* Points 8 */
//
// MATRICE *a = malloc(sizeof(MATRICE));
// if(!a)
//  return 1;
//
//  a->P = malloc(sizeof(int)*3);
//  a->I =  malloc(sizeof(int)*9);
//  a->X =  malloc(sizeof(int)*9);
//
//  a->nz = 9;
//
//  a->P[0] = 0;
//  a->P[1] = 3;
//  a->P[2] = 6;
//
//  a->I[0] = 0;
//  a->I[1] = 1;
//  a->I[2] = 2;
//  a->I[3] = 0;
//  a->I[4] = 1;
//  a->I[5] = 2;
//  a->I[6] = 0;
//  a->I[7] = 1;
//  a->I[8] = 2;
//
//  a->X[0] = 4;
//  a->X[1] = 2;
//  a->X[2] = 2;
//  a->X[3] = 3;
//  a->X[4] = 4;
//  a->X[5] = 3;
//  a->X[6] = -3;
//  a->X[7] = -2;
//  a->X[8] = -1;
//
//
// a = valeur_propre(a);
//
//
// return 0;
