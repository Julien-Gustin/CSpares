#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "matrice.h"
#include "vecteur.h"

void destroy_vecteur(VECTEUR *vecteur){
  free(vecteur->I);
  free(vecteur->X);
  if(vecteur->Xtmp != NULL)
    free(vecteur->Xtmp);
}

VECTEUR mult_matrice_vecteurs_creux(MATRICE matrice, VECTEUR vecteur){
  unsigned int *X = vecteur.Xtmp; //contiendra les valeurs des éléments à leurs lignes respectives
  VECTEUR z;
  z.sommeTot = 0;

  for(size_t i = 0; i < vecteur.nbrNonZero; i++){ // remplis X[] tel que l'indice de la case = lignes de z.I[] ou z.X[] sont les résultats
    if(vecteur.I[i] < matrice.nbrColonnes-1){
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.P[vecteur.I[i]+1]; j++)
        X[matrice.I[j]] += vecteur.X[i] * matrice.X[j];
    }

    else{
      for(size_t j = matrice.P[vecteur.I[i]]; j < matrice.nz; j++)
        X[matrice.I[j]] += vecteur.X[i] * matrice.X[j];
    }
  }

  size_t k = 0; // compteur;

  for(size_t i = 0; i < matrice.nbrLignes; i++){ // k = nombres de non zero
    if(X[i] != 0)
      k++;

  }

  z.I = malloc(sizeof(unsigned int)*k);
  z.X = malloc(sizeof(unsigned int)*k);
  z.Xtmp = NULL;

  k = 0;

  for(size_t i = 0; i < matrice.nbrLignes; i++){
    if(X[i] != 0){
      z.I[k] = i;
      z.X[k] = X[i];
      z.sommeTot += X[i];
      X[i] = 0;
      k++;
    }
  }

  z.nbrNonZero = k;
  return z;
}

/* O(s->nz) */
double *matrice_vecteurs_dense(MATRICE *s, double *v, const size_t N) {
   assert(s && v);

   /* N est la taille de V */
   if(N != s->nbrColonnes) {
      fprintf(stderr, "La matrice et ce vecteur ne peuvent être "
      "multiplier.\n");
      return NULL;
   }

   /* Alloue le tableau Z donc le resultats */
   /* On sait que nbreligne de V = nbre Colonne de s = taille Z*/
   double *z = calloc(s->nbrLignes, sizeof(double));
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

VECTEUR *valeur_propre(MATRICE *a) {
   /* a doit etre carré */
   if(a->nbrLignes != a->nbrColonnes) {
      printf("La valeur propre d'une matrice non carré n'existe pas\n");
      return NULL;
   }
   double norme = 0;
   double norme0 = 1;

   /* 1ier etape initialiser un vecteur random  O(n) */
   double *v = malloc(sizeof(double)*a->nbrLignes);
   if(!v) {
      printf("Erreur d'allocation\n");
      return NULL;
   }
   double *v0 = NULL;

   srand(time(NULL));

   for(size_t k = 0; k < a->nbrLignes; ++k)
      v[k] = rand();


   // permet de gerer le cas si sa ne converge pas
   const int COEF_LIMITE = 10;
   int i = 0;

   /* O(n*nz) */
   while(norme != norme0 && i < a->nbrLignes * COEF_LIMITE) {
      v0 = v;
      norme0 = norme;
      v = matrice_vecteurs_dense(a, v, a->nbrLignes);

      /* Normalisé v */
      norme = 0;
      for(size_t k = 0; k < a->nbrLignes; ++k)
         norme += v[k]*v[k];

      norme = sqrt(norme);

      for(size_t k = 0; k < a->nbrLignes; ++k)
         v[k] = v[k] / norme;
      /* fin normalisé */
      free(v0);
      ++i;
      }

      if(i == a->nbrLignes * COEF_LIMITE) {
         printf("Le vecteur n'a pas convergé\n");
         return NULL;
      }

      printf("Le vecteur propre est [");
      for(size_t k = 0; k < a->nbrLignes; ++k) {
         printf("%f ",v[k]);
      }
      printf("]\n\n");

      /* Une fois le vecteur propre de plus grand module calculer */
      /* Calcule de la valeur propre */

      double *resultat =  vecteur_matrice_dense(a, v, a->nbrLignes);
      double num = 0;
      unsigned int nonNul = 0;
      const double EPSILON = 0.000001;

      for(size_t k = 0; k < a->nbrLignes; ++k) {
         num += resultat[k] * v[k];
         if(v[k] > EPSILON) // si v[k] != 0
            ++nonNul;
      }

      VECTEUR *vPropre = malloc(sizeof(VECTEUR));
      if(!vPropre)
         return NULL;
      vPropre->I = malloc(sizeof(int)* nonNul);
      if(!vPropre->I) {
         free(vPropre);
         return 0;
      }

      vPropre->X = malloc(sizeof(int)* nonNul);
      if(!vPropre->X) {
         free(vPropre->I);
         free(vPropre);
         return 0;
      }
      vPropre->nbrNonZero = nonNul;

      double denum = 0; // denumerateur
      int j =0;
      for(size_t k = 0; k < a->nbrLignes; ++k) {
         denum += v[k] * v[k];
         if(v[k] < EPSILON) {
            vPropre->I[j] = k;
            vPropre->X[j] = v[k];
         }
      }

      vPropre->valeurPropre = num / denum;
      printf("De valeur propre de plus grands modules %lf\n",
         vPropre->valeurPropre);

      free(v);
      free(resultat);
      return vPropre;
}

double *vecteur_matrice_dense(MATRICE *s, double *v, const size_t N) {
   assert(s && v);

   /* N est la taille de V */
   if(N != s->nbrLignes) {
      fprintf(stderr, "La matrice et ce vecteur ne peuvent être "
      "multiplier.\n");
      return NULL;
   }

   /* Alloue le tableau Z donc le resultats */
   /* On sait que nbreligne de V = nbre Colonne de s = taille Z*/
   double *z = calloc(s->nbrColonnes, sizeof(double));
   if(!z) {
      fprintf(stderr, "Erreur d'allocation!\n");
      return NULL;
   }

   /* nbreElements dans une collone */
   size_t nbreElements = 0;
   /* compteur du tableau A.i[] */
   size_t j = 0;

   for(size_t i = 0; i < s->nbrColonnes ; ++i) {
      /* Calcule le nombres d'éléments dans la collone i */
      if(i < s->nbrColonnes -1)
         nbreElements = s->P[i+1] - s->P[i] ;
      else // Derniere collone
         nbreElements = s->nz - s->P[i] ;

      /* Parcours tous les éléments d'une collone */
      nbreElements += j;
      for(; j < nbreElements && j < s->nz; ++j) {
         z[i] += s->X[j] * v[s->I[j]]; // Multiplications des composantes
      }
   }

   return z;
}
