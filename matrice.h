#ifndef __MATRICES__
#define __MATRICES__

#define MAX 9
#define MAX_LIGNES 80

struct matrice_t{
  unsigned int *P; // Etudiants ( colonne )
  unsigned int *I; // Ligne
  unsigned int *X; //
  size_t nz;

  char (*cours)[MAX]; // Tout les cours stocké avec repetition
  char (*coursDif)[MAX]; // Tout les cours stocké sans repetition
  unsigned int *matricules; // Tout les matricules différentes

  size_t nbrCoursDif;
  size_t nbrEtudiantDif; //nbr d'étudient différents
};

typedef struct matrice_t MATRICE;

MATRICE fichier_en_matrice(char* input); // O(4n) + O(2n(log(n))

MATRICE transposee_matrice(MATRICE matrice);

#endif
