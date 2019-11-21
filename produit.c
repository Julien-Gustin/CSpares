#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "produit.h"
#include <time.h>


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




int *matrice_vecteurs_dense(MATRICE *s, int *v, const size_t N, double *sommeTot) {
   assert(s && v);

   *sommeTot = 0;
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
      (*sommeTot) += z[i]* z[i];

      ++k; // Car sa veut dire qu'on change de colone dans A.x[]
   }

   return z;

}

static int sont_different(int *a, int *b, const size_t N) {
   for(size_t k= 0; k < N; ++k) {
      if(a[k] != b[k])
         return 1;
   }
   return 0;
}



int *valeur_propre(MATRICE *a) {
   /* a-> doit etre carré */
   if(a->nbrLignes != a->nbrColonnes) {
      printf("La valeur propre d'une matrice non carré n'existe pas\n");
      return NULL;
   }
   double norme = 0;
   double norme0 = 1;

   /* 1ier etape initialiser un vecteur random  O(n) */
   int *v = malloc(sizeof(int)*a->nbrLignes);
   int *v0 = NULL;

   srand(time(NULL));

   for(size_t k = 0; k < a->nbrLignes; ++k)
      v[k] = rand();



   while(norme != norme0 || sont_different(v, v0, a->nbrLignes)) {
      v0 = v;
      norme0 = norme;
      v = matrice_vecteurs_dense(a, v, a->nbrLignes, &norme);

      // for(size_t k = 0; k < a->nbrLignes; ++k)
      //    printf("%d ",v[k]);
      // printf("\n\n");

      norme = sqrt(norme);

      // printf("%lf\n", norme);

      for(size_t k = 0; k < a->nbrLignes; ++k){
         v[k] = ceil((float) v[k] / norme);
      }
      // free(v0);
      }

      // for(size_t k = 0; k < a->nbrLignes; ++k)
      //    printf("%d ",v[k]);
      // printf("\n\n");

      return v;

}
