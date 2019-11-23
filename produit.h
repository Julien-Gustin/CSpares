#ifndef __PRODUIT__
#define __PRODUIT__

#include "matrice.h"

/* Renvoie un pointeur sur le resultats */
/* Ne pas oublier de free le vecteur ensuite */
double *matrice_vecteurs_dense(MATRICE *s, double *v, const size_t N);

double *vecteur_matrice_dense(MATRICE *s, double *v, const size_t N);



typedef struct element{
   unsigned int ligne; // LA valeurs de la ligne
   unsigned int colonne;
   struct element *next;

}ELEMENTS;

ELEMENTS *produit_matrice(const MATRICE *A, const MATRICE *B);


ELEMENTS *cree_element(unsigned ligne, unsigned colonne);

void supprimer_elements(ELEMENTS *s, ELEMENTS *d);

void ajouter_element(ELEMENTS *s, ELEMENTS *f);
double *valeur_propre(MATRICE *a);

#endif
