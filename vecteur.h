#ifndef __VECTEUR__
#define __VECTEUR__

#include "matrice.h"

typedef struct vecteur_t VECTEUR;

struct vecteur_t{
  unsigned int *I; // lignes
  unsigned int *X; // valeur de la ligne
  unsigned int nbrNonZero; // nombres d'éléménts, donc taille de I
  unsigned int sommeTot; // sommes de tout les éléments

  unsigned int *Xtmp;
};


/* Renvoie un pointeur sur le resultats */
/* Ne pas oublier de free le vecteur ensuite */
double *matrice_vecteurs_dense(MATRICE *s, double *v, const size_t N);

double *vecteur_matrice_dense(MATRICE *s, double *v, const size_t N); //le quel ?

// (8) TODO DOCUMENTATION
double *valeur_propre(MATRICE *a);

/* ------------------------------------------------------------------------- *
 * libere le contenu d'un vecteur
 *
 * PARAMETRES
 * vecteur        pointeur vers un vecteur creux en structure
 * ------------------------------------------------------------------------- */
void destroy_vecteur(VECTEUR *vecteur);

/* ------------------------------------------------------------------------- *
 * (5) Multiplie une matrice creuse avec un vecteur creux et renvois cette multiplication
 *
 * PARAMETRES
 * matrice        matrice creuse en structure
 * vecteur        vecteur creux
 *
 * RETURN
 * vecteur creux
 * ------------------------------------------------------------------------- */
VECTEUR mult_matrice_vecteurs_creux(MATRICE matrice, VECTEUR vecteur); // O(4n), O(n log n)

#endif
