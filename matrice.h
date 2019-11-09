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
  unsigned int *matricules; // Tout les matricules différentes
};

struct matrice_t{
  unsigned int *P; // Etudiants ( colonne )
  unsigned int *I; // Ligne
  unsigned int *X; // a transformer en int
  size_t nz;

  DONNEE fichier;
  size_t nbrLignes;//nbrCoursDif;
  size_t nbrColonnes;//nbr d'étudient différents
};

struct vecteur_t{
  unsigned int *I;
  int *X;
  unsigned int nbrNonZero;
};



MATRICE fichier_en_matrice(char* input); // O(4n) + O(2n(log(n))

MATRICE transposee_matrice(MATRICE matrice);

int *matrice_vecteurs_creux(MATRICE matrice, int *v);

#endif
