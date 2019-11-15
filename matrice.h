#ifndef __MATRICES__
#define __MATRICES__

#define MAX 9
#define MAX_LIGNES 80

typedef struct matrice_t MATRICE;
typedef struct donnee_t DONNEE;
typedef struct vecteur_t VECTEUR;

struct donnee_t{
  char (*cours)[MAX]; // Tout les cours stocké avec repetition
  char (*coursDif)[MAX]; // Tout les cours stocké sans repetition
  unsigned int *matricules; // Tout les matricules
};

struct matrice_t{
  unsigned int *P; // la n-eme valeurs de la colonne
  unsigned int *I; // Ligne
  unsigned int *X; // valeur de la case
  size_t nz; // nombres d'éléments

  DONNEE fichier; // contient les données du fichier
  size_t nbrLignes;
  size_t nbrColonnes;
};

struct vecteur_t{
  unsigned int *I; // lignes
  unsigned int *X; // valeur de la ligne
  unsigned int nbrNonZero; // nombres d'éléménts, donc taille de I
  unsigned int sommeTot; // sommes de tout les éléments
};


/* ------------------------------------------------------------------------- *
 * Renvois une matrice creuse, lu dans un fichier et transformeé en structure
 *
 * PARAMETRES
 * input        nom du fichier
 *
 * RETURN
 * matrice creuse
 * ------------------------------------------------------------------------- */
MATRICE fichier_en_matrice(char* input); // O(4n) + O(2n(log(n))

/* ------------------------------------------------------------------------- *
 * Transpose la matrice données en argument ( structure )
 *
 * PARAMETRES
 * matrice        matrice creuse en structure
 *
 * RETURN
 * matrice creuse
 * ------------------------------------------------------------------------- */
MATRICE transposee_matrice(MATRICE matrice);

/* ------------------------------------------------------------------------- *
 * Multiplie une matrice creuse avec un vecteur creux et renvois cette multiplication
 *
 * PARAMETRES
 * matrice        matrice creuse en structure
 * vecteur        vecteur creux
 *
 * RETURN
 * vecteur creux
 * ------------------------------------------------------------------------- */
VECTEUR mult_matrice_vecteurs_creux(MATRICE matrice, VECTEUR vecteur);

void destroy_matrice(MATRICE *matrice);
void destroy_vecteur(VECTEUR *vecteur);
void destroy_fichier(MATRICE *matrice);

void statistique(MATRICE matrice);
#endif
